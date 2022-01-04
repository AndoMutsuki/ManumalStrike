#include"Application/Headers.h"

using namespace ManumalStrikeNamespace;

BattleScene::BattleScene()
{
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

	m_reflectorScale = 125.0f;
	m_reflectorAng = 90;
	m_reflectorPos = Math::Vector2::Zero;
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

	CalculateManumalMoveVec(m_moveVec1, m_ang1);
	m_rec1 = { 0,0,800,800 };
	m_color1 = { 1.0f,1.0f,1.0f,1.0f };

	m_tex = TEXMANA.GetTex("Data/Texture/Manumal/test.jpg");
	m_reflectorTex = TEXMANA.GetTex("Data/Texture/BattleScene/reflector.png");

	//�}�E�X
	m_baseMousePos = { 1280 / 2, 720 / 2 };
	ScreenToClient(APP.m_window.GetWndHandle(), &m_mousePos);
	SetCursorPos(m_baseMousePos.x, m_baseMousePos.y);
}

BattleScene::~BattleScene()
{
}

void BattleScene::Update()
{
	ProcessMouse();
	FirstShot();

	CalculateReflectorPos();
	CalculateReflectorAng();
	CalculateReflectorMatrix();

	ManumalMutualCollision();
	ManumalEnemyCollision();

	CalculateManumlPos(m_pos1, m_moveVec1, m_ang1, m_power1, m_scale);
	CalculateManumlPos(m_pos2, m_moveVec2, m_ang2, m_power2, m_scale);
	CalculateManumlPos(m_pos3, m_moveVec3, m_ang3, m_power3, m_scale);
	m_mat1 = DirectX::XMMatrixTranslation(m_pos1.x, m_pos1.y, 0);
	m_mat2 = DirectX::XMMatrixTranslation(m_pos2.x, m_pos2.y, 0);
	m_mat3 = DirectX::XMMatrixTranslation(m_pos3.x, m_pos3.y, 0);
}

void BattleScene::Draw2D()
{
	SHADER.m_spriteShader.Begin();

	Math::Matrix scaleMat = DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f);
	m_mat1 = scaleMat * m_mat1;
	UNIQUELIBRARY.Draw2D(m_mat1, m_tex, &m_rec1, &m_color1);
	m_mat2 = scaleMat * m_mat2;
	UNIQUELIBRARY.Draw2D(m_mat2, m_tex, &m_rec1, &m_color1);
	m_mat3 = scaleMat * m_mat3;
	UNIQUELIBRARY.Draw2D(m_mat3, m_tex, &m_rec1, &m_color1);

	UNIQUELIBRARY.Draw2D(m_reflectorMat, m_reflectorTex, 250, 20, 1.0f);

	bool arrowMinOverFlg = m_arrowScale != 0;
	if (m_arrowFlg && arrowMinOverFlg)
	{
		UNIQUELIBRARY.Draw2D(m_arrowMat, m_arrowTex, 200, 1000, 0.8f);
	}

	SHADER.m_spriteShader.End();
}

void BattleScene::ProcessMouse()
{
	GetCursorPos(&m_mousePos);
	ScreenToClient(APP.m_window.GetWndHandle(), &m_mousePos);

	m_mousePos.x -= 640;
	m_mousePos.y = -m_mousePos.y + 360;
}

void BattleScene::FirstShot()
{
	Math::Vector2 nowMousePos = { (float)m_mousePos.x,(float)m_mousePos.y };
	m_arrowScale = UNIQUELIBRARY.GetVecLength(Math::Vector2{ nowMousePos.x,nowMousePos.y }, m_firstArrowPos) / 10.0f;
	if (m_arrowScale < m_arrowScaleMin)
	{
		m_arrowScale = 0;
	}
	else
	{
		m_arrowScale = UNIQUELIBRARY.AdjustmentUpperLimit(m_arrowScale, m_arrowScaleMax) + m_arrowScaleFixed;
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		float manumalMouseLength = UNIQUELIBRARY.GetVecLength(m_pos1, Math::Vector2{ nowMousePos.x,nowMousePos.y });
		if (manumalMouseLength < m_scale)
		{
			if (m_firstArrowPos == Math::Vector2::Zero)
			{
				m_arrowFlg = true;
				m_firstArrowPos = Math::Vector2{ nowMousePos.x,nowMousePos.y };
			}
		}
	}
	else
	{
		if (m_firstArrowPos != Math::Vector2::Zero)
		{
			m_arrowFlg = false;
			m_power1 = m_arrowScale;
			float arrowAng = UNIQUELIBRARY.GetVecAng(m_firstArrowPos, Math::Vector2{ nowMousePos.x,nowMousePos.y });
			m_ang1 = -m_arrowAng;
			CalculateManumalMoveVec(m_moveVec1, m_ang1);
		}
		m_firstArrowPos = Math::Vector2::Zero;
	}

	bool arrowMinOverFlg = m_arrowScale != 0;
	if (m_arrowFlg && arrowMinOverFlg)
	{
		m_arrowAng = UNIQUELIBRARY.GetVecAng(m_firstArrowPos, Math::Vector2{ nowMousePos.x,nowMousePos.y });
		Math::Matrix scaleMat = DirectX::XMMatrixScaling(1.0f, (m_arrowScale - m_arrowScaleFixed) / m_arrowScaleMax, 0);
		Math::Matrix rotMat = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(-m_arrowAng ));
		Math::Matrix transMat = DirectX::XMMatrixTranslation(m_pos1.x, m_pos1.y, 0);
		m_arrowMat = scaleMat * rotMat * transMat;
	}
}

