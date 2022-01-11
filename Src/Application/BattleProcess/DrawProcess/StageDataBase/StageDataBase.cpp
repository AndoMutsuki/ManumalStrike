#include"Application/Headers.h"

StageDataBase::StageDataBase()
{
}

StageDataBase::~StageDataBase()
{
}

void StageDataBase::Draw() const
{
	UNIQUELIBRARY.Draw2D(Math::Matrix::Identity, m_tex, 1280, 720, 1.0f);
}

void StageDataBase::SetStageTexture(KdTexture* _stageTex)
{
	m_tex = _stageTex;
}
