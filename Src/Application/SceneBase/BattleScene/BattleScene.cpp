#include"Application/Headers.h"

using namespace ManumalStrikeNamespace;

BattleScene::BattleScene()
{
	m_scale = 40.0f;
	m_ang1 = 0.0f;
	m_power1 = 20.0f;

	m_reflectorScale = 125.0f;
	m_reflectorAng = 90;
	m_reflectorPos = Math::Vector2::Zero;
	m_reflectorMat = Math::Matrix::Identity;

	m_mat1 = Math::Matrix::Identity;
	m_mat2 = Math::Matrix::Identity;

	m_pos1 = Math::Vector2::Zero;
	m_pos2 = Math::Vector2::Zero;

	CalculateManumalMoveVec(m_moveVec1, m_ang1);
	m_rec1 = { 0,0,800,800 };
	m_color1 = { 1.0f,1.0f,1.0f,1.0f };

	m_tex = TEXMANA.GetTex("Data/Texture/Manumal/test.jpg");
	m_reflectorTex = TEXMANA.GetTex("Data/Texture/BattleScene/reflector.png");
}

BattleScene::~BattleScene()
{
}

void BattleScene::Update()
{
	CalculateReflectorPos();
	CalculateReflectorAng();
	CalculateReflectorMatrix();

	CalculateManumlPos(m_pos1, m_moveVec1, m_ang1, m_power1, m_scale);
	m_mat1 = DirectX::XMMatrixTranslation(m_pos1.x, m_pos1.y, 0);
}

void BattleScene::Draw2D()
{
	SHADER.m_spriteShader.Begin();

	if (!m_testFlg)return;
	Math::Matrix scaleMat = DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f);
	m_mat1 = scaleMat * m_mat1;
	UNIQUELIBRARY.Draw2D(m_mat1, m_tex, &m_rec1, &m_color1);

	UNIQUELIBRARY.Draw2D(m_reflectorMat, m_reflectorTex, 250, 20);

	SHADER.m_spriteShader.End();
}

void BattleScene::CalculateManumlPos(Math::Vector2& _pos, Math::Vector2& _vec, float& _ang, float& _power, const float& _scale)
{
	//マニュマルが動く処理
	_pos += _vec * _power;

	//壁で跳ね返る処理
	if (CalculateHitWall(_pos, _ang, _scale))
	{
		CalculateManumalMoveVec(_vec, _ang);
	}

	//反射板で跳ね返る処理
	if (CalculateHitReflector(_pos, _ang, _scale))
	{
		CalculateManumalMoveVec(_vec, _ang);
	}

	CalculateHitReflectorUnder(_pos, _ang, _scale);
}

void BattleScene::CalculateManumalMoveVec(Math::Vector2& _vec, const float _ang)
{
	_vec = DirectX::XMVector2TransformNormal({ 0,1 }, DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(_ang)));
	_vec.Normalize();
}

const bool BattleScene::CalculateHitWall(Math::Vector2& _pos, float& _ang, const float& _scale)
{
	bool hitWallFlg = false;
	if (Width - _scale < abs(_pos.x))
	{
		hitWallFlg = true;

		CalculateHitPos(_pos.x, (float)(Width - _scale));
		CalculateHitAng(_ang, 0);
		AdjustmentHitAng(_ang);
	}

	if (Height - _scale < abs(_pos.y))
	{
		hitWallFlg = true;

		CalculateHitPos(_pos.y, (float)(Height - _scale));
		CalculateHitAng(_ang, 90);
		AdjustmentHitAng(_ang);
	}

	return hitWallFlg;
}

