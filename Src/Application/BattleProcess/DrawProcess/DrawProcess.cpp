#include"Application/Headers.h"

DrawProcess::DrawProcess()
{
	m_stageDataBase = new Stage1;
	m_battleStatusBarProcess = new BattleStatusBarProcess;
}

DrawProcess::~DrawProcess()
{
	delete m_stageDataBase;
	delete m_battleStatusBarProcess;
}

void DrawProcess::Update()
{
	m_battleStatusBarProcess->Update();
}

void DrawProcess::Draw()
{
	m_stageDataBase->Draw();

	m_battleStatusBarProcess->Draw();
}

void DrawProcess::SetHPRaito(const float _HPRaito)
{
	m_battleStatusBarProcess->SetHPRaito(_HPRaito);
}
