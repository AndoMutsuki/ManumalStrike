#pragma once

class UniqueLibrary
{
public:

	static UniqueLibrary& GetInstance()
	{
		static UniqueLibrary Instance;
		return Instance;
	}

	//Drawを簡単にまとめたもの
	void Draw2D(const Math::Matrix& _mat, const KdTexture* _texture, const int _width, const int _height);

	//Drawを簡単にまとめたもの、詳細設定版
	void Draw2D(const Math::Matrix& _mat, const KdTexture* _texture, const Math::Rectangle* _rec, const Math::Color* _color, int _x = 0, int _y = 0, const Math::Vector2& _pivot = { 0.5f, 0.5f });

	//値の上限を超えないようにする
	template<typename T>
	T AdjustmentUpperLimit(T _value, T _valueMax);

	//値の加減を超えないようにする
	template<typename T>
	T AdjustmentLowerLimit(T _value, T _valueMin);

	//二点の座標の長さを求める
	const float GetVecLength(const Math::Vector2& _pos1, const Math::Vector2& _pos2);

	//二点間のベクトルの絶対的な角度
	const float GetVecAng(const Math::Vector2& _pos1, const Math::Vector2& _pos2);

private:

	UniqueLibrary() {}

};

#define UNIQUELIBRARY UniqueLibrary::GetInstance()

template<typename T>
inline T UniqueLibrary::AdjustmentUpperLimit(T _value, T _valueMax)
{
	if (_value >= _valueMax)
	{
		return _valueMax;
	}
	return _value;
}

template<typename T>
inline T UniqueLibrary::AdjustmentLowerLimit(T _value, T _valueMin)
{
	if (_value <= _valueMin)
	{
		return _valueMin;
	}
	return _value;
}
