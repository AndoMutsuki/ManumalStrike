#include"Application/Headers.h"

EffectBase::EffectBase()
{
	m_effectFinishFlg	= false;
	m_nowTime			= 0;
}

EffectBase::~EffectBase()
{
}

void EffectBase::Init(const Math::Vector2& _pos, const float _scale)
{
	m_pos = _pos;
	m_scale = _scale;

	// エフェクトの初期化
	float posCorrectionRaito = 18.0f;
	m_handle = EFFEKSEER.GetManager()->Play(m_effect, { m_pos.x / posCorrectionRaito, m_pos.y / posCorrectionRaito, 0 });
}

void EffectBase::Update()
{
	m_nowTime++;

	if (m_nowTime > m_effectData.timeMax)
	{
		m_effectFinishFlg = true;
	}
}

void EffectBase::Draw()
{
	// マネージャーの更新
	EFFEKSEER.GetManager()->Update();

	//大きさのセット
	float scaleCorrectionRaito = 180.0f;
	EFFEKSEER.GetManager()->SetScale(m_handle, m_scale / scaleCorrectionRaito, m_scale / scaleCorrectionRaito, 1.0f);

	// エフェクトの描画開始処理を行う。
	EFFEKSEER.GetRenderer()->BeginRendering();

	// エフェクトの描画を行う。
	EFFEKSEER.GetManager()->Draw();

	// エフェクトの描画終了処理を行う。
	EFFEKSEER.GetRenderer()->EndRendering();
}

void EffectBase::SetEffectData(const effectData& _effectData)
{
	m_effectData = _effectData;
	m_effect = *(EFFEKSEER.GetEffect(m_effectData.fileName, m_effectData.fileChar));
}

const bool EffectBase::GetEffectFinishFlg() const
{
	return m_effectFinishFlg;
}
