#include"Application/Headers.h"

Morumon::Morumon()
{
	m_data.HP				= 10;
	m_data.scale			= 50.0f;
	m_data.attack			= 5.0f;
	m_data.speedRaito		= 1.0f;
	m_data.stamina			= 150;
	m_data.nowStamina		= 0;
	m_data.enemyHitType		= enemyHitType::BOUND;
	m_data.pos				= Math::Vector2::Zero;
	m_data.moveVec			= Math::Vector2::Zero;
	m_data.ang				= 0;
	m_data.nowSpeed			= 0;
	m_data.mat				= Math::Matrix::Identity;

	m_texData.tex	= TEXMANA.GetTex("Data/Texture/Manumal/morumon.png");
	m_texData.rec	= { 0,0,100,100 };
	m_texData.color = { 1.0f,1.0f,1.0f,1.0f };

	SetManumalData(m_data);
	SetTexData(m_texData);
}

Morumon::~Morumon()
{
}