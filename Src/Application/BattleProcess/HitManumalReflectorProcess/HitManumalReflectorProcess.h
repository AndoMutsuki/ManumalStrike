#pragma once

//�}�j���}�������˔ɓ����鏈��
class HitManumalReflectorProcess
{
public:

	HitManumalReflectorProcess();

	~HitManumalReflectorProcess();

	//�}�j���}���̃f�[�^�Ɣ��˔̃N���X���Z�b�g����
	void Update(manumalData& _manumalData, ReflectorProcess* _reflectorProcess);

	const bool GetHitReflectorFlg()const;

private:

	//x���W�����˔ɓ������Ă��邩
	const bool HitManumalReflectorX();

	//y���W�����˔ɓ������Ă��邩
	const bool HitManumalReflectorY();

	//���˔̏ォ�瓖���������̏���
	void HitReflectorTopProcess();

	//���˔̉����瓖���������̏���
	void HitReflectorBottomProcess();

	//���˔̉E�[���オ���Ă���Ƃ��̏���
	void ReflectorRightUpProcess();

	//���˔̍��[���オ���Ă���Ƃ��̏���
	void ReflectorLeftUpProcess();

	//���˔����s�ŁA�E���瓖�������Ƃ��̏���
	void ManumalRightComeProcess();

	//���˔����s�ŁA�����瓖�������Ƃ��̏���
	void ManumalLefttComeProcess();

	manumalData			m_manumalData;
	ReflectorProcess*	m_reflectorProcess = nullptr;

	bool				m_hitReflectorFlg;	//�}�j���}�������˔Ɠ������Ă��邩
	float				m_relativePosX;		//���ΓI�Ȉʒu��x���W
	float				m_cosO;				//�}�j���}���Ɣ��˔̊Ԃ̊p��cos�l
	float				m_tanO;				//�}�j���}���Ɣ��˔̊Ԃ̊p��tan�l

};