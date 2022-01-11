#include"Application/Headers.h"

HitManumalWallProcess::HitManumalWallProcess()
{
	m_hitWallFlg = false;
}

HitManumalWallProcess::~HitManumalWallProcess()
{
}

void HitManumalWallProcess::Update(manumalData& _manumalData)
{
	m_hitWallFlg = false;

	//メンバ変数に変換する
	m_manumalData = _manumalData;

	bool hitSideWall = (Width - m_manumalData.scale) < abs(m_manumalData.pos.x);	//壁の横に当たっているか
	if (hitSideWall)
	{
		m_hitWallFlg = true;

		HitSideWallProcess();
	}

	bool hitTopWall		= (Top - m_manumalData.scale) < m_manumalData.pos.y;	//壁の上に当たっているか
	bool hitBottomWall	= (Bottom + m_manumalData.scale) > m_manumalData.pos.y;	//壁の下に当たっているか

	if (hitTopWall)
	{
		m_hitWallFlg = true;
		
		HitTopWallProcess();
	}

	if (hitBottomWall)
	{
		m_hitWallFlg = true;

		HitBottomWallProcess();
	}

	//求めたデータを格納する
	_manumalData = m_manumalData;
}

const bool HitManumalWallProcess::GetHitWallFlg() const
{
	return m_hitWallFlg;
}

void HitManumalWallProcess::HitSideWallProcess()
{
	m_manumalData.pos.x = UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.x, (float)(Width - m_manumalData.scale));
	m_manumalData.ang	= UNIQUELIBRARY.CalculateReflectAng(m_manumalData.ang, 0);
}

void HitManumalWallProcess::HitTopWallProcess()
{
	m_manumalData.pos.y = UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.y, (float)(Top - m_manumalData.scale));
	m_manumalData.ang	= UNIQUELIBRARY.CalculateReflectAng(m_manumalData.ang, 90);
}

void HitManumalWallProcess::HitBottomWallProcess()
{
	m_manumalData.pos.y = UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.y, (float)(Bottom + m_manumalData.scale));
	m_manumalData.ang	= UNIQUELIBRARY.CalculateReflectAng(m_manumalData.ang, 90);
}
