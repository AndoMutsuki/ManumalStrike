#include"Application/Headers.h"

BattleStatusBarProcess::BattleStatusBarProcess()
{
	m_battleStatusBarBackTex	= TEXMANA.GetTex("Data/Texture/BattleScene/battleStatusBarBack.png");
	m_m_battleStatusBarBackMat	= DirectX::XMMatrixTranslation(0, -330, 0);

	m_HPGaugeBackTex = TEXMANA.GetTex("Data/Texture/BattleScene/HPGaugeBack.png");
	m_HPGaugeBackMat = DirectX::XMMatrixTranslation(-290, -330, 0);
	m_HPGaugeTex = TEXMANA.GetTex("Data/Texture/BattleScene/HPGauge.png");
	m_HPGaugeMat = DirectX::XMMatrixTranslation(-290, -330, 0);
	m_HPFrameTex = TEXMANA.GetTex("Data/Texture/BattleScene/HPFrame.png");
	m_HPFrameMat = DirectX::XMMatrixTranslation(-330, -330, 0);
}

BattleStatusBarProcess::~BattleStatusBarProcess()
{
}

void BattleStatusBarProcess::Update()
{
}

void BattleStatusBarProcess::Draw()
{
	UNIQUELIBRARY.Draw2D(m_m_battleStatusBarBackMat, m_battleStatusBarBackTex, 1280, 60, 1.0f);

	UNIQUELIBRARY.Draw2D(m_HPGaugeBackMat, m_HPGaugeBackTex, 536, 60, 1.0f);
	UNIQUELIBRARY.Draw2D(m_HPGaugeMat, m_HPGaugeTex, 536, 60, 1.0f);
	UNIQUELIBRARY.Draw2D(m_HPFrameMat, m_HPFrameTex, 640, 60, 1.0f);
}
