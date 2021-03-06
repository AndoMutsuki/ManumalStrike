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

	//時間の処理
	void TimeProcess();

	//大きさの計算
	void CalculateScale();

	//透明度の計算
	void CalculateAlpha();

	KdTexture* m_tex;

	Math::Matrix	m_mat;
	manumalData		m_manumalData;
	int				m_time;
	const int		m_timeMax = 60;
	float			m_alpha;
};