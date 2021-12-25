#include"Application/Headers.h"

void Scene::Draw2D()//一秒に６０回
{

	
}

void Scene::Update()//一秒に６０回
{
	int a;

}

void Scene::Init()//イニット初期化一番最初に一回だけ
{


}

void Scene::Release()	//終了処理
{
	delete spriteFont;
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
