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
}

void DrawProcess::Draw()
{
	m_stageDataBase->Draw();

	m_battleStatusBarProcess->Draw();
}