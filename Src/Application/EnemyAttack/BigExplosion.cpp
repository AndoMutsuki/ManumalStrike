#include"Application/Headers.h"

BigExplosion::BigExplosion()
{
	m_enemyAttack.damageFixed	= 20;
	m_enemyAttack.damageRaito	= 7.0f;
	m_enemyAttack.range			= 300.0f;

	SetEnemyAttackData(m_enemyAttack);
}

BigExplosion::~BigExplosion()
{
}
