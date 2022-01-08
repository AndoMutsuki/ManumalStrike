#include"Application/Headers.h"

void UniqueLibrary::Draw2D(const Math::Matrix& _mat, const KdTexture* _texture, const int _width, const int _height, const float _alpha)
{
	Math::Rectangle rec = { 0,0,_width,_height };
	SHADER.m_spriteShader.SetMatrix(_mat);
	SHADER.m_spriteShader.DrawTex(_texture, rec, _alpha);
}

void UniqueLibrary::Draw2D(const Math::Matrix& _mat, const KdTexture* _texture, const Math::Rectangle* _rec, const Math::Color* _color, int _x, int _y, const Math::Vector2& _pivot)
{
	SHADER.m_spriteShader.SetMatrix(_mat);
	SHADER.m_spriteShader.DrawTex(_texture, _x, _y, _rec, _color, _pivot);
}

const float UniqueLibrary::GetVecLength(const Math::Vector2& _pos1, const Math::Vector2& _pos2)
{
	Math::Vector2 lengthVec = _pos1 - _pos2;
	float length = lengthVec.Length();
	return length;
}

const float UniqueLibrary::GetVecAng(const Math::Vector2& _pos1, const Math::Vector2& _pos2)
{
	Math::Vector2 vec = _pos1 - _pos2;
	vec.Normalize();

	Math::Vector2 dot = DirectX::XMVector2Dot(vec, { 0,1 });
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

const float UniqueLibrary::CalculateReflectPos(const float& _standardPos, const float& _objectPos)
{
	float standardPos = _standardPos;
	if (_standardPos >= 0)
	{
		standardPos += abs(_objectPos) - abs(_standardPos);
	}
	else
	{
		standardPos -= abs(_objectPos) - abs(_standardPos);
	}

	return standardPos;
}

const float UniqueLibrary::CalculateReflectAng(const float& _standardAng, const float& _objectAng)
{
	float standardAng = _standardAng;
	standardAng = 360 - _standardAng + (2 * _objectAng);

	while (standardAng > 360)
	{
		standardAng -= 360;
	}

	return standardAng;
}
