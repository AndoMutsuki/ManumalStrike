#include"Application/Headers.h"

using namespace ManumalStrikeNamespace;

ManumalBase::ManumalBase()
{
}

ManumalBase::~ManumalBase()
{
}

void ManumalBase::Draw()
{
	float texMagnification = CalculateTexMagnification();
	Math::Matrix scaleMat = DirectX::XMMatrixScaling(texMagnification, texMagnification, texMagnification);
	UNIQUELIBRARY.Draw2D(scaleMat * m_manumalData.mat, m_texData.tex, &m_texData.rec, &m_texData.color);
}

const float ManumalBase::CalculateTexMagnification()
{
	float texMagnification = (float)(m_manumalData.scale * 2) / (float)m_texData.rec.width;
	return texMagnification;
}

void ManumalBase::CalculateMatrix()
{
	m_manumalData.mat = DirectX::XMMatrixTranslation(m_manumalData.pos.x, m_manumalData.pos.y, 0);
}

void ManumalBase::CalculateMoveVec()
{
	Math::Vector2 moveVec = DirectX::XMVector2TransformNormal({ 0,1 }, DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_manumalData.ang)));
	moveVec.Normalize();
	m_manumalData.moveVec = moveVec;
}

void ManumalBase::MoveProcess()
{
	m_manumalData.pos += m_manumalData.moveVec * m_manumalData.power;
}

void ManumalBase::SetManumalData(const manumalData& _manumalData)
{
	m_manumalData = _manumalData;
}

const manumalData& ManumalBase::GetManumalData() const
{
	return m_manumalData;
}

manumalData& ManumalBase::GetManumalDataKinetic()
{
	return m_manumalData;
}

void ManumalBase::SetTexData(const manumalTextureData& _texData)
{
	m_texData = _texData;
}

void ManumalBase::SetPos(const Math::Vector2& _pos)
{
	m_manumalData.pos = _pos;
}
