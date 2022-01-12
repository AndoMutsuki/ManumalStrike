#pragma once

class BattleScene :public SceneBase
{
public:

	BattleScene();

	~BattleScene();

	void Update() override;

	void Draw2D() override;

private:

	MouseProcess*				m_mouseProcess = nullptr;
	FirstShotProcess*			m_firstShotProcess = nullptr;
	ReflectorProcess*			m_reflectorProcess = nullptr;
	ManumalMutualCollision*		m_manumalMutualCollision = nullptr;
	ManumalEnemyCollison*		m_manumalEnemyCollison = nullptr;
	HitManumalWallProcess*		m_hitManumalwallProcess = nullptr;
	HitManumalReflectorProcess* m_hitManumalReflectorProcess = nullptr;
	CalculateHP*				m_calculateHP = nullptr;
	CalculateSpeed*				m_calculateSpeed = nullptr;
	DrawProcess*				m_drawProcess = nullptr;
	std::vector<ManumalBase*>	m_manumalList;
	std::vector<EnemyBase*>		m_enemyList;

	//マニュマル関係
	int			m_nowMoveManumalNum;	//今動いているマニュマルの番号
	const int	m_nowMoveManumalNumMax = 3;	//マニュマルの最大数
	bool		m_shotedFlg;			//すでに打ち出されたフラグ
	bool		m_allManumalStopFlg;	//全てのマニュマルが止まっているフラグ

	//エフェクトの描画
	void EffectDraw();

	//エフェクシア関数
	Effekseer::EffectRef m_effect;
	Effekseer::Handle m_handle;
	bool m_effectFlg;

	//マウス関係
	POINT m_mousePos;
	POINT m_baseMousePos;

};
