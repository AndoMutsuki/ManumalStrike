#include"Application/Headers.h"

FirstShotProcess::FirstShotProcess()
{
	m_arrowTex			= TEXMANA.GetTex("Data/Texture/BattleScene/arrow.png");
	m_keepManumalFlg	= false;
	m_firstMousePos		= Math::Vector2::Zero;
	m_arrowSpeed		= 0;
	m_arrowAng			= 0;
	m_arrowMat			= Math::Matrix::Identity;
}

FirstShotProcess::~FirstShotProcess()
{
}

void FirstShotProcess::Update(manumalData& _manumalData, const POINT& _mouse)
{
	m_manumalData = _manumalData;
	m_nowMousePos = { (float)_mouse.x,(float)_mouse.y };

	CalculateFirstMousePos();

	CalculateArrowSpeed();

	CalculateArrowMat();

	_manumalData = m_manumalData;
}

void FirstShotProcess::DrawArrow() const
{
	UNIQUELIBRARY.Draw2D(m_arrowMat, m_arrowTex, 200, 1000, 0.8f);
}

const bool FirstShotProcess::GetClickFlg()
{
	return m_keepManumalFlg;
}

const bool FirstShotProcess::GetArrowDrawFlg()
{
	return DoCalculateArrowMat();
}

void FirstShotProcess::CalculateFirstMousePos()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		ClickProcess();
	}
	else
	{
		NoClickProcess();
	}
}

void FirstShotProcess::ClickProcess()
{
	float manumalMouseLength	= UNIQUELIBRARY.GetVecLength(m_manumalData.pos, Math::Vector2{ m_nowMousePos.x,m_nowMousePos.y });	//�}�j���}���ƃ}�E�X�̒���
	bool hitManumalMouse		= manumalMouseLength < m_manumalData.scale;	//�}�j���}���ƃ}�E�X���������Ă��邩
	if (!hitManumalMouse) return;

	bool firstTouchFlg = m_firstMousePos == Math::Vector2::Zero;	//���߂ă}�j���}���ɐG�������ǂ���
	if (!firstTouchFlg) return;

	//�}�j���}�����N���b�N�����Ƃ��A�ŏ��Ɉ��s������
	m_keepManumalFlg	= true;
	m_firstMousePos		= { m_nowMousePos.x,m_nowMousePos.y };
}

void FirstShotProcess::NoClickProcess()
{
	bool touchedFlg = m_firstMousePos != Math::Vector2::Zero;	//���łɐG���Ă��邩�ǂ���

	//�}�E�X�̍ŏ��̈ʒu��������
	m_firstMousePos = Math::Vector2::Zero;

	if (!touchedFlg) return;

	//�ł��o���ꂽ�u�Ԃ̏���
	m_keepManumalFlg = false;
	SetManumalFirstShotData();
}

void FirstShotProcess::SetManumalFirstShotData()
{
	//�p���[������
	m_manumalData.power = m_arrowSpeed;

	//�p�x������
	float arrowAng		= UNIQUELIBRARY.GetVecAng(m_firstMousePos, Math::Vector2{ m_nowMousePos.x,m_nowMousePos.y });
	m_manumalData.ang	= -m_arrowAng;
}

void FirstShotProcess::CalculateArrowSpeed()
{
	//���̃X�s�[�h���v�Z
	m_arrowSpeed = UNIQUELIBRARY.GetVecLength(Math::Vector2{ m_nowMousePos.x,m_nowMousePos.y }, m_firstMousePos) / 10.0f;

	//�X�s�[�h�̕␳
	bool arrowSpeedMinLess = m_arrowSpeed < m_arrowSpeedMin;	//�X�s�[�h��������艺�ł��邩
	if (arrowSpeedMinLess)
	{
		m_arrowSpeed = 0;
	}
	else
	{
		m_arrowSpeed = UNIQUELIBRARY.AdjustmentUpperLimit(m_arrowSpeed, m_arrowSpeedMax) + m_arrowSpeedFixed;
	}
}

void FirstShotProcess::CalculateArrowMat()
{
	if (!DoCalculateArrowMat()) return;

	float arrowScaleY		= (m_arrowSpeed - m_arrowSpeedFixed) / m_arrowSpeedMax;	//���̑傫����Y���W
	Math::Matrix scaleMat	= DirectX::XMMatrixScaling(1.0f, arrowScaleY, 0);

	m_arrowAng			= UNIQUELIBRARY.GetVecAng(m_firstMousePos, Math::Vector2{ m_nowMousePos.x,m_nowMousePos.y });
	Math::Matrix rotMat = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(-m_arrowAng));

	Math::Matrix transMat = DirectX::XMMatrixTranslation(m_manumalData.pos.x, m_manumalData.pos.y, 0);

	m_arrowMat = scaleMat * rotMat * transMat;
}

const bool FirstShotProcess::DoCalculateArrowMat()
{
	if (!m_keepManumalFlg)return false;

	bool arrowMinOverFlg = m_arrowSpeed != 0;	//�����X�s�[�h�����邩
	if (!arrowMinOverFlg)return false;

	return true;
}