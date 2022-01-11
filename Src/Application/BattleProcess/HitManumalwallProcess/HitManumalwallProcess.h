#pragma once

//マニュマルが壁に当たる処理
class HitManumalWallProcess
{
public:

	HitManumalWallProcess();

	~HitManumalWallProcess();

	//マニュマルのデータをセット
	void Update(manumalData& _manumalData);

	const bool GetHitWallFlg()const;

private:

	//壁の横に当たった時の処理
	void HitSideWallProcess();

	//壁の上に当たった時の処理
	void HitTopWallProcess();

	//壁の下に当たった時の処理
	void HitBottomWallProcess();

	manumalData m_manumalData;

	bool m_hitWallFlg;

};