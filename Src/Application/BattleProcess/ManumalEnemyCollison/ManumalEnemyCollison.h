#pragma once

//�}�j���}���ƓG�̓����蔻��
class ManumalEnemyCollison
{
public:

	ManumalEnemyCollison();

	~ManumalEnemyCollison();

	//�����Ă���}�j���}���̃f�[�^�ƁA�Ԃ������G�̃f�[�^���Z�b�g
	void Update(manumalData& _movingManumalData, const manumalData& _hitEnemyData);

	const bool GetHitManumalEnemyFlg()const;

private:

	//�}�j���}���ƓG���Ԃ����Ă��邩�v�Z����
	void CalculateHitManumalEnemyFlg();

	//���˂�����̈ʒu���v�Z
	void CalculateReflectePos();

	//���˂�����̊p�x���v�Z
	void CalculateReflecteAng();

	bool m_hitManumalEnemyFlg;	//�}�j���}���ƓG���Ԃ����Ă��邩

	manumalData m_movingManumalData;	//�����Ă���}�j���}���̃f�[�^
	manumalData m_hitEnemyData;			//�Ԃ������G�̃f�[�^
};