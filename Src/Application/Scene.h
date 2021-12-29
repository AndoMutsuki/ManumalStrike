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

	//GUI�ŕ\��������ϐ����Ƃ��Ă���
	void SetGUIVariable(const float _ang);
	void SetGUIFlg(const int _flg);

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

	//GUI�\���p�̕ϐ�
	float m_ang;
	int m_flg;

};

#define SCENE Scene::GetInstance()
