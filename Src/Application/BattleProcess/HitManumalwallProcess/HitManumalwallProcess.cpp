#include"Application/Headers.h"

HitManumalwallProcess::HitManumalwallProcess()
{
	m_hitWallFlg = false;
}

HitManumalwallProcess::~HitManumalwallProcess()
{
}

void HitManumalwallProcess::Update(manumalData& _manumalData)
{
	m_hitWallFlg = false;

	m_manumalData = _manumalData;

	bool hitSideWall = (Width - m_manumalData.scale) < abs(m_manumalData.pos.x);	//•Ç‚Ì‰¡‚É“–‚½‚Á‚Ä‚¢‚é‚©
	if (hitSideWall)
	{
		m_hitWallFlg = true;

		HitSideWallProcess();
	}

	bool hitLengthWall = (Height - m_manumalData.scale) < abs(m_manumalData.pos.y);	//•Ç‚Ìã‚Æ‰º‚É“–‚½‚Á‚Ä‚¢‚é‚©
	if (hitLengthWall)
	{
		m_hitWallFlg = true;
		
		HitLengthWallProcess();
	}

	_manumalData = m_manumalData;
}

const bool HitManumalwallProcess::GetHitWallFlg() const
{
	return m_hitWallFlg;
}

void HitManumalwallProcess::HitSideWallProcess()
{
	m_manumalData.pos.x = UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.x, (float)(Width - m_manumalData.scale));
	m_manumalData.ang = UNIQUELIBRARY.CalculateReflectAng(m_manumalData.ang, 0);
}

void HitManumalwallProcess::HitLengthWallProcess()
{
	m_manumalData.pos.y = UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.y, (float)(Height - m_manumalData.scale));
	m_manumalData.ang = UNIQUELIBRARY.CalculateReflectAng(m_manumalData.ang, 90);
}
