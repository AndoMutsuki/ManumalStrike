#include"Application/Headers.h"

void Scene::Draw2D()//��b�ɂU�O��
{

	
}

void Scene::Update()//��b�ɂU�O��
{
	int a;

}

void Scene::Init()//�C�j�b�g��������ԍŏ��Ɉ�񂾂�
{


}

void Scene::Release()	//�I������
{
	delete spriteFont;
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// �f�o�b�O�E�B���h�E
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
