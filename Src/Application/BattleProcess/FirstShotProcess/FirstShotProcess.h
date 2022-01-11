#pragma once

//マニュマルを最初に打ち出す処理
class FirstShotProcess
{
public:

	FirstShotProcess();

	~FirstShotProcess();

	//マニュマルのデータと現在のマウスのデータを渡す
	void Update(manumalData& _manumalData, const POINT& _mouse);

	void DrawArrow()const;

	const bool GetClickFlg();

	const bool GetArrowDrawFlg();

	//矢印の行列を計算するかどうかのフラグ
	const bool DoCalculateArrowMat();

private:

	//最初のマウスの座標の算出
	void CalculateFirstMousePos();

	//クリックが押されているときの処理
	void ClickProcess();

	//クリックが押されていないときの処理
	void NoClickProcess();

	//マニュマルに最初のショットの情報を入れる
	void SetManumalFirstShotData();

	//矢印の速さを算出
	void CalculateArrowSpeed();

	//矢印の行列を計算
	void CalculateArrowMat();

	KdTexture*		m_arrowTex;					//矢印の画像
	bool			m_keepManumalFlg;			//マニュマルを一回選んで離すまでのフラグ
	Math::Vector2	m_firstMousePos;			//最初のマウスの場所
	Math::Vector2	m_nowMousePos;				//今のマウスの場所
	float			m_arrowSpeed;				//打ち出す速度
	float			m_arrowAng;					//矢印の角度
	Math::Matrix	m_arrowMat;					//矢印の行列
	const float		m_arrowSpeedFixed = 15.0f;	//矢印の固定の速さ
	const float		m_arrowSpeedMax = 25.0f;	//矢印の速さの最大値
	const float		m_arrowSpeedMin = 1.0f;		//矢印の速さの最小値

	manumalData		m_manumalData;				//打ち出すマニュマルのデータ
};