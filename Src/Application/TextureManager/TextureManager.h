#pragma once

class TexManager
{
public:

	static TexManager& GetInstance()
	{
		static TexManager instance;

		return instance;
	}

	~TexManager();

	KdTexture* GetTex(const std::string& _file_name);

private:

	TexManager() {}

	std::map <std::string, KdTexture*>m_texList;

};

#define TEXMANA TexManager::GetInstance()