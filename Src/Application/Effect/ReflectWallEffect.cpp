#include"Application/Headers.h"

ReflectWallEffect::ReflectWallEffect()
{
	m_effectData.fileName	= "reflectWall";
	m_effectData.fileChar	= uR"(Data/Effect/reflectWall/reflectWall.efk)";
	m_effectData.timeMax	= 30;

	SetEffectData(m_effectData);
}

ReflectWallEffect::~ReflectWallEffect()
{
}
