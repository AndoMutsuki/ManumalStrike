#include"Application/Headers.h"

Hinokokko::Hinokokko()
{
	m_enemyData.HP			= 200;
	m_enemyData.scale		= 100.0f;
	m_enemyData.attack		= 30.0f;
	m_enemyData.attackType	= enemyAttackType::EXPLOSION;
	m_enemyData.pos			= Math::Vector2::Zero;
	SetEnemyData(m_enemyData);

	m_texData.tex	= TEXMANA.GetTex("Data/Texture/Manumal/hinokokko.png");
	m_texData.rec	= { 0,0,200,200 };
	m_texData.color = { 1.0f,1.0f,1.0f,1.0f };
	SetTexData(m_texData);
}

Hinokokko::~Hinokokko()
{
}
