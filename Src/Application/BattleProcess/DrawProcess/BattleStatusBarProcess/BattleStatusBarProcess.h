#pragma once

class BattleStatusBarProcess
{
public:

	BattleStatusBarProcess();

	~BattleStatusBarProcess();

	void Update();

	void Draw();

	void SetHPRaito(const float _HPRaito);

private:

	void HPProcess();	//HPÉoÅ[ÇÃèàóù

	KdTexture*		m_battleStatusBarBackTex;
	Math::Matrix	m_m_battleStatusBarBackMat;

	KdTexture*		m_HPGaugeBackTex;
	Math::Matrix	m_HPGaugeBackMat;

	KdTexture*		m_HPGaugeTex;
	const float		m_HPGaugeMatXMax = -290;
	Math::Matrix	m_HPGaugeMat;
	float			m_HPRaito;
	const float		m_HPGaugeWidthMax = 536;
	float			m_HPGaugeWidth;

	KdTexture*		m_HPFrameTex;
	Math::Matrix	m_HPFrameMat;

};