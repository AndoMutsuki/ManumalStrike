#include"Application/Headers.h"

CalculateHP::CalculateHP()
{
	m_HPMax		= 0;
	m_damage	= 0;
	m_HPRaito	= 0;
}

CalculateHP::~CalculateHP()
{
}

void CalculateHP::Update()
{
	m_HPRaito = (float)(m_HPMax - m_damage) / (float)m_HPMax;
}

void CalculateHP::SetHPMax(const int _HPMax)
{
	m_HPMax = _HPMax;
}

void CalculateHP::SetDamage(const int _damage)
{
	m_damage += _damage;
}

const float CalculateHP::GetHPRaito() const
{
	return m_HPRaito;
}

const bool CalculateHP::GetAliveFlg()
{
	if (m_HPRaito < 0)
	{
		return false;
	}
	
	return true;
}
