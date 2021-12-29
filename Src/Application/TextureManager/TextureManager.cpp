#include"Application/Headers.h"

TexManager::~TexManager()
{
	for (auto itr = m_texList.begin(); itr != m_texList.end(); ++itr)
	{
		(itr->second)->Release();
		delete (itr->second);
	}

	m_texList.clear();
}

KdTexture* TexManager::GetTex(const std::string& _file_name)
{
	KdTexture* tmpTex;

	if (m_texList.find(_file_name) == m_texList.end())
	{
		tmpTex = new KdTexture;
		tmpTex->Load(_file_name);

		m_texList[_file_name] = tmpTex;
	}
	else
	{
		tmpTex = m_texList[_file_name];
	}

	return tmpTex;
}