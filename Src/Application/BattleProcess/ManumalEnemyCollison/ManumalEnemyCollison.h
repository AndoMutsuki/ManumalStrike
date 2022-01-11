#pragma once

//マニュマルと敵の当たり判定
class ManumalEnemyCollison
{
public:

	ManumalEnemyCollison();

	~ManumalEnemyCollison();

	//動いているマニュマルのデータと、ぶつかった敵のデータをセット
	void Update(manumalData& _movingManumalData, const manumalData& _hitEnemyData);

	const bool GetHitManumalEnemyFlg()const;

private:

	//マニュマルと敵がぶつかっているか計算する
	void CalculateHitManumalEnemyFlg();

	//反射した後の位置を計算
	void CalculateReflectePos();

	//反射した後の角度を計算
	void CalculateReflecteAng();

	bool m_hitManumalEnemyFlg;	//マニュマルと敵がぶつかっているか

	manumalData m_movingManumalData;	//動いているマニュマルのデータ
	manumalData m_hitEnemyData;			//ぶつかった敵のデータ
};