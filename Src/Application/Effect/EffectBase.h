#pragma once

class EffectBase
{
public:

	EffectBase();

	~EffectBase();

	void Init(const Math::Vector2& _pos, const float _scale);

	void Update();

	void Draw();

	void SetEffectData(const effectData& _effectData);

	const bool GetEffectFinishFlg()const;

private:

	effectData m_effectData;

	Effekseer::EffectRef	m_effect;
	Effekseer::Handle		m_handle;

	bool			m_effectFinishFlg;
	Math::Vector2	m_pos;
	float			m_scale;
	int				m_nowTime;

};