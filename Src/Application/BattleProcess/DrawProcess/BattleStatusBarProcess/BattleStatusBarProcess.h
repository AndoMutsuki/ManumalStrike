#pragma once

class BattleStatusBarProcess
{
public:

	BattleStatusBarProcess();

	~BattleStatusBarProcess();

	void Update();

	void Draw();

private:

	KdTexture*		m_battleStatusBarBackTex;
	Math::Matrix	m_m_battleStatusBarBackMat;

	KdTexture*		m_HPGaugeBackTex;
	Math::Matrix	m_HPGaugeBackMat;
	KdTexture*		m_HPGaugeTex;
	Math::Matrix	m_HPGaugeMat;
	KdTexture*		m_HPFrameTex;
	Math::Matrix	m_HPFrameMat;

};