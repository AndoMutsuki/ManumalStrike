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
	m_drawProcess = new DrawProcess;
	m_manumalList.clear();
	m_manumalList.push_back(new Morumon);
	m_manumalList.push_back(new Morumon);
	m_manumalList.push_back(new Morumon);
	m_manumalList[1]->SetPos({ 200,0 });
	m_manumalList[2]->SetPos({ -200,0 });

	//最大HPを計算
	int HPMax = std::accumulate(m_manumalList.begin(), m_manumalList.end(), 0,
		[](int HP, ManumalBase* manumalBase) { return HP + manumalBase->GetManumalData().HP; });
	m_calculateHP->SetHPMax(HPMax);

	m_effect = *(EFFEKSEER.GetEffect(uR"(Data/Effect/reflectWall/reflectWall.efk)"));
	m_handle = 0;
	m_effectFlg = false;

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
	m_manumalList.clear();
}

void BattleScene::Update()
{
	m_mousePos = m_mouseProcess->Update(m_mousePos);

	m_firstShotProcess->Update(m_manumalList[0]->GetManumalDataKinetic(), m_mousePos);
	m_manumalList[0]->CalculateMoveVec();

	m_reflectorProcess->Update(m_firstShotProcess->GetClickFlg());

	m_manumalMutualCollision->Update(m_manumalList[0]->GetManumalData(), m_manumalList[1]->GetManumalDataKinetic());
	if (m_manumalMutualCollision->GetmHitManumalMutualFlg())
	{
		std::for_each(m_manumalList.begin(), m_manumalList.end(),
			std::mem_fun(&ManumalBase::CalculateMoveVec));
	}

	m_manumalEnemyCollison->Update(m_manumalList[0]->GetManumalDataKinetic(), m_manumalList[2]->GetManumalData());
	if (m_manumalEnemyCollison->GetHitManumalEnemyFlg())
	{
		std::for_each(m_manumalList.begin(), m_manumalList.end(),
			std::mem_fun(&ManumalBase::CalculateMoveVec));
	}

	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::MoveProcess));

	m_calculateHP->Update();
	if (!m_calculateHP->GetAliveFlg())
	{
		return;
	}

	//反射板で跳ね返る処理
	m_hitManumalReflectorProcess->Update(m_manumalList[0]->GetManumalDataKinetic(), m_reflectorProcess);
	if (m_hitManumalReflectorProcess->GetHitReflectorFlg())
	{
		m_manumalList[0]->CalculateMoveVec();
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

	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::CalculateMatrix));
}

void BattleScene::Draw2D()
{
	SHADER.m_spriteShader.Begin();

	m_drawProcess->Draw();

	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::Draw));

	m_reflectorProcess->Draw();

	if (m_firstShotProcess->GetArrowDrawFlg())
	{
		m_firstShotProcess->DrawArrow();
	}

	EffectDraw();

	SHADER.m_spriteShader.End();
}

void BattleScene::EffectDraw()
{
	if (!m_effectFlg)
	{
		// エフェクトの再生
		m_handle = EFFEKSEER.GetManager()->Play(m_effect, 0, 0, 0);
		m_effectFlg = true;
	}

	// エフェクトの移動
	//EFFEKSEER.GetManager()->AddLocation(m_handle, ::Effekseer::Vector3D(0.2f, 0.0f, 0.0f));

	//EFFEKSEER.GetManager()->SetRotation(m_handle, 0,0,0);
	//EFFEKSEER.GetManager()->SetRotation(m_handle, {0,1,0}, 270);

	// マネージャーの更新
	EFFEKSEER.GetManager()->Update();

	// エフェクトの描画開始処理を行う。
	EFFEKSEER.GetRenderer()->BeginRendering();

	// エフェクトの描画を行う。
	EFFEKSEER.GetManager()->Draw();

	// エフェクトの描画終了処理を行う。
	EFFEKSEER.GetRenderer()->EndRendering();
}
