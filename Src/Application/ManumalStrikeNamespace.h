#pragma once

namespace ManumalStrikeNamespace
{
	//��ʂ̑傫��
	static const int Width = 640;
	static const int Height = 360;

	//���˔�y���W
	static const int ReflectorPosY = 280;

	//�G�Ɠ����������̋����̎��
	enum class enemyHitType
	{
		BOUND,			//���˕Ԃ�
		PENETRATION		//�ђ�
	};

	//�F��R���{�̎��
	enum class frendshipCombo
	{
		BOUND,			//���˕Ԃ�
		PENETRATION		//�ђ�
	};

	//�}�j���}���̊�{���
	struct manumalData
	{
		int				m_HP;			//�q�b�g�|�C���g
		float			m_scale;		//�傫��
		float			m_attack;		//�U����
		float			m_speed;		//����
		int				m_stamina;		//�����������܂ł̎���
		enemyHitType	m_enemyHitType;	//�G�Ɠ����������̋����̎��
		Math::Vector3	m_pos;			//�ʒu
		Math::Vector3	m_moveVec;		//�i�ތ���
		float			m_ang;			//�p�x
		float			m_power;		//�i�ޑ傫��
	};
}