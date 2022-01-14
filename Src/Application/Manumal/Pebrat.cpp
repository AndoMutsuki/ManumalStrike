#include"Application/Headers.h"

Pebrat::Pebrat()
{
	m_data.HP				= 450;
	m_data.scale			= 55.0f;
	m_data.attack			= 7.0f;
	m_data.speedRaito		= 0.8f;
	m_data.stamina			= 180;
	m_data.nowStamina		= 0;
	m_data.enemyHitType		= enemyHitType::BOUND;
	m_data.pos				= Math::Vector2::Zero;
	m_data.moveVec			= Math::Vector2::Zero;
	m_data.ang				= 0;
	m_data.nowSpeed			= 0;
	m_data.mat				= Math::Matrix::Identity;
	m_data.frendshipType	= frendshipComboType::EXPLOSION;
	m_data.friendFinishFlg			= false;

	m_texData.tex		= TEXMANA.GetTex("Data/Texture/Manumal/pebrat.png");
	m_texData.rec		= { 0,0,100,100 };
	m_texData.color		= { 1.0f,1.0f,1.0f,1.0f };

	SetManumalData(m_data);
	SetTexData(m_texData);
}

Pebrat::~Pebrat()
{
}
