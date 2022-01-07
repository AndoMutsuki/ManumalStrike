#pragma once

class ReflectorProcess
{
public: 

	ReflectorProcess();

	~ReflectorProcess();

	void Update(const bool _shotPrepareFlg);

	void Draw()const;

	const float GetLength()const;

	const float GetAng()const;

	const Math::Vector2& GetPos()const;

private:

	//�ʒu�̌v�Z
	void CalculatePos();

	//�E�ɓ�������
	void MoveRight();

	//���ɓ�������
	void MoveLeft();

	//�p�x�̌v�Z
	void CalculateAng();

	//�E�[���X������
	void LeanRight();

	//���[���X������
	void LeanLeft();

	//�s��̍���
	void CalculateMatrix();

	float			m_length;			//����
	float			m_ang;				//�p�x
	Math::Vector2	m_pos;				//�ʒu
	Math::Matrix	m_mat;				//�s��
	const float		m_moveSpeed = 15.0f;//�����X�s�[�h
	const float		m_angSpeed = 3.0f;	//�X����X�s�[�h
	KdTexture*		m_tex = nullptr;	//�摜
};