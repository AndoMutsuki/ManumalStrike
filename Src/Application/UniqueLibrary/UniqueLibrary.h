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
	void Draw2D(const Math::Matrix& _mat, const KdTexture* _texture, const Math::Rectangle* _rec, const Math::Color* _color, int _x = 0, int _y = 0, const Math::Vector2& _pivot = { 0.5f, 0.5f });

	//オブジェクトにぶつかっていたら、折り返した位置をもとめる
	void CalculateHitPos(float& _standardPos, const float& _objectPos);

	//オブジェクトにぶつかっていたら、折り返した角度をもとめる
	void CalculateHitAng(float& _standardAng, const float& _objectAng);

	//任意のベクトルが(0,0,1)のベクトルに対して何度の方向に向いているかを返す
	const float GetVecAng(const Math::Vector3& _vec);

private:

	UniqueLibrary() {}

};

#define UNIQUELIBRARY UniqueLibrary::GetInstance()