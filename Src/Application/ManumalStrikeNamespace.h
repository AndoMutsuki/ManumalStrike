#pragma once

namespace ManumalStrikeNamespace
{
	//画面の大きさ
	static const int Width	= 640;
	static const int Top	= 360;
	static const int Bottom = -300;

	//反射板のy座標
	static const int ReflectorPosY = 220;

	//敵と当たった時の挙動の種類
	enum class enemyHitType
	{
		BOUND,			//跳ね返る
		PENETRATION		//貫通
	};

	//友情コンボの種類
	enum class frendshipCombo
	{
		BEAM,			//ビーム
		EXPLOSION		//爆発
	};

	//マニュマルの基本情報
	struct manumalData
	{
		int				HP;				//ヒットポイント
		float			scale;			//半径
		float			attack;			//攻撃力
		float			speedRaito;		//速さ倍率
		int				stamina;		//減速しだすまでの時間
		int				nowStamina;		//今のスタミナ
		enemyHitType	enemyHitType;	//敵と当たった時の挙動の種類
		Math::Vector2	pos;			//位置
		Math::Vector2	moveVec;		//進む向き
		float			ang;			//角度
		float			nowSpeed;		//進む大きさ
		Math::Matrix	mat;			//行列
	};

	//敵の攻撃の種類
	enum class enemyAttackType
	{
		BEAM,			//ビーム
		EXPLOSION		//爆発
	};


	//敵の基本情報
	struct enemyData
	{
		int				HP;				//ヒットポイント
		float			scale;			//半径
		float			attack;			//攻撃力
		enemyAttackType attackType;		//攻撃の種類
		Math::Vector2	pos;			//位置
	};

	//画像情報
	struct textureData
	{
		KdTexture*			tex;		//画像
		Math::Rectangle		rec;		//幅、高さなど
		Math::Color			color;		//色
	};
}