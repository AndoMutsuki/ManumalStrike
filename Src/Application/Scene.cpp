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
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d\nAng : %f", APP.m_fps, m_ang);
	}
	ImGui::End();
}

void Scene::SetGUIVariable(const float _ang)
{
	m_ang = _ang;
}
