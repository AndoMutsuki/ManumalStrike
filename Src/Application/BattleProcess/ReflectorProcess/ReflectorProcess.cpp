#include"Application/Headers.h"

using namespace ManumalStrikeNamespace;

ReflectorProcess::ReflectorProcess()
{
	m_tex = TEXMANA.GetTex("Data/Texture/BattleScene/reflector.png");

	m_length = 125.0f;
	m_ang = 90.0f;
	m_pos = Math::Vector2::Zero;
	m_pos.y = -ReflectorPosY;
	m_mat = Math::Matrix::Identity;
}

ReflectorProcess::~ReflectorProcess()
{
}

void ReflectorProcess::Update(const bool _shotPrepareFlg)
{
	if (_shotPrepareFlg)return;

	CalculatePos();
	CalculateAng();
	CalculateMatrix();
}

void ReflectorProcess::Draw() const
{
	UNIQUELIBRARY.Draw2D(m_mat, m_tex, 250, 20, 1.0f);
}

const float ReflectorProcess::GetLength() const
{
	return m_length;
}

const float ReflectorProcess::GetAng() const
{
	return m_ang;
}

const Math::Vector2& ReflectorProcess::GetPos() const
{
	return m_pos;
}

void ReflectorProcess::CalculatePos()
{
	if (GetAsyncKeyState('D') & 0x8000)
	{
		MoveRight();
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		MoveLeft();
	}
}

void ReflectorProcess::MoveRight()
{
	m_pos.x += m_moveSpeed;
	m_pos.x = UNIQUELIBRARY.AdjustmentUpperLimit(m_pos.x, Width - m_length);
}

void ReflectorProcess::MoveLeft()
{
	m_pos.x -= m_moveSpeed;
	m_pos.x = UNIQUELIBRARY.AdjustmentLowerLimit(m_pos.x, -Width + m_length);
}

void ReflectorProcess::CalculateAng()
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		LeanRight();
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		LeanLeft();
	}
}

void ReflectorProcess::LeanRight()
{
	float m_reflectorAngLimit = 120.0f;
	m_ang += m_angSpeed;
	m_ang = UNIQUELIBRARY.AdjustmentUpperLimit(m_ang, m_reflectorAngLimit);
}

void ReflectorProcess::LeanLeft()
{
	float reflectorAngLower = 60.0f;
	m_ang -= m_angSpeed;
	m_ang = UNIQUELIBRARY.AdjustmentLowerLimit(m_ang, reflectorAngLower);
}

void ReflectorProcess::CalculateMatrix()
{
	Math::Matrix rotMat = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_ang + 90.0f));
	Math::Matrix posMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0);
	m_mat = rotMat * posMat;
}
