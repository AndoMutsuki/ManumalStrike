#include"Application/Headers.h"

using namespace ManumalStrikeNamespace;

BattleScene::BattleScene()
{
	m_scale = 40.0f;
	m_ang1 = 0.0f;
	m_power1 = 20.0f;

	m_reflectorAng = 90;

	m_mat1 = Math::Matrix::Identity;
	m_mat2 = Math::Matrix::Identity;

	m_pos1 = Math::Vector2::Zero;
	m_pos2 = Math::Vector2::Zero;

	CalculateManumalMoveVec(m_moveVec1, m_ang1);
	m_rec1 = { 0,0,800,800 };
	m_color1 = { 1.0f,1.0f,1.0f,1.0f };

	m_tex = new KdTexture;
	m_tex->Load("Data/Texture/Manumal/test.jpg");
}

BattleScene::~BattleScene()
{
	m_tex->Release();
	delete m_tex;
}

void BattleScene::Update()
{
	CalculateReflectorAng();

	CalculateManumlPos(m_pos1, m_moveVec1, m_ang1, m_power1);
	m_mat1 = DirectX::XMMatrixTranslation(m_pos1.x, m_pos1.y, 0);

	SCENE.SetGUIVariable(m_reflectorAng);
}

void BattleScene::Draw2D()
{
	SHADER.m_spriteShader.Begin();

	Math::Matrix scaleMat = DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f);
	m_mat1 = scaleMat * m_mat1;
	UNIQUELIBRARY.Draw2D(m_mat1, m_tex, &m_rec1, &m_color1);

	SHADER.m_spriteShader.End();
}

void BattleScene::CalculateManumlPos(Math::Vector2& _pos, Math::Vector2& _vec, float& _ang, float& _power)
{
	_pos += _vec * _power;

	if (CalculateHitWall(_pos, _ang))
	{
		CalculateManumalMoveVec(_vec, _ang);
	}
}

void BattleScene::CalculateManumalMoveVec(Math::Vector2& _vec, const float _ang)
{
	_vec = DirectX::XMVector2TransformNormal({ 0,1 }, DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(_ang)));
	_vec.Normalize();
}

const bool BattleScene::CalculateHitWall(Math::Vector2& _pos, float& _ang)
{
	bool hitWallFlg = false;
	if (m_width < abs(_pos.x))
	{
		hitWallFlg = true;

		UNIQUELIBRARY.CalculateHitPos(_pos.x, (float)m_width);
		UNIQUELIBRARY.CalculateHitAng(_ang, 0);
		UNIQUELIBRARY.AdjustmentHitAng(_ang);
	}

	if (m_height < abs(_pos.y)) 
	{
		hitWallFlg = true;

		UNIQUELIBRARY.CalculateHitPos(_pos.y, (float)m_height);

		if (_pos.y < 0)
		{
			UNIQUELIBRARY.CalculateHitAng(_ang, m_reflectorAng);	//”½ŽË”Â‚Ì”½ŽË
			UNIQUELIBRARY.AdjustmentHitAng(_ang);
		}
		else
		{
			UNIQUELIBRARY.CalculateHitAng(_ang, 90);
			UNIQUELIBRARY.AdjustmentHitAng(_ang);
		}
	}

	return hitWallFlg;
}

void BattleScene::CalculateReflectorAng()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_reflectorAng += 1.0f;
		//m_reflectorAng = std::max(m_reflectorAng, 135.0f);
		if (m_reflectorAng >= 135)
		{
			m_reflectorAng = 135.0f;
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_reflectorAng -= 1.0f;
		//m_reflectorAng = std::min(m_reflectorAng, 45.0f);
		if (m_reflectorAng <= 45)
		{
			m_reflectorAng = 45.0f;
		}
	}
}
