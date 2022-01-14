#pragma once

class BattleScene :public SceneBase
{
public:

	BattleScene();

	~BattleScene();

	void Update() override;

	void Draw2D() override;

private:

	//HPの処理
	const bool HPProcess();

	//HPの計算
	void CalculateHPDeath();

	//最初に打ち出す処理
	void FirstShotProcessBattleScene();

	//次のマニュマルの発射に移る
	void NextManumalProcess();

	//敵の攻撃の処理
	void EnemyAttackProcess();

	//敵の攻撃の設定
	void SetEnemyAttack(enemyAttackType _enemyAttackType, const Math::Vector2& _pos);

	//打ち出すマニュマルの円のエフェクトの処理
	void ShotCircleProcess();

	//マニュマル同士の当たり判定の処理
	void ManumalMutualCollisionProcess();

	//マニュマル同士で当たっていたときの処理
	void HitedManumalMutualCollisionProcess(std::vector<ManumalBase*>::iterator _iter);

	//友情コンボの設定
	void SetFriendshipCombo(frendshipComboType _frendshipComboType, const Math::Vector2& _pos);

	//マニュマルと敵の当たり判定の処理
	void ManumalEnemyCollisonProcess();

	//反射板で跳ね返る処理
	void HitManumalReflectorProcessBattleScene();

	//壁で跳ね返る処理
	void HitManumalwallProcessBattleScene();

	//エフェクト関係
	void EffectProcess();

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

	//マニュマル関係
	int			m_nowMoveManumalNum;	//今動いているマニュマルの番号
	const int	m_nowMoveManumalNumMax = 3;	//マニュマルの最大数
	bool		m_shotedFlg;			//すでに打ち出されたフラグ
	bool		m_allManumalStopFlg;	//全てのマニュマルが止まっているフラグ

	//マウス関係
	POINT m_mousePos;
	POINT m_baseMousePos;

};
