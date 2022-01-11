#include"Application/Headers.h"

void Scene::Draw2D()//一秒に６０回
{
	m_sceneBase->Draw2D();
	
}

void Scene::Update()//一秒に６０回
{
	m_sceneBase->Update();

}

void Scene::Init()//イニット初期化一番最初に一回だけ
{
	m_sceneBase = new BattleScene;

}

void Scene::Release()	//終了処理
{
	delete spriteFont;
	
	delete m_sceneBase;
}

void Scene::ImGuiUpdate()
{
	IMGUIMANA.Update();
}
