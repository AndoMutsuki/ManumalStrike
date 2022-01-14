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
	ManumalAttackCircle*		m_manumalAttackCircle = nullptr;

	std::vector<ManumalBase*>	m_manumalList;
	std::vector<EnemyBase*>		m_enemyList;
	FriendshipComboBase*		m_frendshipCombo = nullptr;
	EnemyAttackBase*			m_enemyAttack = nullptr;
	std::vector<EffectBase*>	m_effectList;

	void SetFriendshipCombo(frendshipComboType _frendshipComboType, const Math::Vector2& _pos);
	void SetEnemyAttack(enemyAttackType _enemyAttackType, const Math::Vector2& _pos);

	//マニュマル関係
	int			m_nowMoveManumalNum;	//今動いているマニュマルの番号
	const int	m_nowMoveManumalNumMax = 3;	//マニュマルの最大数
	bool		m_shotedFlg;			//すでに打ち出されたフラグ
	bool		m_allManumalStopFlg;	//全てのマニュマルが止まっているフラグ

	//マウス関係
	POINT m_mousePos;
	POINT m_baseMousePos;

};
