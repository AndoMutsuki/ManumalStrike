#pragma once

class CalculateHP
{
public:

	CalculateHP();

	~CalculateHP();

	void Update();

	//�ő�HP���Z�b�g
	void SetHPMax(const int _HPMax);

	//HP�̊�����n��
	const float GetHPRaito()const;

	//�����Ă��邩
	const bool GetAliveFlg();

private:

	int		m_HPMax;	//�ő�HP
	int		m_damage;	//�󂯂��_���[�W
	float	m_HPRaito;	//HP�̊���
};