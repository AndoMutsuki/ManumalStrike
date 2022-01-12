#pragma once

class EnemyBase
{
public:

	EnemyBase();

	virtual ~EnemyBase();

	virtual void Draw();

	//敵の位置をセット
	void SetEnemyPos(const Math::Vector2& _pos);

	//敵のデータを派生クラスで入力
	void SetEnemyData(const enemyData& _enemyData);

	//敵のデータのゲッター
	virtual const enemyData& GetEnemyData()const;

	//敵のデータのゲッター(変更可能)
	virtual enemyData& GetEnemyDataKinetic();

	//画像データを派生クラスで入力
	void SetTexData(const textureData& _texData);

private:

	//画像の拡大率を算出
	const float CalculateTexMagnification();

	enemyData	m_enemyData;
	textureData	m_texData;
};