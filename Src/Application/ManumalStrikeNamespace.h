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
	enum class frendshipComboType
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
		float			speedRaito;		//�����{��
		int				stamina;		//�����������܂ł̎���
		int				nowStamina;		//���̃X�^�~�i
		enemyHitType	enemyHitType;	//�G�Ɠ����������̋����̎��
		Math::Vector2	pos;			//�ʒu
		Math::Vector2	moveVec;		//�i�ތ���
		float			ang;			//�p�x
		float			nowSpeed;		//�i�ޑ傫��
		Math::Matrix	mat;			//�s��
		frendshipComboType	frendshipType;	//�F��R���{�̃^�C�v
		bool			frendFlg;		//�F��R���{�t���O
	};

	//�F��R���{�̊�{���
	struct friendshipComboData
	{
		int		damageFixed;	//�Œ�_���[�W
		float	damageRaito;	//�}�j���}���̍U���͈ˑ��_���[�W
		float	range;			//�˒�
	};

	//�G�̍U���̎��
	enum class enemyAttackType
	{
		BEAM,			//�r�[��
		EXPLOSION,		//����
		BIGEXPLOSION	//�傫������
	};


	//�G�̊�{���
	struct enemyData
	{
		int				HP;				//�q�b�g�|�C���g
		float			scale;			//���a
		int				attackTurn;		//�U���܂ł̃^�[����
		int				nowAttackTurn;	//���̍U���܂ł̃^�[����
		float			attack;			//�U����
		enemyAttackType attackType;		//�U���̎��
		Math::Vector2	pos;			//�ʒu
	};

	//�G�̍U���̊�{���
	struct enemyAttackData
	{
		int		damageFixed;	//�Œ�_���[�W
		float	damageRaito;	//�G�̍U���͈ˑ��_���[�W
		float	range;			//�˒�
	};

	//�G�t�F�N�g�̊�{���
	struct effectData
	{
		std::string fileName;
		char16_t*	fileChar;
		int			timeMax;
	};

	//�摜���
	struct textureData
	{
		KdTexture*			tex;		//�摜
		Math::Rectangle		rec;		//���A�����Ȃ�
		Math::Color			color;		//�F
	};
}