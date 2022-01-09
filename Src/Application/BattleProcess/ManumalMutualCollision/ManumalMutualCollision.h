#pragma once

class ManumalMutualCollision
{
public:

	ManumalMutualCollision();

	~ManumalMutualCollision();

	//動いているマニュマルのデータと、ぶつかったマニュマルのデータをセット
	void Update(const manumalData& _movingManumalData, manumalData& _hitedManumalData);

	const bool GetmHitManumalMutualFlg()const;

private:

	//マニュマル同士がぶつかっているか計算する
	void CalculateHitManumalMutualFlg();

	//反射した後の計算
	void CalculateReflecte();

	bool m_hitManumalMutualFlg;	//動いているマニュマルと他のマニュマルがぶつかっているか

	manumalData m_movingManumalData;	//動いているマニュマルのデータ
	manumalData m_hitedManumalData;		//ぶつかったマニュマルのデータ
};