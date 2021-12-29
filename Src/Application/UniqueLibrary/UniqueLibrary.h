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
	float AdjustmentUpperLimit(float _value, float _valueMax);

	//�l�̉����𒴂��Ȃ��悤�ɂ���
	float AdjustmentLowerLimit(float _value, float _valueMin);

	//�C�ӂ̃x�N�g����(0,0,1)�̃x�N�g���ɑ΂��ĉ��x�̕����Ɍ����Ă��邩��Ԃ�
	const float GetVecAng(const Math::Vector3& _vec);

private:

	UniqueLibrary() {}

};

#define UNIQUELIBRARY UniqueLibrary::GetInstance()