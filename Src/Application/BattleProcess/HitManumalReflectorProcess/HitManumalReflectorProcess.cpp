#include"Application/Headers.h"

HitManumalReflectorProcess::HitManumalReflectorProcess()
{
	m_hitReflectorFlg	= false;
	m_relativePosX		= 0;
	m_cosO				= 0;
	m_tanO				= 0;
}

HitManumalReflectorProcess::~HitManumalReflectorProcess()
{
}

void HitManumalReflectorProcess::Update(manumalData& _manumalData, ReflectorProcess* _reflectorProcess)
{
	m_hitReflectorFlg = false; 

	//�����o�ϐ��ɕϊ�����
	m_manumalData		= _manumalData;
	m_reflectorProcess	= _reflectorProcess;

	if (m_manumalData.pos.y > -100)	return;		//���˔�薾�炩�ɏ�ɂ���ꍇ�͑������^�[��

	if (!HitManumalReflectorX())	return;		//X���W�����˔ɓ������Ă��Ȃ��ꍇ�͑������^�[��

	if (!HitManumalReflectorY())	return;		//Y���W�����˔ɓ������Ă��Ȃ��ꍇ�͑������^�[��

	m_hitReflectorFlg = true;

	//���˂̌v�Z
	bool hitReflectorTopFlg = m_manumalData.pos.y > (-ReflectorPosY + (m_relativePosX * m_tanO));	//���˔̏ォ�瓖�����Ă��邩
	if (hitReflectorTopFlg)
	{
		HitReflectorTopProcess();
	}
	else
	{
		HitReflectorBottomProcess();
	}

	//���߂��f�[�^���i�[����
	_manumalData = m_manumalData;
}

const bool HitManumalReflectorProcess::GetHitReflectorFlg() const
{
	return m_hitReflectorFlg;
}

const bool HitManumalReflectorProcess::HitManumalReflectorX()
{
	m_relativePosX		= m_manumalData.pos.x - m_reflectorProcess->GetPos().x;
	m_cosO				= cos(DirectX::XMConvertToRadians(m_reflectorProcess->GetAng() + 90));
	bool hitReflectorX	= abs(m_relativePosX) - abs(m_reflectorProcess->GetLength() * m_cosO) < m_manumalData.scale;	//X���W�����˔ɓ������Ă��邩
	return hitReflectorX;
}

const bool HitManumalReflectorProcess::HitManumalReflectorY()
{
	m_tanO				= tan(DirectX::XMConvertToRadians(m_reflectorProcess->GetAng() + 90));
	bool hitReflectorY	= abs(abs(m_manumalData.pos.y) - abs(-ReflectorPosY + (m_relativePosX * m_tanO))) < m_manumalData.scale;	//Y���W�����˔ɓ������Ă��邩
	return hitReflectorY;
}

void HitManumalReflectorProcess::HitReflectorTopProcess()
{
	m_manumalData.pos.y = UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.y, (-ReflectorPosY + (m_relativePosX * m_tanO) + m_manumalData.scale));
	m_manumalData.ang	= UNIQUELIBRARY.CalculateReflectAng(m_manumalData.ang, m_reflectorProcess->GetAng());
}

void HitManumalReflectorProcess::HitReflectorBottomProcess()
{
	m_manumalData.pos.y = UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.y, (-ReflectorPosY + (m_relativePosX * m_tanO) - m_manumalData.scale));
	m_manumalData.ang	= UNIQUELIBRARY.CalculateReflectAng(m_manumalData.ang, m_reflectorProcess->GetAng() + 90);

	bool reflectorRightUpFlg	= m_reflectorProcess->GetAng() > 90;	//���˔̉E�[���オ���Ă��邩
	bool reflectorLeftUpFlg		= m_reflectorProcess->GetAng() < 90;	//���˔̍��[���オ���Ă��邩
	if (reflectorRightUpFlg)
	{
		ReflectorRightUpProcess();
	}
	else if (reflectorLeftUpFlg)
	{
		ReflectorLeftUpProcess();
	}
	else	//���˔����s
	{
		bool manumalRightComeFlg = m_manumalData.pos.x > m_reflectorProcess->GetPos().x;	//���˔̉E�����瓖�����Ă��邩
		if (manumalRightComeFlg)
		{
			ManumalRightComeProcess();
		}
		else
		{
			ManumalLefttComeProcess();
		}
	}
}

void HitManumalReflectorProcess::ReflectorRightUpProcess()
{
	m_manumalData.ang	= UNIQUELIBRARY.AdjustmentLowerLimit(m_manumalData.ang, 200.0f);
	m_manumalData.pos.x = UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.x, (m_reflectorProcess->GetPos().x + (abs(m_relativePosX) * m_tanO) + m_manumalData.scale));
}

void HitManumalReflectorProcess::ReflectorLeftUpProcess()
{
	m_manumalData.ang	= UNIQUELIBRARY.AdjustmentUpperLimit(m_manumalData.ang, 160.0f);
	m_manumalData.pos.x = UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.x, (m_reflectorProcess->GetPos().x + (abs(m_relativePosX) * m_tanO) - m_manumalData.scale));
}

void HitManumalReflectorProcess::ManumalRightComeProcess()
{
	m_manumalData.ang	= UNIQUELIBRARY.AdjustmentLowerLimit(m_manumalData.ang, 200.0f);
	m_manumalData.pos.x = UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.x, (m_reflectorProcess->GetLength() * m_cosO - m_reflectorProcess->GetPos().x - m_manumalData.scale));
}

void HitManumalReflectorProcess::ManumalLefttComeProcess()
{
	m_manumalData.ang	= UNIQUELIBRARY.AdjustmentUpperLimit(m_manumalData.ang, 160.0f);
	m_manumalData.pos.x = UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.x, (m_reflectorProcess->GetLength() * m_cosO + m_reflectorProcess->GetPos().x - m_manumalData.scale));
}
