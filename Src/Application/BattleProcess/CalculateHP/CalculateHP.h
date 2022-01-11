#pragma once

class CalculateHP
{
public:

	CalculateHP();

	~CalculateHP();

	void Update();

	//最大HPをセット
	void SetHPMax(const int _HPMax);

	//HPの割合を渡す
	const float GetHPRaito()const;

	//生きているか
	const bool GetAliveFlg();

private:

	int		m_HPMax;	//最大HP
	int		m_damage;	//受けたダメージ
	float	m_HPRaito;	//HPの割合
};