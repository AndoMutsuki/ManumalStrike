#pragma once

//マニュマルが反射板に当たる処理
class HitManumalReflectorProcess
{
public:

	HitManumalReflectorProcess();

	~HitManumalReflectorProcess();

	//マニュマルのデータと反射板のクラスをセットする
	void Update(manumalData& _manumalData, ReflectorProcess* _reflectorProcess);

	const bool GetHitReflectorFlg()const;

private:

	//x座標が反射板に当たっているか
	const bool HitManumalReflectorX();

	//y座標が反射板に当たっているか
	const bool HitManumalReflectorY();

	//反射板の上から当たった時の処理
	void HitReflectorTopProcess();

	//反射板の下から当たった時の処理
	void HitReflectorBottomProcess();

	//反射板の右端が上がっているときの処理
	void ReflectorRightUpProcess();

	//反射板の左端が上がっているときの処理
	void ReflectorLeftUpProcess();

	//反射板が並行で、右から当たったときの処理
	void ManumalRightComeProcess();

	//反射板が並行で、左から当たったときの処理
	void ManumalLefttComeProcess();

	manumalData			m_manumalData;
	ReflectorProcess*	m_reflectorProcess = nullptr;

	bool				m_hitReflectorFlg;	//マニュマルが反射板と当たっているか
	float				m_relativePosX;		//相対的な位置のx座標
	float				m_cosO;				//マニュマルと反射板の間の角のcos値
	float				m_tanO;				//マニュマルと反射板の間の角のtan値

};