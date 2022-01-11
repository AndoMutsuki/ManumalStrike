#pragma once

class Scene
{
public:

	// �����ݒ�
	void Init();

	// ���
	void Release();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw2D();

	// GUI����
	void ImGuiUpdate();

	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}

private:

	//�ėp�s��
	Math::Matrix matrix;

	DirectX::SpriteBatch* spriteBatch;
	DirectX::SpriteFont* spriteFont;

	Scene() {}

	SceneBase* m_sceneBase;

};

#define SCENE Scene::GetInstance()
