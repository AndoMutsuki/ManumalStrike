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
		delete *iter;
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
	m_mousePos = m_mouseProcess->Update(m_mousePos);

	//HPの計算
	m_calculateHP->Update();
	if (!m_calculateHP->GetAliveFlg())
	{
		m_drawProcess->SetHPRaito(m_calculateHP->GetHPRaito());
		m_drawProcess->Update();
		return;
	}

	//打ち出されたらフラグを立てる
	if (m_firstShotProcess->DoCalculateArrowMat() && !GetAsyncKeyState(MK_LBUTTON))
	{
		m_shotedFlg = true;
	}

	//打ち出せるマニュマルを示す
	if (!m_shotedFlg)
	{
		m_manumalAttackCircle->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalData());
	}

	//最初に打ち出す処理
	if (m_manumalList[m_nowMoveManumalNum]->GetManumalData().nowSpeed <= 0)
	{
		m_firstShotProcess->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalDataKinetic(), m_mousePos);
		m_manumalList[m_nowMoveManumalNum]->CalculateMoveVec();
	}

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
	if (m_shotedFlg && m_allManumalStopFlg)
	{
		for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
		{
			(*iter)->GetManumalDataKinetic().frendFlg = false;
		}

		for (auto iter = m_enemyList.begin(); iter != m_enemyList.end(); ++iter)
		{
			if (!(*iter)->GetAliveFlg())continue;

			(*iter)->GetEnemyDataKinetic().nowAttackTurn--;

			if ((*iter)->GetEnemyDataKinetic().nowAttackTurn != 0)continue;

			(*iter)->GetEnemyDataKinetic().nowAttackTurn = (*iter)->GetEnemyData().attackTurn;

			SetEnemyAttack((*iter)->GetEnemyData().attackType, (*iter)->GetEnemyData().pos);
			if (m_enemyAttack != nullptr)
			{
				m_enemyAttack->Update((*iter)->GetEnemyDataKinetic(), m_manumalList);
				m_calculateHP->SetDamage(m_enemyAttack->GetDamage());
			}
			delete m_enemyAttack;
			m_enemyAttack = nullptr;
		}

		m_shotedFlg = false;
		m_manumalAttackCircle->Init();
		m_nowMoveManumalNum++;
		if (m_nowMoveManumalNum >= m_nowMoveManumalNumMax)
		{
			m_nowMoveManumalNum = 0;
		}
		m_manumalAttackCircle->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalData());
		return;
	}

	//マニュマルの移動処理
	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::MoveProcess));

	//マニュマル同士の当たり判定
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		if (m_manumalList[m_nowMoveManumalNum] == *iter)continue;

		m_manumalMutualCollision->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalData(), (*iter)->GetManumalDataKinetic());
		if (m_manumalMutualCollision->GetmHitManumalMutualFlg())
		{
			std::for_each(m_manumalList.begin(), m_manumalList.end(),
				std::mem_fun(&ManumalBase::CalculateMoveVec));

			if ((*iter)->GetManumalData().frendFlg)continue;

			(*iter)->GetManumalDataKinetic().frendFlg = true;

			SetFriendshipCombo((*iter)->GetManumalData().frendshipType, (*iter)->GetManumalData().pos);
			if (m_frendshipCombo != nullptr)
			{
				m_frendshipCombo->Update((*iter)->GetManumalDataKinetic(), m_enemyList);
			}
			delete m_frendshipCombo;
			m_frendshipCombo = nullptr;
		}
	}

	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		for (auto iter2 = m_manumalList.begin(); iter2 != m_manumalList.end(); ++iter2)
		{
			if (m_manumalList[m_nowMoveManumalNum] == *iter)continue;
			if (m_manumalList[m_nowMoveManumalNum] == *iter2)continue;
			if (iter == iter2)continue;

			m_manumalMutualCollision->Update((*iter)->GetManumalDataKinetic(), (*iter2)->GetManumalDataKinetic());
			if (m_manumalMutualCollision->GetmHitManumalMutualFlg())
			{
				(*iter)->CalculateMoveVec();
				(*iter2)->CalculateMoveVec();
			}
		}
	}

	//マニュマルと敵の当たり判定
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		for (auto iterE = m_enemyList.begin(); iterE != m_enemyList.end(); ++iterE)
		{
			if (!(*iterE)->GetAliveFlg())continue;

			m_manumalEnemyCollison->Update((*iter)->GetManumalDataKinetic(), (*iterE)->GetEnemyData());
			if (m_manumalEnemyCollison->GetHitManumalEnemyFlg())
			{
				(*iter)->CalculateMoveVec();

				if (m_manumalList[m_nowMoveManumalNum] == *iter)
				{
					(*iterE)->SetDamage((int)(*iter)->GetManumalData().attack);
				}
			}
		}
	}

	//反射板で跳ね返る処理
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		m_hitManumalReflectorProcess->Update((*iter)->GetManumalDataKinetic(), m_reflectorProcess);
		if (m_hitManumalReflectorProcess->GetHitReflectorFlg())
		{
			(*iter)->CalculateMoveVec();
		}
	}

	//壁で跳ね返る処理
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		m_hitManumalwallProcess->Update((*iter)->GetManumalDataKinetic());
		if (m_hitManumalwallProcess->GetHitWallFlg())
		{
			(*iter)->CalculateMoveVec();
		}
	}

	//マニュマルの行列の計算
	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::CalculateMatrix));

	//HPのセット
	m_drawProcess->SetHPRaito(m_calculateHP->GetHPRaito());

	//UI関係の処理
	m_drawProcess->Update();

	//エフェクト関係
	std::for_each(m_effectList.begin(), m_effectList.end(),
		std::mem_fun(&EffectBase::Update));

	for (UINT i = 0; i < m_effectList.size(); i++)
	{
		if (m_effectList[i]->GetEffectFinishFlg())
		{
			delete m_effectList[i];
			m_effectList = UNIQUELIBRARY.DeleteList(i, m_effectList);
		}
	}
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
