#pragma once

class HitManumalwallProcess
{
public:

	HitManumalwallProcess();

	~HitManumalwallProcess();

	//マニュマルのデータをセット
	void Update(manumalData& _manumalData);

	const bool GetHitWallFlg()const;

private:

	//壁の横に当たった時の処理
	void HitSideWallProcess();

	//壁の上と下に当たった時の処理
	void HitLengthWallProcess();

	manumalData m_manumalData;

	bool m_hitWallFlg;

};