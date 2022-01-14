#include"Application/Headers.h"

BattleScene::BattleScene()
{
	m_mouseProcess = new MouseProcess;
	m_firstShotProcess = new FirstShotProcess;
	m_reflectorProcess = new ReflectorProcess;
	m_manumalMutualCollision = new ManumalMutualCollision;
	m_manumalEnemyCollison = new ManumalEnemyCollison;
	m_hitManumalwallProcess = new HitManumalWallProcess;
	m_hitManumalReflectorProcess = new HitManumalReflectorProcess;
	m_calculateHP = new CalculateHP;
	m_calculateSpeed = new CalculateSpeed;
	m_drawProcess = new DrawProcess;
	m_manumalAttackCircle = new ManumalAttackCircle;

	m_manumalList.clear();
	m_manumalList.push_back(new Raibit);
	m_manumalList.push_back(new Morumon);
	m_manumalList.push_back(new Pebrat);
	m_manumalList[0]->SetPos({ -200,-100 });
	m_manumalList[1]->SetPos({ 0,-120 });
	//m_manumalList[2]->SetPos({ 200,-100 });
	m_manumalList[2]->SetPos({ -350,230 });
	m_enemyList.clear();
	m_enemyList.push_back(new FireCube);
	m_enemyList.push_back(new FireCube);
	m_enemyList.push_back(new Hinokokko);
	m_enemyList[0]->SetEnemyPos({ -400,250 });
	m_enemyList[1]->SetEnemyPos({ 350,100 });
	m_enemyList[2]->SetEnemyPos({ 0,120 });
	m_effectList.clear();

	//最大HPを計算
	int HPMax = std::accumulate(m_manumalList.begin(), m_manumalList.end(), 0,
		[](int HP, ManumalBase* manumalBase) { return HP + manumalBase->GetManumalData().HP; });
	m_calculateHP->SetHPMax(HPMax);

	//マニュマル関係
	m_nowMoveManumalNum = 0;
	m_shotedFlg = false;

	//マウス
	m_baseMousePos = { 1280 / 2, 720 / 2 };
	ScreenToClient(APP.m_window.GetWndHandle(), &m_mousePos);
	SetCursorPos(m_baseMousePos.x, m_baseMousePos.y);
}

BattleScene::~BattleScene()
{
	delete m_mouseProcess;
	delete m_firstShotProcess;
	delete m_reflectorProcess;
	delete m_manumalMutualCollision;
	delete m_manumalEnemyCollison;
	delete m_hitManumalwallProcess;
	delete m_hitManumalReflectorProcess;
	delete m_drawProcess;
	delete m_manumalAttackCircle;

	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		delete* iter;
	}
	m_manumalList.clear();

	for (auto iter = m_enemyList.begin(); iter != m_enemyList.end(); ++iter)
	{
		delete* iter;
	}
	m_enemyList.clear();

	for (auto iter = m_effectList.begin(); iter != m_effectList.end(); ++iter)
	{
		delete* iter;
	}
	m_effectList.clear();
}

void BattleScene::Update()
{
	//マウスの処理
	m_mousePos = m_mouseProcess->Update(m_mousePos);

	//HPの処理
	bool aliveFlg = HPProcess();	//プレイヤーが生きているかのフラグ
	if (!aliveFlg)return;			//死んでいたら早期リターン

	//マニュマルが打ち出されたらフラグを立てる
	bool shotFlg = m_firstShotProcess->DoCalculateArrowMat() && !GetAsyncKeyState(MK_LBUTTON);
	if (shotFlg)
	{
		m_shotedFlg = true;
	}

	//打ち出せるマニュマルに円のエフェクトを付ける
	if (!m_shotedFlg)
	{
		m_manumalAttackCircle->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalData());
	}

	//最初に打ち出す処理
	FirstShotProcessBattleScene();

	//反射板の処理
	m_reflectorProcess->Update(m_firstShotProcess->GetClickFlg());

	//スピードの計算
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		m_calculateSpeed->Update((*iter)->GetManumalDataKinetic());
	}

	//全てのマニュマルが止まっているか
	m_allManumalStopFlg = std::all_of(m_manumalList.begin(), m_manumalList.end(),
		[](ManumalBase* manumalBase) {return manumalBase->GetManumalData().nowSpeed <= 0; });

	//次のマニュマルの発射に移る
	NextManumalProcess();

	//マニュマルの移動処理
	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::MoveProcess));

	//マニュマル同士の当たり判定
	ManumalMutualCollisionProcess();

	//マニュマルと敵の当たり判定
	ManumalEnemyCollisonProcess();

	//反射板で跳ね返る処理
	HitManumalReflectorProcessBattleScene();

	//壁で跳ね返る処理
	HitManumalwallProcessBattleScene();

	//マニュマルの行列の計算
	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::CalculateMatrix));

	//HPのセット
	m_drawProcess->SetHPRaito(m_calculateHP->GetHPRaito());

	//UI関係の処理
	m_drawProcess->Update();

	//エフェクト関係
	EffectProcess();
}

