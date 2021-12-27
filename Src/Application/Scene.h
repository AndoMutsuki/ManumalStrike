#pragma once

class Scene
{
public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	//GUIで表示させる変数をとってくる
	void SetGUIVariable(const float _ang);

	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}

private:

	//汎用行列
	Math::Matrix matrix;

	DirectX::SpriteBatch* spriteBatch;
	DirectX::SpriteFont* spriteFont;

	Scene() {}

	SceneBase* m_sceneBase;

	//GUI表示用の変数
	float m_ang;

};

#define SCENE Scene::GetInstance()
