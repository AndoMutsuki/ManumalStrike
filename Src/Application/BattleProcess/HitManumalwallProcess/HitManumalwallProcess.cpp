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

	//�����o�ϐ��ɕϊ�����
	m_manumalData = _manumalData;

	bool hitSideWall = (Width - m_manumalData.scale) < abs(m_manumalData.pos.x);	//�ǂ̉��ɓ������Ă��邩
	if (hitSideWall)
	{
		m_hitWallFlg = true;

		HitSideWallProcess();
	}

	bool hitTopWall		= (Top - m_manumalData.scale) < m_manumalData.pos.y;	//�ǂ̏�ɓ������Ă��邩
	bool hitBottomWall	= (Bottom + m_manumalData.scale) > m_manumalData.pos.y;	//�ǂ̉��ɓ������Ă��邩

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

	//���߂��f�[�^���i�[����
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
