#pragma once

class CalculateSpeed
{
public:

	CalculateSpeed();

	~CalculateSpeed();

	void Update(manumalData& _manumalData);

private:

	//スタミナ計算
	void CalculateStamina();

	//スピード減速
	void CalculateDeceleration();

	manumalData m_manumalData;

	bool m_decelerationFlg;	//減速フラグ

};