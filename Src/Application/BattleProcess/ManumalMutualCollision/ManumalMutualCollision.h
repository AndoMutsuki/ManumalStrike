#pragma once

class ManumalMutualCollision
{
public:

	ManumalMutualCollision();

	~ManumalMutualCollision();

	//�����Ă���}�j���}���̃f�[�^�ƁA�Ԃ������}�j���}���̃f�[�^���Z�b�g
	void Update(const manumalData& _movingManumalData, manumalData& _hitedManumalData);

	const bool GetmHitManumalMutualFlg()const;

private:

	//�}�j���}�����m���Ԃ����Ă��邩�v�Z����
	void CalculateHitManumalMutualFlg();

	//���˂�����̌v�Z
	void CalculateReflecte();

	bool m_hitManumalMutualFlg;	//�����Ă���}�j���}���Ƒ��̃}�j���}�����Ԃ����Ă��邩

	manumalData m_movingManumalData;	//�����Ă���}�j���}���̃f�[�^
	manumalData m_hitedManumalData;		//�Ԃ������}�j���}���̃f�[�^
};