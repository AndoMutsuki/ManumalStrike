#include"Application/Headers.h"

StageDataBase::StageDataBase()
{
	m_mat = DirectX::XMMatrixTranslation(0, 30, 0);
}

StageDataBase::~StageDataBase()
{
}

void StageDataBase::Draw() const
{
	UNIQUELIBRARY.Draw2D(m_mat, m_tex, 1280, 660, 1.0f);
}

void StageDataBase::SetStageTexture(KdTexture* _stageTex)
{
	m_tex = _stageTex;
}