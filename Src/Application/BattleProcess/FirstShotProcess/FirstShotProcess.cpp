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
	float manumalMouseLength	= UNIQUELIBRARY.GetVecLength(m_manumalData.pos, Math::Vector2{ m_nowMousePos.x,m_nowMousePos.y });	//マニュマルとマウスの長さ
	bool hitManumalMouse		= manumalMouseLength < m_manumalData.scale;	//マニュマルとマウスが当たっているか
	if (!hitManumalMouse) return;

	bool firstTouchFlg = m_firstMousePos == Math::Vector2::Zero;	//初めてマニュマルに触ったかどうか
	if (!firstTouchFlg) return;

	//マニュマルをクリックしたとき、最初に一回行う処理
	m_keepManumalFlg	= true;
	m_firstMousePos		= { m_nowMousePos.x,m_nowMousePos.y };
}

void FirstShotProcess::NoClickProcess()
{
	bool touchedFlg = m_firstMousePos != Math::Vector2::Zero;	//すでに触っているかどうか

	//マウスの最初の位置を初期化
	m_firstMousePos = Math::Vector2::Zero;

	if (!touchedFlg) return;

	//打ち出された瞬間の処理
	m_keepManumalFlg = false;
	SetManumalFirstShotData();
}

void FirstShotProcess::SetManumalFirstShotData()
{
	//パワーを入れる
	m_manumalData.power = m_arrowSpeed;

	//角度を入れる
	float arrowAng		= UNIQUELIBRARY.GetVecAng(m_firstMousePos, Math::Vector2{ m_nowMousePos.x,m_nowMousePos.y });
	m_manumalData.ang	= -m_arrowAng;
}

void FirstShotProcess::CalculateArrowSpeed()
{
	//矢印のスピードを計算
	m_arrowSpeed = UNIQUELIBRARY.GetVecLength(Math::Vector2{ m_nowMousePos.x,m_nowMousePos.y }, m_firstMousePos) / 10.0f;

	//スピードの補正
	bool arrowSpeedMinLess = m_arrowSpeed < m_arrowSpeedMin;	//スピードが下限より下であるか
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

	float arrowScaleY		= (m_arrowSpeed - m_arrowSpeedFixed) / m_arrowSpeedMax;	//矢印の大きさのY座標
	Math::Matrix scaleMat	= DirectX::XMMatrixScaling(1.0f, arrowScaleY, 0);

	m_arrowAng			= UNIQUELIBRARY.GetVecAng(m_firstMousePos, Math::Vector2{ m_nowMousePos.x,m_nowMousePos.y });
	Math::Matrix rotMat = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(-m_arrowAng));

	Math::Matrix transMat = DirectX::XMMatrixTranslation(m_manumalData.pos.x, m_manumalData.pos.y, 0);

	m_arrowMat = scaleMat * rotMat * transMat;
}

const bool FirstShotProcess::DoCalculateArrowMat()
{
	if (!m_keepManumalFlg)return false;

	bool arrowMinOverFlg = m_arrowSpeed != 0;	//初期スピードがあるか
	if (!arrowMinOverFlg)return false;

	return true;
}
