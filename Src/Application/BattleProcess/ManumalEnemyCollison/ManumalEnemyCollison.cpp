#include"Application/Headers.h"

ManumalEnemyCollison::ManumalEnemyCollison()
{
	m_hitManumalEnemyFlg = false;
}

ManumalEnemyCollison::~ManumalEnemyCollison()
{
}

void ManumalEnemyCollison::Update(manumalData& _movingManumalData, const enemyData& _hitEnemyData)
{
	//�����o�ϐ��ɕϊ�����
	m_movingManumalData = _movingManumalData;
	m_hitEnemyData		= _hitEnemyData;

	CalculateHitManumalEnemyFlg();
	if (!m_hitManumalEnemyFlg) return;

	CalculateReflectePos();

	CalculateReflecteAng();
	
	//���߂��f�[�^���i�[����
	_movingManumalData = m_movingManumalData;
}

const bool ManumalEnemyCollison::GetHitManumalEnemyFlg() const
{
	return m_hitManumalEnemyFlg;
}

void ManumalEnemyCollison::CalculateHitManumalEnemyFlg()
{
	float betweenManumalEnemyLength	= UNIQUELIBRARY.GetVecLength(m_movingManumalData.pos, m_hitEnemyData.pos);	//�}�j���}���ƓG�̋���
	float sumManumalEnemyScale		= m_movingManumalData.scale + m_hitEnemyData.scale;								//�}�j���}���ƓG�̑傫���̍��v
	m_hitManumalEnemyFlg			= betweenManumalEnemyLength < sumManumalEnemyScale;
}

void ManumalEnemyCollison::CalculateReflectePos()
{
	Math::Vector2 betweenVec	= m_movingManumalData.pos - m_hitEnemyData.pos;	//�}�j���}���ƓG�̊Ԃ̃x�N�g��
	betweenVec.Normalize();
	Math::Vector2 reflectedPos	= m_hitEnemyData.pos + betweenVec * (m_movingManumalData.scale + m_hitEnemyData.scale);	//���˂�����̈ʒu
	m_movingManumalData.pos		= reflectedPos;
}

void ManumalEnemyCollison::CalculateReflecteAng()
{
	float collicionAng = -UNIQUELIBRARY.GetVecAng(m_movingManumalData.pos, m_hitEnemyData.pos) + 180.0f;	//�ǂ̕ӂɂԂ����Ă��邩���߂邽�߂̊p�x

	//�ǂ̕ӂɂԂ����Ă��邩���߁A����ɂ��p�x�����߂�
	if (collicionAng <= 135 && collicionAng > 45)			//���̕�
	{
		m_movingManumalData.ang = UNIQUELIBRARY.CalculateReflectAng(m_movingManumalData.ang, 0);
	}
	else if (collicionAng <= 225 && collicionAng > 135)		//���̕�
	{
		m_movingManumalData.ang = UNIQUELIBRARY.CalculateReflectAng(m_movingManumalData.ang, 90);
	}
	else if (collicionAng <= 315 && collicionAng > 225)		//�E�̕�
	{
		m_movingManumalData.ang = UNIQUELIBRARY.CalculateReflectAng(m_movingManumalData.ang, 0);
	}
	else													//��̕�
	{
		m_movingManumalData.ang = UNIQUELIBRARY.CalculateReflectAng(m_movingManumalData.ang, 90);
	}
}
