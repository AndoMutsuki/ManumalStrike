#include"Application/Headers.h"

using namespace ManumalStrikeNamespace;

Morumon::Morumon()
{
	m_data.HP				= 10;
	m_data.scale			= 40.0f;
	m_data.attack			= 5.0f;
	m_data.speed			= 5.0f;
	m_data.stamina			= 180;
	m_data.enemyHitType		= enemyHitType::BOUND;
	m_data.pos				= Math::Vector2::Zero;
	m_data.moveVec			= Math::Vector2::Zero;
	m_data.ang				= 0;
	m_data.power			= 0;
	m_data.mat				= Math::Matrix::Identity;

	m_texData.tex	= TEXMANA.GetTex("Data/Texture/Manumal/test.jpg");
	m_texData.rec	= { 0,0,800,800 };
	m_texData.color = { 1.0f,1.0f,1.0f,1.0f };

	SetManumalData(m_data);
	SetTexData(m_texData);
}

Morumon::~Morumon()
{
}