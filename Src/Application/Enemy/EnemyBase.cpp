#include"Application/Headers.h"

using namespace ManumalStrikeNamespace;

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
}

void EnemyBase::Draw()const
{
}

void EnemyBase::SetManumalData(const manumalData& _manumalData)
{
	m_manumalData = _manumalData;
}

const manumalData& EnemyBase::GetManumalData() const
{
	return m_manumalData;
}
