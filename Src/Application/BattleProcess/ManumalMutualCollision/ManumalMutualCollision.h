#pragma once

//マニュマル同士の当たり判定
class ManumalMutualCollision
{
public:

	ManumalMutualCollision();

	~ManumalMutualCollision();

	//動いているマニュマルのデータと、ぶつかったマニュマルのデータをセット
	void Update(const manumalData& _movingManumalData, manumalData& _hitedManumalData);

	const bool GetHitManumalMutualFlg()const;

private:

	//マニュマル同士がぶつかっているか計算する
	void CalculateHitManumalMutualFlg();

	//反射した後の計算
	void CalculateReflecte();

	bool m_hitManumalMutualFlg;	//動いているマニュマルと他のマニュマルがぶつかっているか

	manumalData m_movingManumalData;	//動いているマニュマルのデータ
	manumalData m_hitedManumalData;		//ぶつかったマニュマルのデータ
};