#pragma once

class EffectManager
{
public:

	~EffectManager();

	void Init();

	static EffectManager& GetInstance()
	{
		static EffectManager Instance;
		return Instance;
	}

	EffekseerRendererDX11::RendererRef m_renderer;
	Effekseer::ManagerRef m_manager;

private:

	EffectManager() {};

};

#define EFFEKSEER EffectManager::GetInstance()