#pragma once

class CalculateSpeed
{
public:

	CalculateSpeed();

	~CalculateSpeed();

	void Update(manumalData& _manumalData);

private:

	//�X�^�~�i�v�Z
	void CalculateStamina();

	//�X�s�[�h����
	void CalculateDeceleration();

	manumalData m_manumalData;

	bool m_decelerationFlg;	//�����t���O

};