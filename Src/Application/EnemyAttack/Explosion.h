#pragma once

class Explosion :public EnemyAttackBase
{
public:

	Explosion();

	~Explosion();

private:

	enemyAttackData m_enemyAttack;
	
};