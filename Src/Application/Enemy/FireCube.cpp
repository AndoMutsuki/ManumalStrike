#include"Application/Headers.h"

FireCube::FireCube()
{
	m_enemyData.HP				= 100;
	m_enemyData.scale			= 50.0f;
	m_enemyData.attackTurn		= 2;
	m_enemyData.nowAttackTurn	= 1;
	m_enemyData.attack			= 20.0f;
	m_enemyData.attackType		= enemyAttackType::EXPLOSION;
	m_enemyData.pos				= Math::Vector2::Zero;
	SetEnemyData(m_enemyData);

	m_texData.tex	= TEXMANA.GetTex("Data/Texture/Enemy/fireCube.png");
	m_texData.rec	= { 0,0,200,200 };
	m_texData.color = { 1.0f,1.0f,1.0f,1.0f };
	SetTexData(m_texData);
}

FireCube::~FireCube()
{
}
