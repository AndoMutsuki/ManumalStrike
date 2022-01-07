#pragma once

namespace ManumalStrikeNamespace
{
	//画面の大きさ
	static const int Width = 640;
	static const int Height = 360;

	//反射板のy座標
	static const int ReflectorPosY = 280;

	//敵と当たった時の挙動の種類
	enum class enemyHitType
	{
		BOUND,			//跳ね返る
		PENETRATION		//貫通
	};

	//友情コンボの種類
	enum class frendshipCombo
	{
		BOUND,			//跳ね返る
		PENETRATION		//貫通
	};

	//マニュマルの基本情報
	struct manumalData
	{
		int				m_HP;			//ヒットポイント
		float			m_scale;		//大きさ
		float			m_attack;		//攻撃力
		float			m_speed;		//速さ
		int				m_stamina;		//減速しだすまでの時間
		enemyHitType	m_enemyHitType;	//敵と当たった時の挙動の種類
		Math::Vector3	m_pos;			//位置
		Math::Vector3	m_moveVec;		//進む向き
		float			m_ang;			//角度
		float			m_power;		//進む大きさ
	};
}