void BattleScene::Draw2D()
{
	SHADER.m_spriteShader.Begin();

	m_drawProcess->Draw();

	if (!m_shotedFlg)
	{
		m_manumalAttackCircle->Draw();
	}

	for (auto iter = m_enemyList.begin(); iter != m_enemyList.end(); ++iter)
	{
		if (!(*iter)->GetAliveFlg())continue;

		(*iter)->Draw();
	}

	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::Draw));

	m_reflectorProcess->Draw();

	if (m_firstShotProcess->GetArrowDrawFlg())
	{
		m_firstShotProcess->DrawArrow();
	}

	std::for_each(m_effectList.begin(), m_effectList.end(),
		std::mem_fun(&EffectBase::Draw));

	SHADER.m_spriteShader.End();
}

const bool BattleScene::HPProcess()
{
	m_calculateHP->Update();
	if (!m_calculateHP->GetAliveFlg())
	{
		CalculateHPDeath();
		return false;
	}

	return true;
}

void BattleScene::CalculateHPDeath()
{
	m_drawProcess->SetHPRaito(m_calculateHP->GetHPRaito());
	m_drawProcess->Update();
}

void BattleScene::FirstShotProcessBattleScene()
{
	bool moveFlg = m_manumalList[m_nowMoveManumalNum]->GetManumalData().nowSpeed > 0;	//打ち出すマニュマルが動いているか

	//マニュマルが止まっていたら
	if (!moveFlg)
	{
		//最初に打ち出す処理
		m_firstShotProcess->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalDataKinetic(), m_mousePos);

		//ベクトルの計算
		m_manumalList[m_nowMoveManumalNum]->CalculateMoveVec();
	}
}

void BattleScene::NextManumalProcess()
{
	bool nextManumalFlg = m_shotedFlg && m_allManumalStopFlg;
	if (!nextManumalFlg)return;

	m_shotedFlg = false;

	//友情コンボ終了のフラグをきる
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		(*iter)->GetManumalDataKinetic().friendFinishFlg = false;
	}

	//敵の攻撃の処理
	EnemyAttackProcess();

	//打ち出すマニュマルの円のエフェクトの処理
	ShotCircleProcess();

	return;
}

void BattleScene::EnemyAttackProcess()
{
	for (auto iter = m_enemyList.begin(); iter != m_enemyList.end(); ++iter)
	{
		//敵が死んでいたらぬける
		if (!(*iter)->GetAliveFlg())continue;

		//攻撃のターン数を減らす
		(*iter)->GetEnemyDataKinetic().nowAttackTurn--;

		//まだ攻撃するターン数ではない場合ぬける
		if ((*iter)->GetEnemyDataKinetic().nowAttackTurn != 0)continue;

		//ターン数を最大値に戻す
		(*iter)->GetEnemyDataKinetic().nowAttackTurn = (*iter)->GetEnemyData().attackTurn;

		//敵の攻撃をセットする
		SetEnemyAttack((*iter)->GetEnemyData().attackType, (*iter)->GetEnemyData().pos);
		if (m_enemyAttack != nullptr)
		{
			//ダメージを算出する
			m_enemyAttack->Update((*iter)->GetEnemyDataKinetic(), m_manumalList);
			m_calculateHP->SetDamage(m_enemyAttack->GetDamage());
		}

		//デリート
		delete m_enemyAttack;
		m_enemyAttack = nullptr;
	}
}

void BattleScene::SetEnemyAttack(enemyAttackType _enemyAttackType, const Math::Vector2& _pos)
{
	switch (_enemyAttackType)
	{
	case enemyAttackType::BEAM:
		m_enemyAttack = nullptr;
		break;

	case enemyAttackType::EXPLOSION:
		m_enemyAttack = new Explosion;
		m_effectList.push_back(new ExplosionEffect);
		break;

	case enemyAttackType::BIGEXPLOSION:
		m_enemyAttack = new BigExplosion;
		m_effectList.push_back(new ExplosionEffect);
		break;

	default:
		m_frendshipCombo = nullptr;
		assert(!"敵の攻撃タイプに不正な値");
		break;
	}

	m_effectList[m_effectList.size() - 1]->Init(_pos, m_enemyAttack->GetRange());
}

void BattleScene::ShotCircleProcess()
{
	//次のマニュマルを打ち出す
	m_nowMoveManumalNum++;
	if (m_nowMoveManumalNum >= m_nowMoveManumalNumMax)
	{
		m_nowMoveManumalNum = 0;
	}

	//円のエフェクトの処理を行う
	m_manumalAttackCircle->Init();
	m_manumalAttackCircle->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalData());
}

