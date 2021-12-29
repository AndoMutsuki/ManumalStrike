#include"Application/Headers.h"

void UniqueLibrary::Draw2D(const Math::Matrix& _mat, const KdTexture* _texture, const int _width, const int _height)
{
	Math::Rectangle rec = { 0,0,_width,_height };
	SHADER.m_spriteShader.SetMatrix(_mat);
	SHADER.m_spriteShader.DrawTex(_texture, rec);
}

void UniqueLibrary::Draw2D(const Math::Matrix& _mat, const KdTexture* _texture, const Math::Rectangle* _rec, const Math::Color* _color, int _x, int _y, const Math::Vector2& _pivot)
{
	SHADER.m_spriteShader.SetMatrix(_mat);
	SHADER.m_spriteShader.DrawTex(_texture, _x, _y, _rec, _color, _pivot);
}

float UniqueLibrary::AdjustmentUpperLimit(float _value, float _valueMax)
{
	if (_value >= _valueMax)
	{
		return _valueMax;
	}
	return _value;
}

float UniqueLibrary::AdjustmentLowerLimit(float _value, float _valueMin)
{
	if (_value <= _valueMin)
	{
		return _valueMin;
	}
	return _value;
}

const float UniqueLibrary::GetVecAng(const Math::Vector3& _vec)
{
	Math::Vector3 vec = _vec;
	vec.z = 0;
	vec.Normalize();

	Math::Vector3 dot = DirectX::XMVector3Dot(vec, { 0,0,1 });
	if (dot.x > 1)
		dot.x = 1;
	if (dot.x < -1)
		dot.x = -1;

	float ang = DirectX::XMConvertToDegrees(acos(dot.x));

	if (vec.x < 0)
	{
		ang = -ang;
	}

	return ang;
}