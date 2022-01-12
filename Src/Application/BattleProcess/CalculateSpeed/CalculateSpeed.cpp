#include"Application/Headers.h"

CalculateSpeed::CalculateSpeed()
{
	m_decelerationFlg = false;
}

CalculateSpeed::~CalculateSpeed()
{
}

void CalculateSpeed::Update(manumalData& _manumalData)
{
	m_manumalData = _manumalData;

	CalculateStamina();

	if (m_decelerationFlg)
	{
		CalculateDeceleration();
	}

	_manumalData = m_manumalData;
}

void CalculateSpeed::CalculateStamina()
{
	if (m_manumalData.nowStamina > 0)
	{
		m_manumalData.nowStamina--;
		m_decelerationFlg = false;
		return;
	}

	m_decelerationFlg = true;
}

void CalculateSpeed::CalculateDeceleration()
{
	if (m_manumalData.nowSpeed <= 0)return;

	m_manumalData.nowSpeed -= 0.3f;
	m_manumalData.nowSpeed = UNIQUELIBRARY.AdjustmentLowerLimit(m_manumalData.nowSpeed, 0.0f);
}
