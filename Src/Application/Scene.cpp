#include"Application/Headers.h"

void Scene::Draw2D()//��b�ɂU�O��
{
	m_sceneBase->Draw2D();
	
}

void Scene::Update()//��b�ɂU�O��
{
	m_sceneBase->Update();

}

void Scene::Init()//�C�j�b�g��������ԍŏ��Ɉ�񂾂�
{
	m_sceneBase = new BattleScene;

}

void Scene::Release()	//�I������
{
	delete spriteFont;
	
	delete m_sceneBase;
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
