#include"Application/Headers.h"

ManumalMutualCollision::ManumalMutualCollision()
{
	m_hitManumalMutualFlg = false;
}

ManumalMutualCollision::~ManumalMutualCollision()
{
}

void ManumalMutualCollision::Update(const manumalData& _movingManumalData, manumalData& _hitedManumalData)
{
	//メンバ変数に変換する
	m_movingManumalData = _movingManumalData;
	m_hitedManumalData	= _hitedManumalData;

	CalculateHitManumalMutualFlg();
	if (!m_hitManumalMutualFlg) return;

	CalculateReflecte();

	//求めたデータを格納する
	_hitedManumalData = m_hitedManumalData;
}

const bool ManumalMutualCollision::GetmHitManumalMutualFlg() const
{
	return m_hitManumalMutualFlg;
}

void ManumalMutualCollision::CalculateHitManumalMutualFlg()
{
	float betweenManumalMutualLength	= UNIQUELIBRARY.GetVecLength(m_movingManumalData.pos, m_hitedManumalData.pos);	//マニュマル同士の距離
	float sumManumalMutualScale			= m_movingManumalData.scale + m_hitedManumalData.scale;								//マニュマル同士の大きさの合計
	m_hitManumalMutualFlg				= betweenManumalMutualLength < sumManumalMutualScale;
}

void ManumalMutualCollision::CalculateReflecte()
{
	//反射した後の位置の計算
	Math::Vector2 betweenVec	= m_hitedManumalData.pos - m_movingManumalData.pos;
	betweenVec.Normalize();
	Math::Vector2 reflectedPos	= m_movingManumalData.pos + betweenVec * (m_movingManumalData.scale + m_hitedManumalData.scale);	//反射した後の位置
	m_hitedManumalData.pos		= reflectedPos;

	//反射した後の角度の計算
	float reflectedAng		= -UNIQUELIBRARY.GetVecAng(m_hitedManumalData.pos, m_movingManumalData.pos);	//反射した後の角度
	m_hitedManumalData.ang	= reflectedAng;
}
