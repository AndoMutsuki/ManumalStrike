#pragma once

class BattleScene :public SceneBase
{
public:

	BattleScene();

	~BattleScene();

	void Update() override;

	void Draw2D() override;

private:

	//HP�̏���
	const bool HPProcess();

	//HP�̌v�Z
	void CalculateHPDeath();

	//�ŏ��ɑł��o������
	void FirstShotProcessBattleScene();

	//���̃}�j���}���̔��˂Ɉڂ�
	void NextManumalProcess();

	//�G�̍U���̏���
	void EnemyAttackProcess();

	//�G�̍U���̐ݒ�
	void SetEnemyAttack(enemyAttackType _enemyAttackType, const Math::Vector2& _pos);

	//�ł��o���}�j���}���̉~�̃G�t�F�N�g�̏���
	void ShotCircleProcess();

	//�}�j���}�����m�̓����蔻��̏���
	void ManumalMutualCollisionProcess();

	//�}�j���}�����m�œ������Ă����Ƃ��̏���
	void HitedManumalMutualCollisionProcess(std::vector<ManumalBase*>::iterator _iter);

	//�F��R���{�̐ݒ�
	void SetFriendshipCombo(frendshipComboType _frendshipComboType, const Math::Vector2& _pos);

	//�}�j���}���ƓG�̓����蔻��̏���
	void ManumalEnemyCollisonProcess();

	//���˔Œ��˕Ԃ鏈��
	void HitManumalReflectorProcessBattleScene();

	//�ǂŒ��˕Ԃ鏈��
	void HitManumalwallProcessBattleScene();

	//�G�t�F�N�g�֌W
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

	//�}�j���}���֌W
	int			m_nowMoveManumalNum;	//�������Ă���}�j���}���̔ԍ�
	const int	m_nowMoveManumalNumMax = 3;	//�}�j���}���̍ő吔
	bool		m_shotedFlg;			//���łɑł��o���ꂽ�t���O
	bool		m_allManumalStopFlg;	//�S�Ẵ}�j���}�����~�܂��Ă���t���O

	//�}�E�X�֌W
	POINT m_mousePos;
	POINT m_baseMousePos;

};