void BattleScene::CalculateManumlPos(Math::Vector2& _pos, Math::Vector2& _vec, float& _ang, float& _power, const float& _scale)
{
	//�}�j���}������������
	_pos += _vec * _power;

	//���˔Œ��˕Ԃ鏈��
	if (CalculateHitReflector(_pos, _ang, _scale))
	{
		CalculateManumalMoveVec(_vec, _ang);
	}

	//�ǂŒ��˕Ԃ鏈��
	if (CalculateHitWall(_pos, _ang, _scale))
	{
		CalculateManumalMoveVec(_vec, _ang);
	}
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
	//���˔�薾�炩�ɏ�ɂ���ꍇ�͑������^�[��
	if (_pos.y > -150) return false;

	//x���W�����˔ɓ������Ă��邩
	float relativePos = _pos.x - m_reflectorPos.x;	//�}�j���}���̑��ΓI�Ȉʒu
	float cosO = cos(DirectX::XMConvertToRadians(m_reflectorAng + 90));
	bool hitReflectorX = abs(relativePos) - abs(m_reflectorScale * cosO) > _scale;
	if (hitReflectorX) return false;

	//y���W�����˔ɓ������Ă��邩
	float tanO = tan(DirectX::XMConvertToRadians(m_reflectorAng + 90));
	bool hitReflectorY = abs(abs(_pos.y) - abs(-ReflectorPosY + (relativePos * tanO))) > _scale;
	if (hitReflectorY) return false;

	//���˂̌v�Z
	bool hitReflectorTopFlg = _pos.y > (-ReflectorPosY + (relativePos * tanO));
	if (hitReflectorTopFlg)
	{
		CalculateHitPos(_pos.y, (-ReflectorPosY + (relativePos * tanO) + _scale));
		CalculateHitAng(_ang, m_reflectorAng);
		AdjustmentHitAng(_ang);
	}
	else
	{
		CalculateHitPos(_pos.y, (-ReflectorPosY + (relativePos * tanO) - _scale));
		CalculateHitAng(_ang, m_reflectorAng + 90);
		AdjustmentHitAng(_ang);

		if (m_reflectorAng > 90)
		{
			_ang = UNIQUELIBRARY.AdjustmentLowerLimit(_ang, 200.0f);
			CalculateHitPos(_pos.x, (m_reflectorScale * cosO  - m_reflectorPos.x - _scale));
		}
		else if (m_reflectorAng < 90)
		{
			_ang = UNIQUELIBRARY.AdjustmentUpperLimit(_ang, 160.0f);
			CalculateHitPos(_pos.x, (m_reflectorScale * cosO + m_reflectorPos.x - _scale));
		}
		else
		{
			if (_pos.x > m_reflectorPos.x)
			{
				_ang = UNIQUELIBRARY.AdjustmentLowerLimit(_ang, 200.0f);
				CalculateHitPos(_pos.x, (m_reflectorScale * cosO - m_reflectorPos.x - _scale));
			}
			else
			{
				_ang = UNIQUELIBRARY.AdjustmentUpperLimit(_ang, 160.0f);
				CalculateHitPos(_pos.x, (m_reflectorScale * cosO + m_reflectorPos.x - _scale));
			}
		}
	}

	return true;
}

void BattleScene::CalculateReflectorPos()
{
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_reflectorPos.x += m_moveSpeed;
		m_reflectorPos.x = UNIQUELIBRARY.AdjustmentUpperLimit(m_reflectorPos.x, Width - m_reflectorScale);
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_reflectorPos.x -= m_moveSpeed;
		m_reflectorPos.x = UNIQUELIBRARY.AdjustmentLowerLimit(m_reflectorPos.x, -Width + m_reflectorScale);
	}
}

void BattleScene::CalculateReflectorAng()
{
	if (m_arrowFlg)return;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_reflectorAng += m_angSpeed;
		m_reflectorAng = UNIQUELIBRARY.AdjustmentUpperLimit(m_reflectorAng, 120.0f);
	}

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
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

void BattleScene::ManumalMutualCollision()
{
	if (UNIQUELIBRARY.GetVecLength(m_pos1, m_pos2) > m_scale + m_scale)return;

	Math::Vector2 betweenVec = m_pos2 - m_pos1;
	betweenVec.Normalize();
	m_pos2 = m_pos1 + betweenVec * (m_scale + m_scale);
	m_ang2 = -UNIQUELIBRARY.GetVecAng(m_pos2, m_pos1);
	//m_power2 = 50;
	CalculateManumalMoveVec(m_moveVec2, m_ang2);
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

	CalculateManumalMoveVec(m_moveVec1, m_ang1);
}
