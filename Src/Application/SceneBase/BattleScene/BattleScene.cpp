#include"Application/Headers.h"

BattleScene::BattleScene()
{
	m_mouseProcess = new MouseProcess;
	m_firstShotProcess = new FirstShotProcess;
	m_reflectorProcess = new ReflectorProcess;
	m_manumalMutualCollision = new ManumalMutualCollision;
	m_manumalEnemyCollison = new ManumalEnemyCollison;
	m_hitManumalwallProcess = new HitManumalwallProcess;
	m_hitManumalReflectorProcess = new HitManumalReflectorProcess;
	m_manumalList.clear();
	m_manumalList.push_back(new Morumon);
	m_manumalList.push_back(new Morumon);
	m_manumalList.push_back(new Morumon);
	m_manumalList[1]->SetPos({ 200,0 });
	m_manumalList[2]->SetPos({ -200,0 });

	m_scale = 40.0f;
	m_ang1 = 0.0f;
	m_power1 = 0;

	m_ang2 = 0;
	m_ang3 = 0;
	m_power2 = 0;
	m_power3 = 0;


	m_arrowTex = TEXMANA.GetTex("Data/Texture/BattleScene/arrow.png");
	m_arrowFlg = false;
	m_firstArrowPos = Math::Vector2::Zero;
	m_arrowAng = 0;
	m_arrowMat = Math::Matrix::Identity;
	m_arrowScale = 0;

	m_reflectorLength = m_reflectorProcess->GetLength();
	m_reflectorAng = m_reflectorProcess->GetAng();
	m_reflectorPos = m_reflectorProcess->GetPos();
	m_reflectorMat = Math::Matrix::Identity;

	m_mat1 = Math::Matrix::Identity;
	m_mat2 = Math::Matrix::Identity;
	m_mat3 = Math::Matrix::Identity;

	m_pos1 = Math::Vector2::Zero;
	m_pos2 = { 200,0 };
	m_pos3 = { -200,0 };

	m_moveVec1 = Math::Vector2::Zero;
	m_moveVec2 = Math::Vector2::Zero;
	m_moveVec3 = Math::Vector2::Zero;

	for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
	{
		(*i)->CalculateMoveVec();
	}

	m_rec1 = { 0,0,800,800 };
	m_color1 = { 1.0f,1.0f,1.0f,1.0f };

	m_tex = TEXMANA.GetTex("Data/Texture/Manumal/test.jpg");
	m_reflectorTex = TEXMANA.GetTex("Data/Texture/BattleScene/reflector.png");

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
	delete m_hitManumalReflectorProcess;
	m_manumalList.clear();
}

void BattleScene::Update()
{
	m_mousePos = m_mouseProcess->Update(m_mousePos);

	m_firstShotProcess->Update(m_manumalList[0]->GetManumalDataKinetic(), m_mousePos);
	for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
	{
		(*i)->CalculateMoveVec();
	}

	m_reflectorProcess->Update(m_firstShotProcess->GetClickFlg());

	m_manumalMutualCollision->Update(m_manumalList[0]->GetManumalData(), m_manumalList[1]->GetManumalDataKinetic());
	if (m_manumalMutualCollision->GetmHitManumalMutualFlg())
	{
		for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
		{
			(*i)->CalculateMoveVec();
		}
	}

	m_manumalEnemyCollison->Update(m_manumalList[0]->GetManumalDataKinetic(), m_manumalList[2]->GetManumalData());
	if (m_manumalEnemyCollison->GetHitManumalEnemyFlg())
	{
		for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
		{
			(*i)->CalculateMoveVec();
		}
	}

	for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
	{
		(*i)->MoveProcess();
	}

	//壁で跳ね返る処理
	for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
	{
		m_hitManumalwallProcess->Update((*i)->GetManumalDataKinetic());
		if (m_hitManumalwallProcess->GetHitWallFlg())
		{
			(*i)->CalculateMoveVec();
		}
	}

	//反射板で跳ね返る処理
	for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
	{
		m_hitManumalReflectorProcess->Update((*i)->GetManumalDataKinetic(), m_reflectorProcess);
		if (m_hitManumalReflectorProcess->GetHitReflectorFlg())
		{
			(*i)->CalculateMoveVec();
		}
	}

	for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
	{
		(*i)->CalculateMatrix();
	}
}

void BattleScene::Draw2D()
{
	SHADER.m_spriteShader.Begin();

	for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
	{
		(*i)->Draw();
	}

	m_reflectorProcess->Draw();

	if (m_firstShotProcess->GetArrowDrawFlg())
	{
		m_firstShotProcess->DrawArrow();
	}

	bool arrowMinOverFlg = m_arrowScale != 0;
	if (m_arrowFlg && arrowMinOverFlg)
	{
		UNIQUELIBRARY.Draw2D(m_arrowMat, m_arrowTex, 200, 1000, 0.8f);
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
