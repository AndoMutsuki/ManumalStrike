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
	IMGUIMANA.Update();
}
