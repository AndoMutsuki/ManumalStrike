#pragma once

//�}�j���}�����ǂɓ����鏈��
class HitManumalWallProcess
{
public:

	HitManumalWallProcess();

	~HitManumalWallProcess();

	//�}�j���}���̃f�[�^���Z�b�g
	void Update(manumalData& _manumalData);

	const bool GetHitWallFlg()const;

private:

	//�ǂ̉��ɓ����������̏���
	void HitSideWallProcess();

	//�ǂ̏�ɓ����������̏���
	void HitTopWallProcess();

	//�ǂ̉��ɓ����������̏���
	void HitBottomWallProcess();

	manumalData m_manumalData;

	bool m_hitWallFlg;

};