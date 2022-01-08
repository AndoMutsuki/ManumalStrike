#pragma once

using namespace ManumalStrikeNamespace;

class ManumalBase
{
public:

	ManumalBase();

	virtual ~ManumalBase();

	virtual void Draw();

	//行列の計算
	virtual void CalculateMatrix();

	//移動するベクトルの計算
	virtual void CalculateMoveVec();

	//実際に移動する処理
	virtual void MoveProcess();

	//マニュマルのデータを派生クラスで入力
	void SetManumalData(const manumalData& _manumalData);

	//マニュマルのデータのゲッター
	virtual const manumalData& GetManumalData()const;

	//マニュマルのデータのゲッター(変更可能)
	virtual manumalData& GetManumalDataKinetic();

	//画像データを派生クラスで入力
	void SetTexData(const manumalTextureData& _texData);

	//位置のセッター
	virtual void SetPos(const Math::Vector2& _pos);

private:

	//画像の拡大率を算出
	const float CalculateTexMagnification();

	manumalData			m_manumalData;
	manumalTextureData	m_texData;

};