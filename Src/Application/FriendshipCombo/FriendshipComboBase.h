#pragma once

class FriendshipComboBase
{
public:

	FriendshipComboBase();

	~FriendshipComboBase();

	void Update(manumalData& _manumalData, std::vector<EnemyBase*>& _enemyList);

	void SetFriendshipComboData(friendshipComboData& _frendshipComboData);

	const int GetDamage()const;

	const float GetRange()const;

private:

	//�U�����������Ă��邩�m�F����
	const bool HitAttack(std::vector<EnemyBase*>::iterator _enemy);

	//�_���[�W��^���鏈��
	void DamageProcess();

	friendshipComboData m_friendshipData;

	manumalData				m_manumalData;
	std::vector<EnemyBase*>	m_enemyList;

	int m_damage;

};