#pragma once

class EnemyAttackBase
{
public:

	EnemyAttackBase();

	virtual ~EnemyAttackBase();

	void Update(enemyData& _enemyData, std::vector<ManumalBase*>& _manumalList);

	void SetEnemyAttackData(enemyAttackData& _enemyAttackData);

	const int GetDamage()const;

	const float GetRange()const;

private:

	//攻撃が当たっているか確認する
	const bool HitAttack(std::vector<ManumalBase*>::iterator _manumal);

	//ダメージを与える処理
	void DamageProcess();

	enemyAttackData m_enemyAttackData;

	enemyData					m_enemyData;
	std::vector<ManumalBase*>	m_manumalList;

	int m_damage;
};