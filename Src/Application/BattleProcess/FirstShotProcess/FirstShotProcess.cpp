#include"Application/Headers.h"

using namespace ManumalStrikeNamespace;

FirstShotProcess::FirstShotProcess()
{
	m_arrowTex = TEXMANA.GetTex("Data/Texture/BattleScene/arrow.png");
	m_touchingFlg = false;
	m_firstMousePos = Math::Vector2::Zero;
	m_arrowSpeed = 0;
	m_arrowAng = 0;	
	m_arrowMat = Math::Matrix::Identity;
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
	float manumalMouseLength = UNIQUELIBRARY.GetVecLength(m_manumalData.pos, Math::Vector2{ m_nowMousePos.x,m_nowMousePos.y });
	bool hitManumalMouse = manumalMouseLength < m_manumalData.scale;
	if (hitManumalMouse)
	{
		bool firstTouchFlg = m_firstMousePos == Math::Vector2::Zero;	//初めてマニュマルに触ったかどうか
		if (firstTouchFlg)
		{
			m_touchingFlg = true;
			m_firstMousePos = { m_nowMousePos.x,m_nowMousePos.y };
		}
	}
}

void FirstShotProcess::NoClickProcess()
{
	bool touchedFlg = m_firstMousePos != Math::Vector2::Zero;	//すでに触っているかどうか
	if (touchedFlg)
	{
		m_touchingFlg = false;
		SetManumalFirstShotData();
	}

	m_firstMousePos = Math::Vector2::Zero;
}

void FirstShotProcess::SetManumalFirstShotData()
{
	m_manumalData.power = m_arrowSpeed;
	float arrowAng = UNIQUELIBRARY.GetVecAng(m_firstMousePos, Math::Vector2{ m_nowMousePos.x,m_nowMousePos.y });
	m_manumalData.ang = -m_arrowAng;
}

void FirstShotProcess::CalculateArrowSpeed()
{
	m_arrowSpeed = UNIQUELIBRARY.GetVecLength(Math::Vector2{ m_nowMousePos.x,m_nowMousePos.y }, m_firstMousePos) / 10.0f;
	if (m_arrowSpeed < m_arrowSpeedMin)
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
	if (DoCalculateArrowMat())
	{
		Math::Matrix scaleMat = DirectX::XMMatrixScaling(1.0f, (m_arrowSpeed - m_arrowSpeedFixed) / m_arrowSpeedMax, 0);
		m_arrowAng = UNIQUELIBRARY.GetVecAng(m_firstMousePos, Math::Vector2{ m_nowMousePos.x,m_nowMousePos.y });
		Math::Matrix rotMat = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(-m_arrowAng));
		Math::Matrix transMat = DirectX::XMMatrixTranslation(m_manumalData.pos.x, m_manumalData.pos.y, 0);
		m_arrowMat = scaleMat * rotMat * transMat;
	}
}

const bool FirstShotProcess::DoCalculateArrowMat()
{
	if (!m_touchingFlg)return false;
	bool arrowMinOverFlg = m_arrowSpeed != 0;	//初期スピードがあるか
	if (!arrowMinOverFlg)return false;
	return true;
}
