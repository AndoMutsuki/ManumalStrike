#include"Application/Headers.h"

ManumalEnemyCollison::ManumalEnemyCollison()
{
	m_hitManumalEnemyFlg = false;
}

ManumalEnemyCollison::~ManumalEnemyCollison()
{
}

void ManumalEnemyCollison::Update(manumalData& _movingManumalData, const enemyData& _hitEnemyData)
{
	//メンバ変数に変換する
	m_movingManumalData = _movingManumalData;
	m_hitEnemyData		= _hitEnemyData;

	CalculateHitManumalEnemyFlg();
	if (!m_hitManumalEnemyFlg) return;

	CalculateReflectePos();

	CalculateReflecteAng();
	
	//求めたデータを格納する
	_movingManumalData = m_movingManumalData;
}

const bool ManumalEnemyCollison::GetHitManumalEnemyFlg() const
{
	return m_hitManumalEnemyFlg;
}

void ManumalEnemyCollison::CalculateHitManumalEnemyFlg()
{
	float betweenManumalEnemyLength	= UNIQUELIBRARY.GetVecLength(m_movingManumalData.pos, m_hitEnemyData.pos);	//マニュマルと敵の距離
	float sumManumalEnemyScale		= m_movingManumalData.scale + m_hitEnemyData.scale;								//マニュマルと敵の大きさの合計
	m_hitManumalEnemyFlg			= betweenManumalEnemyLength < sumManumalEnemyScale;
}

void ManumalEnemyCollison::CalculateReflectePos()
{
	Math::Vector2 betweenVec	= m_movingManumalData.pos - m_hitEnemyData.pos;	//マニュマルと敵の間のベクトル
	betweenVec.Normalize();
	Math::Vector2 reflectedPos	= m_hitEnemyData.pos + betweenVec * (m_movingManumalData.scale + m_hitEnemyData.scale);	//反射した後の位置
	m_movingManumalData.pos		= reflectedPos;
}

void ManumalEnemyCollison::CalculateReflecteAng()
{
	float collicionAng = -UNIQUELIBRARY.GetVecAng(m_movingManumalData.pos, m_hitEnemyData.pos) + 180.0f;	//どの辺にぶつかっているか求めるための角度

	//どの辺にぶつかっているか求め、それにより角度を求める
	if (collicionAng <= 135 && collicionAng > 45)			//左の辺
	{
		m_movingManumalData.ang = UNIQUELIBRARY.CalculateReflectAng(m_movingManumalData.ang, 0);
	}
	else if (collicionAng <= 225 && collicionAng > 135)		//下の辺
	{
		m_movingManumalData.ang = UNIQUELIBRARY.CalculateReflectAng(m_movingManumalData.ang, 90);
	}
	else if (collicionAng <= 315 && collicionAng > 225)		//右の辺
	{
		m_movingManumalData.ang = UNIQUELIBRARY.CalculateReflectAng(m_movingManumalData.ang, 0);
	}
	else													//上の辺
	{
		m_movingManumalData.ang = UNIQUELIBRARY.CalculateReflectAng(m_movingManumalData.ang, 90);
	}
}
