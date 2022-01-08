#include"Application/Headers.h"

using namespace ManumalStrikeNamespace;

BattleScene::BattleScene()
{
	m_mouseProcess = new MouseProcess;
	m_firstShotProcess = new FirstShotProcess;
	m_reflectorProcess = new ReflectorProcess;
	m_manumalList.push_back(new Morumon);
	m_manumalList.push_back(new Morumon);
	m_manumalList[1]->SetPos({ 100,0 });

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
	m_pos2 = {200,0};
	m_pos3 = {-200,0};

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

	m_effect = *(EFFEKSEER.GetEffect(uR"(Data/Effect/test.efk)"));
	m_handle = 0;
	m_effectFlg = false;

	//マウス
	m_baseMousePos = { 1280 / 2, 720 / 2 };
	ScreenToClient(APP.m_window.GetWndHandle(), &m_mousePos);
	SetCursorPos(m_baseMousePos.x, m_baseMousePos.y);
}

BattleScene::~BattleScene()
{
	delete m_reflectorProcess;
}

void BattleScene::Update()
{
	m_mousePos = m_mouseProcess->Update(m_mousePos);

	m_firstShotProcess->Update(m_manumalList[0]->GetManumalDataKinetic(), m_mousePos);
	for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
	{
		(*i)->CalculateMoveVec();
	}

	m_reflectorProcess->Update(m_arrowFlg);

	ManumalMutualCollision();
	ManumalEnemyCollision();

	for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
	{
		(*i)->MoveProcess();
	}
	CalculateManumlPos(m_manumalList[0]->GetManumalDataKinetic().pos, m_manumalList[0]->GetManumalDataKinetic().moveVec, m_manumalList[0]->GetManumalDataKinetic().ang, m_manumalList[0]->GetManumalDataKinetic().power, m_manumalList[0]->GetManumalDataKinetic().scale);
	CalculateManumlPos(m_pos2, m_moveVec2, m_ang2, m_power2, m_scale);
	CalculateManumlPos(m_pos3, m_moveVec3, m_ang3, m_power3, m_scale);

	for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
	{
		(*i)->CalculateMatrix();
	}
}

