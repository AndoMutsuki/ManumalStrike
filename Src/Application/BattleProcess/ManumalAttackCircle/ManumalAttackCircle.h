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

	//���Ԃ̏���
	void TimeProcess();

	//�傫���̌v�Z
	void CalculateScale();

	//�����x�̌v�Z
	void CalculateAlpha();

	KdTexture* m_tex;

	Math::Matrix	m_mat;
	manumalData		m_manumalData;
	int				m_time;
	const int		m_timeMax = 60;
	float			m_alpha;
};