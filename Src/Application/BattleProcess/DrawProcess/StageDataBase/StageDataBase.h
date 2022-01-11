#pragma once

class StageDataBase
{
public:

	StageDataBase();

	~StageDataBase();

	void Draw()const;

	void SetStageTexture(KdTexture* _stageTex);

private:

	KdTexture*		m_tex;
	Math::Matrix	m_mat;
};