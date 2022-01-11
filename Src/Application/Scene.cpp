#include"Application/Headers.h"

void Scene::Draw2D()//ˆê•b‚É‚U‚O‰ñ
{
	m_sceneBase->Draw2D();
	
}

void Scene::Update()//ˆê•b‚É‚U‚O‰ñ
{
	m_sceneBase->Update();

}

void Scene::Init()//ƒCƒjƒbƒg‰Šú‰»ˆê”ÔÅ‰‚Éˆê‰ñ‚¾‚¯
{
	m_sceneBase = new BattleScene;

}

void Scene::Release()	//I—¹ˆ—
{
	delete spriteFont;
	
	delete m_sceneBase;
}

void Scene::ImGuiUpdate()
{
	IMGUIMANA.Update();
}
