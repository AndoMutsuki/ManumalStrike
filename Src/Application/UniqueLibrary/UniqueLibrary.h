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
	float AdjustmentUpperLimit(float _value, float _valueMax);

	//値の加減を超えないようにする
	float AdjustmentLowerLimit(float _value, float _valueMin);

	//任意のベクトルが(0,0,1)のベクトルに対して何度の方向に向いているかを返す
	const float GetVecAng(const Math::Vector3& _vec);

private:

	UniqueLibrary() {}

};

#define UNIQUELIBRARY UniqueLibrary::GetInstance()