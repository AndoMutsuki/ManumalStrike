#include"Application/Headers.h"

void UniqueLibrary::Draw2D(const Math::Matrix& _mat, const KdTexture* _texture, const Math::Rectangle* _rec, const Math::Color* _color, int _x, int _y, const Math::Vector2& _pivot)
{
	SHADER.m_spriteShader.SetMatrix(_mat);
	SHADER.m_spriteShader.DrawTex(_texture, _x, _y, _rec, _color, _pivot);
}

void UniqueLibrary::CalculateHitPos(float& _standardPos, const float& _objectPos)
{
	if (_standardPos >= 0)
	{
		_standardPos += abs(_objectPos) - abs(_standardPos);
	}
	else
	{
		_standardPos -= abs(_objectPos) - abs(_standardPos);
	}
}

void UniqueLibrary::CalculateHitAng(float& _standardAng, const float& _objectAng)
{
	_standardAng = 360 - _standardAng + (2 * _objectAng);

	while (_standardAng > 360)
	{
		_standardAng -= 360;
	}
}

void UniqueLibrary::AdjustmentHitAng(float& _standardAng)
{
	if (_standardAng >= 80 && _standardAng <= 90)
	{
		_standardAng = 80.0f;
	}

	if (_standardAng > 90 && _standardAng <= 100)
	{
		_standardAng = 100.0f;
	}

	if (_standardAng >= 260 && _standardAng < 270)
	{
		_standardAng = 260.0f;
	}

	if (_standardAng >= 270 && _standardAng <= 280)
	{
		_standardAng = 280.0f;
	}
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