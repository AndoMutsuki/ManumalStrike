#include"Application/Headers.h"

EnemyAttackBase::EnemyAttackBase()
{
	m_damage = 0;
}

EnemyAttackBase::~EnemyAttackBase()
{
}

void EnemyAttackBase::Update(enemyData& _enemyData, std::vector<ManumalBase*>& _manumalList)
{
	m_enemyData = _enemyData;
	m_manumalList = _manumalList;

	m_damage = 0;

	for (auto iter = _manumalList.begin(); iter != _manumalList.end(); ++iter)
	{
		if (!HitAttack(iter)) continue;

		DamageProcess();
	}

	_enemyData = m_enemyData;
	_manumalList = m_manumalList;
}

void EnemyAttackBase::SetEnemyAttackData(enemyAttackData& _enemyAttackData)
{
	m_enemyAttackData = _enemyAttackData;
}

const int EnemyAttackBase::GetDamage()const
{
	return m_damage;
}

const float EnemyAttackBase::GetRange() const
{
	return m_enemyAttackData.range;
}

const bool EnemyAttackBase::HitAttack(std::vector<ManumalBase*>::iterator _manumal)
{
	Math::Vector2 betweenVec	= m_enemyData.pos - (*_manumal)->GetManumalData().pos;	//ŠÔ‚ÌƒxƒNƒgƒ‹
	float betweenLength			= betweenVec.Length() - (*_manumal)->GetManumalData().scale;	//ŠÔ‚Ì’·‚³
	return betweenLength < m_enemyAttackData.range ? true : false;
}

void EnemyAttackBase::DamageProcess()
{
	int damage = m_enemyAttackData.damageFixed + (int)(m_enemyAttackData.damageRaito * m_enemyData.attack);
	m_damage = damage;
}
