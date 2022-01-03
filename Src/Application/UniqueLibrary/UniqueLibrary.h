#pragma once

class UniqueLibrary
{
public:

	static UniqueLibrary& GetInstance()
	{
		static UniqueLibrary Instance;
		return Instance;
	}

	//Draw���ȒP�ɂ܂Ƃ߂�����
	void Draw2D(const Math::Matrix& _mat, const KdTexture* _texture, const int _width, const int _height);

	//Draw���ȒP�ɂ܂Ƃ߂����́A�ڍאݒ��
	void Draw2D(const Math::Matrix& _mat, const KdTexture* _texture, const Math::Rectangle* _rec, const Math::Color* _color, int _x = 0, int _y = 0, const Math::Vector2& _pivot = { 0.5f, 0.5f });

	//�l�̏���𒴂��Ȃ��悤�ɂ���
	template<typename T>
	T AdjustmentUpperLimit(T _value, T _valueMax);

	//�l�̉����𒴂��Ȃ��悤�ɂ���
	template<typename T>
	T AdjustmentLowerLimit(T _value, T _valueMin);

	//��_�̍��W�̒��������߂�
	const float GetVecLength(const Math::Vector2& _pos1, const Math::Vector2& _pos2);

	//��_�Ԃ̃x�N�g���̐�ΓI�Ȋp�x
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
