#include"Application/Headers.h"

ExplosionEffect::ExplosionEffect()
{
	m_effectData.fileName	= "explosion";
	m_effectData.fileChar	= uR"(Data/Effect/explosion/explosion.efk)";
	m_effectData.timeMax = 120;

	SetEffectData(m_effectData);
}

ExplosionEffect::~ExplosionEffect()
{
}
