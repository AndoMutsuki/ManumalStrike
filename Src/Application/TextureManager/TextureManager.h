#pragma once

class TexManager
{
public:
	~TexManager();

	KdTexture* GetTex(const std::string& _file_name);

	static TexManager& GetInstance()
	{
		static TexManager instance;

		return instance;
	}

private:
	TexManager() {}

	std::map <std::string, KdTexture*>m_texList;

};

#define TEXMANA TexManager::GetInstance()