#include"Application/Headers.h"

Explosion::Explosion()
{
	m_enemyAttack.damageFixed	= 10;
	m_enemyAttack.damageRaito	= 5.0f;
	m_enemyAttack.range			= 100.0f;

	SetEnemyAttackData(m_enemyAttack);
}

Explosion::~Explosion()
{
}
