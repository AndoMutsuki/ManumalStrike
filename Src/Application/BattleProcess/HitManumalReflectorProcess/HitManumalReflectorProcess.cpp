#include"Application/Headers.h"

HitManumalReflectorProcess::HitManumalReflectorProcess()
{
}

HitManumalReflectorProcess::~HitManumalReflectorProcess()
{
}

void HitManumalReflectorProcess::Update(manumalData& _manumalData, ReflectorProcess* _reflectorProcess)
{
	m_manumalData = _manumalData;
	m_reflectorProcess = _reflectorProcess;

	//���˔�薾�炩�ɏ�ɂ���ꍇ�͑������^�[��
	//if (m_manumalData.pos.y > -150) return false;

	//x���W�����˔ɓ������Ă��邩
	float relativePos = m_manumalData.pos.x - m_reflectorProcess->GetPos().x;	//�}�j���}���̑��ΓI�Ȉʒu
	float cosO = cos(DirectX::XMConvertToRadians(m_reflectorProcess->GetAng() + 90));
	bool hitReflectorX = abs(relativePos) - abs(m_reflectorProcess->GetLength() * cosO) > m_manumalData.scale;
	//if (hitReflectorX) return false;

	//y���W�����˔ɓ������Ă��邩
	float tanO = tan(DirectX::XMConvertToRadians(m_reflectorProcess->GetAng() + 90));
	bool hitReflectorY = abs(abs(m_manumalData.pos.y) - abs(-ReflectorPosY + (relativePos * tanO))) > m_manumalData.scale;
	//if (hitReflectorY) return false;

	//���˂̌v�Z
	bool hitReflectorTopFlg = m_manumalData.pos.y > (-ReflectorPosY + (relativePos * tanO));
	if (hitReflectorTopFlg)
	{
		UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.y, (-ReflectorPosY + (relativePos * tanO) + m_manumalData.scale));
		UNIQUELIBRARY.CalculateReflectAng(m_manumalData.ang, m_reflectorProcess->GetAng());
	}
	else
	{
		UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.y, (-ReflectorPosY + (relativePos * tanO) - m_manumalData.scale));
		UNIQUELIBRARY.CalculateReflectAng(m_manumalData.ang, m_reflectorProcess->GetAng() + 90);

		if (m_reflectorProcess->GetAng() > 90)
		{
			m_manumalData.ang = UNIQUELIBRARY.AdjustmentLowerLimit(m_manumalData.ang, 200.0f);
			UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.x, (m_reflectorProcess->GetLength() * cosO - m_reflectorProcess->GetPos().x - m_manumalData.scale));
		}
		else if (m_reflectorProcess->GetAng() < 90)
		{
			m_manumalData.ang = UNIQUELIBRARY.AdjustmentUpperLimit(m_manumalData.ang, 160.0f);
			UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.x, (m_reflectorProcess->GetLength() * cosO + m_reflectorProcess->GetPos().x - m_manumalData.scale));
		}
		else
		{
			if (m_manumalData.pos.x > m_reflectorProcess->GetPos().x)
			{
				m_manumalData.ang = UNIQUELIBRARY.AdjustmentLowerLimit(m_manumalData.ang, 200.0f);
				UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.x, (m_reflectorProcess->GetLength() * cosO - m_reflectorProcess->GetPos().x - m_manumalData.scale));
			}
			else
			{
				m_manumalData.ang = UNIQUELIBRARY.AdjustmentUpperLimit(m_manumalData.ang, 160.0f);
				UNIQUELIBRARY.CalculateReflectPos(m_manumalData.pos.x, (m_reflectorProcess->GetLength() * cosO + m_reflectorProcess->GetPos().x - m_manumalData.scale));
			}
		}
	}

	//return true;
}
