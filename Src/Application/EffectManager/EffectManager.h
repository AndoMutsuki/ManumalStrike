#pragma once

class EffectManager
{
public:

	~EffectManager();

	void Init();

	const EffekseerRendererDX11::RendererRef& GetRenderer()const;

	const Effekseer::ManagerRef& GetManager()const;

	//�t���C�E�F�C�g�p�^�[���ŃG�t�F�N�g���Ƃ��Ă���
	const std::shared_ptr<Effekseer::EffectRef> GetEffect(const char16_t* _fileName);

	static EffectManager& GetInstance()
	{
		static EffectManager Instance;
		return Instance;
	}

private:

	EffectManager() {};

	EffekseerRendererDX11::RendererRef m_renderer;
	Effekseer::ManagerRef m_manager;

	std::map<std::string, std::shared_ptr<Effekseer::EffectRef>>m_effectList;
};

#define EFFEKSEER EffectManager::GetInstance()