void BattleScene::ManumalMutualCollisionProcess()
{
	//動いているマニュマルと止まっているマニュマルの当たり判定
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		//同一のマニュマルの場合は除外する
		if (m_manumalList[m_nowMoveManumalNum] == *iter)continue;

		//当たり判定
		m_manumalMutualCollision->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalData(), (*iter)->GetManumalDataKinetic());

		//当たっていなれば除く
		if (!m_manumalMutualCollision->GetHitManumalMutualFlg())continue;

		//当たっていた時の処理
		HitedManumalMutualCollisionProcess(iter);
	}

	//止まっているマニュマル同士の当たり判定
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		for (auto iter2 = m_manumalList.begin(); iter2 != m_manumalList.end(); ++iter2)
		{
			//動いているマニュマルは除く
			if (m_manumalList[m_nowMoveManumalNum] == *iter)continue;

			//動いているマニュマルは除く
			if (m_manumalList[m_nowMoveManumalNum] == *iter2)continue;

			//同一のマニュマルの場合は除外する
			if (iter == iter2)continue;

			//当たり判定
			m_manumalMutualCollision->Update((*iter)->GetManumalDataKinetic(), (*iter2)->GetManumalDataKinetic());

			//当たっていなければ除く
			if (!m_manumalMutualCollision->GetHitManumalMutualFlg())continue;

			//当たっていた時の処理
			(*iter)->CalculateMoveVec();
			(*iter2)->CalculateMoveVec();

		}
	}
}

void BattleScene::HitedManumalMutualCollisionProcess(std::vector<ManumalBase*>::iterator _iter)
{
	//友情コンボの処理
	//すでに友情コンボを発動していたらリターン
	if ((*_iter)->GetManumalData().friendFinishFlg)return;

	//友情コンボフラグをたてる
	(*_iter)->GetManumalDataKinetic().friendFinishFlg = true;

	//友情コンボをセットする
	SetFriendshipCombo((*_iter)->GetManumalData().frendshipType, (*_iter)->GetManumalData().pos);
	if (m_frendshipCombo != nullptr)
	{
		//友情コンボの処理
		m_frendshipCombo->Update((*_iter)->GetManumalDataKinetic(), m_enemyList);
	}

	//ベクトルの計算
	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::CalculateMoveVec));

	//デリート
	delete m_frendshipCombo;
	m_frendshipCombo = nullptr;
}

void BattleScene::SetFriendshipCombo(frendshipComboType _frendshipComboType, const Math::Vector2& _pos)
{
	switch (_frendshipComboType)
	{
	case frendshipComboType::BEAM:
		m_enemyAttack = nullptr;
		break;

	case frendshipComboType::EXPLOSION:
		m_frendshipCombo = new FriendExplosion;
		m_effectList.push_back(new ExplosionEffect);
		break;

	default:
		m_enemyAttack = nullptr;
		assert(!"敵の攻撃タイプに不正な値");
		break;
	}

	m_effectList[m_effectList.size() - 1]->Init(_pos, m_frendshipCombo->GetRange());
}

void BattleScene::ManumalEnemyCollisonProcess()
{
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		for (auto iterE = m_enemyList.begin(); iterE != m_enemyList.end(); ++iterE)
		{
			//敵が死んでいたら除く
			if (!(*iterE)->GetAliveFlg())continue;

			//マニュマルと敵の当たり判定
			m_manumalEnemyCollison->Update((*iter)->GetManumalDataKinetic(), (*iterE)->GetEnemyData());

			//当たっていなければ除く
			if (!m_manumalEnemyCollison->GetHitManumalEnemyFlg())continue;

			//行列の計算
			(*iter)->CalculateMoveVec();

			//当たったマニュマルが動いていないなら除外
			if (m_manumalList[m_nowMoveManumalNum] != *iter)continue;

			//当たったマニュマルが動いていたらダメージの処理
			(*iterE)->SetDamage((int)(*iter)->GetManumalData().attack);
		}
	}
}

void BattleScene::HitManumalReflectorProcessBattleScene()
{
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		//反射板で跳ね返る処理
		m_hitManumalReflectorProcess->Update((*iter)->GetManumalDataKinetic(), m_reflectorProcess);

		//反射板に当たっていなかったら除外
		if (!m_hitManumalReflectorProcess->GetHitReflectorFlg())continue;

		//反射板に当たっているときの処理
		(*iter)->CalculateMoveVec();
	}
}

void BattleScene::HitManumalwallProcessBattleScene()
{
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		//壁で跳ね返る処理
		m_hitManumalwallProcess->Update((*iter)->GetManumalDataKinetic());

		//壁に当たっていなかったら除外
		if (!m_hitManumalwallProcess->GetHitWallFlg())continue;

		//壁に当たっているときの処理
		(*iter)->CalculateMoveVec();
	}
}

void BattleScene::EffectProcess()
{
	//エフェクトのアップデート
	std::for_each(m_effectList.begin(), m_effectList.end(),
		std::mem_fun(&EffectBase::Update));

	for (UINT i = 0; i < m_effectList.size(); i++)
	{
		//エフェクトが終わってなかったら除外
		if (!m_effectList[i]->GetEffectFinishFlg())continue;

		//エフェクトを消す処理
		delete m_effectList[i];
		m_effectList = UNIQUELIBRARY.DeleteList(i, m_effectList);
	}
}
