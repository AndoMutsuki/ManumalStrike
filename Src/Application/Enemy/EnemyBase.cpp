#include"Application/Headers.h"

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Draw()
{
	float texMagnification	= CalculateTexMagnification();	//‰æ‘œ‚ÌŠg‘å—¦
	Math::Matrix scaleMat	= DirectX::XMMatrixScaling(texMagnification, texMagnification, texMagnification);
	Math::Matrix posMat		= DirectX::XMMatrixTranslation(m_enemyData.pos.x, m_enemyData.pos.y, 0);

	UNIQUELIBRARY.Draw2D(scaleMat * posMat, m_texData.tex, &m_texData.rec, &m_texData.color);
}

void EnemyBase::SetEnemyPos(const Math::Vector2& _pos)
{
	m_enemyData.pos = _pos;
}

void EnemyBase::SetDamage(const int _damage)
{
	m_enemyData.HP -= _damage;
}

const bool EnemyBase::GetAliveFlg()
{
	return m_enemyData.HP > 0 ? true : false;
}

void EnemyBase::SetEnemyData(const enemyData& _enemyData)
{
	m_enemyData = _enemyData;
}

const enemyData& EnemyBase::GetEnemyData() const
{
	return m_enemyData;
}

enemyData& EnemyBase::GetEnemyDataKinetic()
{
	return m_enemyData;
}

void EnemyBase::SetTexData(const textureData& _texData)
{
	m_texData = _texData;
}

const float EnemyBase::CalculateTexMagnification()
{
	float texMagnification = (float)(m_enemyData.scale * 2) / (float)m_texData.rec.width;	//‰æ‘œ‚ÌŠg‘å—¦
	return texMagnification;
}
