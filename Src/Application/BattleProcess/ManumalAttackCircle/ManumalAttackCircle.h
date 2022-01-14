#pragma once

class ManumalAttackCircle
{
public:

	ManumalAttackCircle();

	~ManumalAttackCircle();

	void Init();

	void Update(const manumalData& _manumalData);

	void Draw()const;

private:

	//ŠÔ‚Ìˆ—
	void TimeProcess();

	//‘å‚«‚³‚ÌŒvZ
	void CalculateScale();

	//“§–¾“x‚ÌŒvZ
	void CalculateAlpha();

	KdTexture* m_tex;

	Math::Matrix	m_mat;
	manumalData		m_manumalData;
	int				m_time;
	const int		m_timeMax = 60;
	float			m_alpha;
};