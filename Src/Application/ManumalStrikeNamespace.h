#pragma once

namespace ManumalStrikeNamespace
{
	//��ʂ̑傫��
	static const int Width	= 640;
	static const int Top	= 360;
	static const int Bottom = -300;

	//���˔�y���W
	static const int ReflectorPosY = 220;

	//�G�Ɠ����������̋����̎��
	enum class enemyHitType
	{
		BOUND,			//���˕Ԃ�
		PENETRATION		//�ђ�
	};

	//�F��R���{�̎��
	enum class frendshipCombo
	{
		BEAM,			//�r�[��
		EXPLOSION		//����
	};

	//�}�j���}���̊�{���
	struct manumalData
	{
		int				HP;				//�q�b�g�|�C���g
		float			scale;			//���a
		float			attack;			//�U����
		float			speed;			//����
		int				stamina;		//�����������܂ł̎���
		enemyHitType	enemyHitType;	//�G�Ɠ����������̋����̎��
		Math::Vector2	pos;			//�ʒu
		Math::Vector2	moveVec;		//�i�ތ���
		float			ang;			//�p�x
		float			nowSpeed;			//�i�ޑ傫��
		Math::Matrix	mat;			//�s��
	};

	//�}�j���}���̉摜���
	struct manumalTextureData
	{
		KdTexture*			tex;		//�摜
		Math::Rectangle		rec;		//���A�����Ȃ�
		Math::Color			color;		//�F
	};
}