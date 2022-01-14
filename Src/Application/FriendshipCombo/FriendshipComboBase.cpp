#include"Application/Headers.h"

FriendshipComboBase::FriendshipComboBase()
{
	m_damage = 0;
}

FriendshipComboBase::~FriendshipComboBase()
{
}

void FriendshipComboBase::Update(manumalData& _manumalData, std::vector<EnemyBase*>& _enemyList)
{
	m_manumalData = _manumalData;
	m_enemyList = _enemyList;

	m_damage = 0;

	for (auto iter = m_enemyList.begin(); iter != m_enemyList.end(); ++iter)
	{
		if (!HitAttack(iter)) continue;

		DamageProcess();

		(*iter)->SetDamage(m_damage);
	}

	_manumalData = m_manumalData;
	_enemyList = m_enemyList;
}

void FriendshipComboBase::SetFriendshipComboData(friendshipComboData& _frendshipComboData)
{
	m_friendshipData = _frendshipComboData;
}

const int FriendshipComboBase::GetDamage() const
{
	return m_damage;
}

const float FriendshipComboBase::GetRange() const
{
	return m_friendshipData.range;
}

const bool FriendshipComboBase::HitAttack(std::vector<EnemyBase*>::iterator _enemy)
{
	Math::Vector2 betweenVec = m_manumalData.pos - (*_enemy)->GetEnemyData().pos;	//ŠÔ‚ÌƒxƒNƒgƒ‹
	float betweenLength = betweenVec.Length() - (*_enemy)->GetEnemyData().scale;	//ŠÔ‚Ì’·‚³
	return betweenLength < m_friendshipData.range ? true : false;
}

void FriendshipComboBase::DamageProcess()
{
	int damage = m_friendshipData.damageFixed + (int)(m_friendshipData.damageRaito * m_manumalData.attack);
	m_damage = damage;
}