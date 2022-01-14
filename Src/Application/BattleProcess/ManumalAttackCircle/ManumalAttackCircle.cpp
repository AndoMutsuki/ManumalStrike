#include"Application/Headers.h"

ManumalAttackCircle::ManumalAttackCircle()
{
	m_tex = TEXMANA.GetTex("Data/Texture/Manumal/manumalAttackCircle.png");

	Init();
}

ManumalAttackCircle::~ManumalAttackCircle()
{
}

void ManumalAttackCircle::Init()
{
	m_mat = Math::Matrix::Identity;
	m_time = m_timeMax;
	m_alpha = 1.0f;
}

void ManumalAttackCircle::Update(const manumalData& _manumalData)
{
	m_manumalData = _manumalData;

	TimeProcess();

	CalculateScale();

	CalculateAlpha();
}

void ManumalAttackCircle::Draw() const
{
	UNIQUELIBRARY.Draw2D(m_mat, m_tex, 100, 100, m_alpha);
}

void ManumalAttackCircle::TimeProcess()
{
	m_time--;
	
	if (m_time < 0)
	{
		m_time = m_timeMax;
	}
}

void ManumalAttackCircle::CalculateScale()
{
	float scale = ((float)m_time * 0.01f + 1.1f);
	Math::Matrix scaleMat = DirectX::XMMatrixScaling(scale, scale, scale);

	m_mat = scaleMat * m_manumalData.mat;
}

void ManumalAttackCircle::CalculateAlpha()
{
	m_alpha = 1.0f / (float)m_timeMax * m_time;
}
