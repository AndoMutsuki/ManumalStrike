#pragma once

//�}�j���}�����ŏ��ɑł��o������
class FirstShotProcess
{
public:

	FirstShotProcess();

	~FirstShotProcess();

	//�}�j���}���̃f�[�^�ƌ��݂̃}�E�X�̃f�[�^��n��
	void Update(manumalData& _manumalData, const POINT& _mouse);

	void DrawArrow()const;

	const bool GetClickFlg();

	const bool GetArrowDrawFlg();

	//���̍s����v�Z���邩�ǂ����̃t���O
	const bool DoCalculateArrowMat();

private:

	//�ŏ��̃}�E�X�̍��W�̎Z�o
	void CalculateFirstMousePos();

	//�N���b�N��������Ă���Ƃ��̏���
	void ClickProcess();

	//�N���b�N��������Ă��Ȃ��Ƃ��̏���
	void NoClickProcess();

	//�}�j���}���ɍŏ��̃V���b�g�̏�������
	void SetManumalFirstShotData();

	//���̑������Z�o
	void CalculateArrowSpeed();

	//���̍s����v�Z
	void CalculateArrowMat();

	KdTexture*		m_arrowTex;					//���̉摜
	bool			m_keepManumalFlg;			//�}�j���}�������I��ŗ����܂ł̃t���O
	Math::Vector2	m_firstMousePos;			//�ŏ��̃}�E�X�̏ꏊ
	Math::Vector2	m_nowMousePos;				//���̃}�E�X�̏ꏊ
	float			m_arrowSpeed;				//�ł��o�����x
	float			m_arrowAng;					//���̊p�x
	Math::Matrix	m_arrowMat;					//���̍s��
	const float		m_arrowSpeedFixed = 15.0f;	//���̌Œ�̑���
	const float		m_arrowSpeedMax = 25.0f;	//���̑����̍ő�l
	const float		m_arrowSpeedMin = 1.0f;		//���̑����̍ŏ��l

	manumalData		m_manumalData;				//�ł��o���}�j���}���̃f�[�^
};