void BattleScene::Draw2D()
{
	SHADER.m_spriteShader.Begin();

	/*Math::Matrix scaleMat = DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f);
	m_mat1 = scaleMat * m_mat1;
	UNIQUELIBRARY.Draw2D(m_mat1, m_tex, &m_rec1, &m_color1);
	m_mat2 = scaleMat * m_mat2;
	UNIQUELIBRARY.Draw2D(m_mat2, m_tex, &m_rec1, &m_color1);
	m_mat3 = scaleMat * m_mat3;
	UNIQUELIBRARY.Draw2D(m_mat3, m_tex, &m_rec1, &m_color1);*/

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

void BattleScene::CalculateManumlPos(Math::Vector2& _pos, Math::Vector2& _vec, float& _ang, float& _power, const float& _scale)
{
	//マニュマルが動く処理
	//_pos += _vec * _power;

	//反射板で跳ね返る処理
	if (CalculateHitReflector(_pos, _ang, _scale))
	{
		for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
		{
			(*i)->CalculateMoveVec();
		}
	}

	//壁で跳ね返る処理
	if (CalculateHitWall(_pos, _ang, _scale))
	{
		for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
		{
			(*i)->CalculateMoveVec();
		}
	}
}

const bool BattleScene::CalculateHitWall(Math::Vector2& _pos, float& _ang, const float& _scale)
{
	bool hitWallFlg = false;
	if (Width - _scale < abs(_pos.x))
	{
		hitWallFlg = true;

		CalculateHitPos(_pos.x, (float)(Width - _scale));
		CalculateHitAng(_ang, 0);
	}

	if (Height - _scale < abs(_pos.y))
	{
		hitWallFlg = true;

		CalculateHitPos(_pos.y, (float)(Height - _scale));
		CalculateHitAng(_ang, 90);
	}

	return hitWallFlg;
}

const bool BattleScene::CalculateHitReflector(Math::Vector2& _pos, float& _ang, const float& _scale)
{
	//反射板より明らかに上にある場合は早期リターン
	if (_pos.y > -150) return false;

	//x座標が反射板に当たっているか
	float relativePos = _pos.x - m_reflectorProcess->GetPos().x;	//マニュマルの相対的な位置
	float cosO = cos(DirectX::XMConvertToRadians(m_reflectorProcess->GetAng() + 90));
	bool hitReflectorX = abs(relativePos) - abs(m_reflectorProcess->GetLength() * cosO) > _scale;
	if (hitReflectorX) return false;

	//y座標が反射板に当たっているか
	float tanO = tan(DirectX::XMConvertToRadians(m_reflectorProcess->GetAng() + 90));
	bool hitReflectorY = abs(abs(_pos.y) - abs(-ReflectorPosY + (relativePos * tanO))) > _scale;
	if (hitReflectorY) return false;

	//反射の計算
	bool hitReflectorTopFlg = _pos.y > (-ReflectorPosY + (relativePos * tanO));
	if (hitReflectorTopFlg)
	{
		CalculateHitPos(_pos.y, (-ReflectorPosY + (relativePos * tanO) + _scale));
		CalculateHitAng(_ang, m_reflectorProcess->GetAng());
	}
	else
	{
		CalculateHitPos(_pos.y, (-ReflectorPosY + (relativePos * tanO) - _scale));
		CalculateHitAng(_ang, m_reflectorProcess->GetAng() + 90);

		if (m_reflectorProcess->GetAng() > 90)
		{
			_ang = UNIQUELIBRARY.AdjustmentLowerLimit(_ang, 200.0f);
			CalculateHitPos(_pos.x, (m_reflectorProcess->GetLength() * cosO  - m_reflectorProcess->GetPos().x - _scale));
		}
		else if (m_reflectorProcess->GetAng() < 90)
		{
			_ang = UNIQUELIBRARY.AdjustmentUpperLimit(_ang, 160.0f);
			CalculateHitPos(_pos.x, (m_reflectorProcess->GetLength() * cosO + m_reflectorProcess->GetPos().x - _scale));
		}
		else
		{
			if (_pos.x > m_reflectorProcess->GetPos().x)
			{
				_ang = UNIQUELIBRARY.AdjustmentLowerLimit(_ang, 200.0f);
				CalculateHitPos(_pos.x, (m_reflectorProcess->GetLength() * cosO - m_reflectorProcess->GetPos().x - _scale));
			}
			else
			{
				_ang = UNIQUELIBRARY.AdjustmentUpperLimit(_ang, 160.0f);
				CalculateHitPos(_pos.x, (m_reflectorProcess->GetLength() * cosO + m_reflectorProcess->GetPos().x - _scale));
			}
		}
	}

	return true;
}

void BattleScene::CalculateHitPos(float& _standardPos, const float& _objectPos)
{
	if (_standardPos >= 0)
	{
		_standardPos += abs(_objectPos) - abs(_standardPos);
	}
	else
	{
		_standardPos -= abs(_objectPos) - abs(_standardPos);
	}
}

void BattleScene::CalculateHitAng(float& _standardAng, const float& _objectAng)
{
	_standardAng = 360 - _standardAng + (2 * _objectAng);

	while (_standardAng > 360)
	{
		_standardAng -= 360;
	}
}

void BattleScene::ManumalMutualCollision()
{
	if (UNIQUELIBRARY.GetVecLength(m_pos1, m_pos2) > m_scale + m_scale)return;

	Math::Vector2 betweenVec = m_pos2 - m_pos1;
	betweenVec.Normalize();
	m_pos2 = m_pos1 + betweenVec * (m_scale + m_scale);
	m_ang2 = -UNIQUELIBRARY.GetVecAng(m_pos2, m_pos1);
	//m_power2 = 50;
	for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
	{
		(*i)->CalculateMoveVec();
	}
}

void BattleScene::ManumalEnemyCollision()
{
	if (UNIQUELIBRARY.GetVecLength(m_pos1, m_pos3) > m_scale + m_scale)return;

	Math::Vector2 betweenVec = m_pos1 - m_pos3;
	betweenVec.Normalize();
	m_pos1 = m_pos3 + betweenVec * (m_scale + m_scale);
	float collicionAng = -UNIQUELIBRARY.GetVecAng(m_pos1, m_pos3) + 180.0f;

	if (collicionAng <= 135 && collicionAng > 45)
	{
		CalculateHitAng(m_ang1, 0);
	}
	else if (collicionAng <= 225 && collicionAng > 135)
	{
		CalculateHitAng(m_ang1, 90);
	}
	else if (collicionAng <= 315 && collicionAng > 225)
	{
		CalculateHitAng(m_ang1, 0);
	}
	else
	{
		CalculateHitAng(m_ang1, 90);
	}

	for (auto i = m_manumalList.begin(); i != m_manumalList.end(); ++i)
	{
		(*i)->CalculateMoveVec();
	}
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
