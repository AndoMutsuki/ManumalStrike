#include"Application/Headers.h"

using namespace ManumalStrikeNamespace;

Morumon::Morumon()
{
	m_manumalData.m_HP				= 10;
	m_manumalData.m_scale			= 40.0f;
	m_manumalData.m_attack			= 5.0f;
	m_manumalData.m_speed			= 5.0f;
	m_manumalData.m_stamina			= 180;
	//m_manumalData.m_enemyHitType = BOUND;
}

Morumon::~Morumon()
{
}

void Morumon::Update()
{
}

void Morumon::Draw() const
{
}
