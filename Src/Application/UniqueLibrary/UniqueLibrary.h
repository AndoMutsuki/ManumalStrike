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
	void Draw2D(const Math::Matrix& _mat, const KdTexture* _texture, const Math::Rectangle* _rec, const Math::Color* _color, int _x = 0, int _y = 0, const Math::Vector2& _pivot = { 0.5f, 0.5f });

	//�I�u�W�F�N�g�ɂԂ����Ă�����A�܂�Ԃ����ʒu�����Ƃ߂�
	void CalculateHitPos(float& _standardPos, const float& _objectPos);

	//�I�u�W�F�N�g�ɂԂ����Ă�����A�܂�Ԃ����p�x�����Ƃ߂�
	void CalculateHitAng(float& _standardAng, const float& _objectAng);

	//�C�ӂ̃x�N�g����(0,0,1)�̃x�N�g���ɑ΂��ĉ��x�̕����Ɍ����Ă��邩��Ԃ�
	const float GetVecAng(const Math::Vector3& _vec);

private:

	UniqueLibrary() {}

};

#define UNIQUELIBRARY UniqueLibrary::GetInstance()