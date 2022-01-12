#pragma once

class Hinokokko :public EnemyBase
{
public:

	Hinokokko();

	~Hinokokko();

private:

	enemyData	m_enemyData;
	textureData	m_texData;
};