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

};

#define SCENE Scene::GetInstance()
