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

	//�}�j���}���֌W
	int			m_nowMoveManumalNum;	//�������Ă���}�j���}���̔ԍ�
	const int	m_nowMoveManumalNumMax = 3;	//�}�j���}���̍ő吔
	bool		m_shotedFlg;			//���łɑł��o���ꂽ�t���O
	bool		m_allManumalStopFlg;	//�S�Ẵ}�j���}�����~�܂��Ă���t���O

	//�G�t�F�N�g�̕`��
	void EffectDraw();

	//�G�t�F�N�V�A�֐�
	Effekseer::EffectRef m_effect;
	Effekseer::Handle m_handle;
	bool m_effectFlg;

	//�}�E�X�֌W
	POINT m_mousePos;
	POINT m_baseMousePos;

};
