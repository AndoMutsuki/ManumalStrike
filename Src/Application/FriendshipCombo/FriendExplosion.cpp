#include"Application/Headers.h"

FriendExplosion::FriendExplosion()
{
	m_friendshipComboData.damageFixed	= 100;
	m_friendshipComboData.damageRaito	= 5.0f;
	m_friendshipComboData.range			= 200.0f;

	SetFriendshipComboData(m_friendshipComboData);
}

FriendExplosion::~FriendExplosion()
{
}
