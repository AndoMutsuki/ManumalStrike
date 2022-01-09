#include"Application/Headers.h"

ManumalMutualCollision::ManumalMutualCollision()
{
	m_hitManumalMutualFlg = false;
}

ManumalMutualCollision::~ManumalMutualCollision()
{
}

void ManumalMutualCollision::Update(const manumalData& _movingManumalData, manumalData& _hitedManumalData)
{
	//�����o�ϐ��ɕϊ�����
	m_movingManumalData = _movingManumalData;
	m_hitedManumalData	= _hitedManumalData;

	CalculateHitManumalMutualFlg();
	if (!m_hitManumalMutualFlg) return;

	CalculateReflecte();

	//���߂��f�[�^���i�[����
	_hitedManumalData = m_hitedManumalData;
}

const bool ManumalMutualCollision::GetmHitManumalMutualFlg() const
{
	return m_hitManumalMutualFlg;
}

void ManumalMutualCollision::CalculateHitManumalMutualFlg()
{
	float betweenManumalMutualLength	= UNIQUELIBRARY.GetVecLength(m_movingManumalData.pos, m_hitedManumalData.pos);	//�}�j���}�����m�̋���
	float sumManumalMutualScale			= m_movingManumalData.scale + m_hitedManumalData.scale;								//�}�j���}�����m�̑傫���̍��v
	m_hitManumalMutualFlg				= betweenManumalMutualLength < sumManumalMutualScale;
}

void ManumalMutualCollision::CalculateReflecte()
{
	//���˂�����̈ʒu�̌v�Z
	Math::Vector2 betweenVec	= m_hitedManumalData.pos - m_movingManumalData.pos;
	betweenVec.Normalize();
	Math::Vector2 reflectedPos	= m_movingManumalData.pos + betweenVec * (m_movingManumalData.scale + m_hitedManumalData.scale);	//���˂�����̈ʒu
	m_hitedManumalData.pos		= reflectedPos;

	//���˂�����̊p�x�̌v�Z
	float reflectedAng		= -UNIQUELIBRARY.GetVecAng(m_hitedManumalData.pos, m_movingManumalData.pos);	//���˂�����̊p�x
	m_hitedManumalData.ang	= reflectedAng;
}
