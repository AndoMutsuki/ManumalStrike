#pragma once

class HitManumalwallProcess
{
public:

	HitManumalwallProcess();

	~HitManumalwallProcess();

	//�}�j���}���̃f�[�^���Z�b�g
	void Update(manumalData& _manumalData);

	const bool GetHitWallFlg()const;

private:

	//�ǂ̉��ɓ����������̏���
	void HitSideWallProcess();

	//�ǂ̏�Ɖ��ɓ����������̏���
	void HitLengthWallProcess();

	manumalData m_manumalData;

	bool m_hitWallFlg;

};