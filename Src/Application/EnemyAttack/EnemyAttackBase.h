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

	//�U�����������Ă��邩�m�F����
	const bool HitAttack(std::vector<ManumalBase*>::iterator _manumal);

	//�_���[�W��^���鏈��
	void DamageProcess();

	enemyAttackData m_enemyAttackData;

	enemyData					m_enemyData;
	std::vector<ManumalBase*>	m_manumalList;

	int m_damage;
};