const bool BattleScene::CalculateHitReflector(Math::Vector2& _pos, float& _ang, const float& _scale)
{
	//反射板より明らかに上にある場合は早期リターン
	if (_pos.y > -150)return false;	

	//x座標が反射板に当たっているか
	float relativePos = _pos.x - m_reflectorPos.x;	//マニュマルの相対的な位置
	float cosO = cos(DirectX::XMConvertToRadians(m_reflectorAng + 90));
	if (abs(relativePos) - abs(m_reflectorScale * cosO - _scale) > 0)return false;

	//y座標が反射板に当たっているか
	float tanO = tan(DirectX::XMConvertToRadians(m_reflectorAng + 90));
	if (_pos.y - (-ReflectorPosY + (relativePos * tanO) + _scale) > 0)return false;

	{
		//反射の計算
		CalculateHitPos(_pos.y, (-ReflectorPosY + (relativePos * tanO) + _scale));
		CalculateHitAng(_ang, m_reflectorAng);
		AdjustmentHitAng(_ang);
	}

	return true;
}

const bool BattleScene::CalculateHitReflectorUnder(Math::Vector2& _pos, float& _ang, const float& _scale)
{
	//反射板より明らかに上にある場合は早期リターン
	if (_pos.y > -150)return false;

	float relativePos = _pos.x - m_reflectorPos.x;	//マニュマルの相対的な位置
	float cosO = cos(DirectX::XMConvertToRadians(m_reflectorAng + 90));
	float tanO = tan(DirectX::XMConvertToRadians(m_reflectorAng + 90));

	//反射板の下から当たっているか
	{
		bool collisionX;	//x座標が反射板の下に当たっているか
		bool collisionY;	//y座標が反射板の下に当たっているか

		collisionX = (abs(relativePos) - abs(m_reflectorScale * cosO - _scale) > 0);
		if (relativePos > 0)
		{
			collisionY = (_pos.y - (-ReflectorPosY + (m_reflectorScale * tanO) + _scale)) < 0;
			if (collisionX && collisionY)
			{
				m_testFlg = false;
			}
			return true;
		}
		else
		{
			collisionY = (_pos.y - (-ReflectorPosY + (-m_reflectorScale * tanO) + _scale)) < 0;
			if (collisionX && collisionY)
			{
				m_testFlg = false;
			}
			return true;
		}
	}
	return false;
}

void BattleScene::CalculateReflectorPos()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_reflectorPos.x += m_moveSpeed;
		m_reflectorPos.x = UNIQUELIBRARY.AdjustmentUpperLimit(m_reflectorPos.x, Width - m_reflectorScale);
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_reflectorPos.x -= m_moveSpeed;
		m_reflectorPos.x = UNIQUELIBRARY.AdjustmentLowerLimit(m_reflectorPos.x, -Width + m_reflectorScale);
	}
}

void BattleScene::CalculateReflectorAng()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_reflectorAng += m_angSpeed;
		m_reflectorAng = UNIQUELIBRARY.AdjustmentUpperLimit(m_reflectorAng, 120.0f);
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_reflectorAng -= m_angSpeed;
		m_reflectorAng = UNIQUELIBRARY.AdjustmentLowerLimit(m_reflectorAng, 60.0f);
	}
}

void BattleScene::CalculateReflectorMatrix()
{
	m_reflectorPos.y = -ReflectorPosY;
	m_reflectorMat = DirectX::XMMatrixTranslation(m_reflectorPos.x, m_reflectorPos.y, 0);
	Math::Matrix rotMat = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_reflectorAng + 90.0f));
	m_reflectorMat = rotMat * m_reflectorMat;
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

void BattleScene::AdjustmentHitAng(float& _standardAng)
{
	if (_standardAng >= 70 && _standardAng <= 90)
	{
		_standardAng = 70.0f;
	}

	if (_standardAng > 90 && _standardAng <= 110)
	{
		_standardAng = 110.0f;
	}

	if (_standardAng >= 250 && _standardAng < 270)
	{
		_standardAng = 250.0f;
	}

	if (_standardAng >= 270 && _standardAng <= 290)
	{
		_standardAng = 290.0f;
	}
}
