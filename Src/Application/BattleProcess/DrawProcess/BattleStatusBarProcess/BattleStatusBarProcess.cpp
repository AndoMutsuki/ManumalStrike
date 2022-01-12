#include"Application/Headers.h"

BattleStatusBarProcess::BattleStatusBarProcess()
{
	m_battleStatusBarBackTex	= TEXMANA.GetTex("Data/Texture/BattleScene/battleStatusBarBack.png");
	m_m_battleStatusBarBackMat	= DirectX::XMMatrixTranslation(0, -330, 0);

	m_HPGaugeBackTex = TEXMANA.GetTex("Data/Texture/BattleScene/HPGaugeBack.png");
	m_HPGaugeBackMat = DirectX::XMMatrixTranslation(-290, -330, 0);

	m_HPGaugeTex	= TEXMANA.GetTex("Data/Texture/BattleScene/HPGauge.png");
	m_HPGaugeMat	= DirectX::XMMatrixTranslation(m_HPGaugeMatXMax, -330, 0);
	m_HPRaito		= 0;
	m_HPGaugeWidth	= m_HPGaugeWidthMax;

	m_HPFrameTex = TEXMANA.GetTex("Data/Texture/BattleScene/HPFrame.png");
	m_HPFrameMat = DirectX::XMMatrixTranslation(-330, -330, 0);
}

BattleStatusBarProcess::~BattleStatusBarProcess()
{
}

void BattleStatusBarProcess::Update()
{
	HPProcess();
}

void BattleStatusBarProcess::Draw()
{
	UNIQUELIBRARY.Draw2D(m_m_battleStatusBarBackMat, m_battleStatusBarBackTex, 1280, 60, 1.0f);

	UNIQUELIBRARY.Draw2D(m_HPGaugeBackMat, m_HPGaugeBackTex, 536, 60, 1.0f);

	UNIQUELIBRARY.Draw2D(m_HPGaugeMat, m_HPGaugeTex, (int)m_HPGaugeWidth, 60, 1.0f);

	UNIQUELIBRARY.Draw2D(m_HPFrameMat, m_HPFrameTex, 640, 60, 1.0f);
}

void BattleStatusBarProcess::SetHPRaito(const float _HPRaito)
{
	m_HPRaito = _HPRaito;
}

void BattleStatusBarProcess::HPProcess()
{
	//HPゲージの幅
	m_HPGaugeWidth = m_HPGaugeWidthMax * m_HPRaito;

	//HPゲージの位置の調整
	m_HPGaugeMat._41 = m_HPGaugeMatXMax - ((m_HPGaugeWidthMax - m_HPGaugeWidth) / 2);
}
