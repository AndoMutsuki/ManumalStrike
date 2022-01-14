#include"Application/Headers.h"

BattleScene::BattleScene()
{
	m_mouseProcess = new MouseProcess;
	m_firstShotProcess = new FirstShotProcess;
	m_reflectorProcess = new ReflectorProcess;
	m_manumalMutualCollision = new ManumalMutualCollision;
	m_manumalEnemyCollison = new ManumalEnemyCollison;
	m_hitManumalwallProcess = new HitManumalWallProcess;
	m_hitManumalReflectorProcess = new HitManumalReflectorProcess;
	m_calculateHP = new CalculateHP;
	m_calculateSpeed = new CalculateSpeed;
	m_drawProcess = new DrawProcess;
	m_manumalAttackCircle = new ManumalAttackCircle;

	m_manumalList.clear();
	m_manumalList.push_back(new Raibit);
	m_manumalList.push_back(new Morumon);
	m_manumalList.push_back(new Pebrat);
	m_manumalList[0]->SetPos({ -200,-100 });
	m_manumalList[1]->SetPos({ 0,-120 });
	//m_manumalList[2]->SetPos({ 200,-100 });
	m_manumalList[2]->SetPos({ -350,230 });
	m_enemyList.clear();
	m_enemyList.push_back(new FireCube);
	m_enemyList.push_back(new FireCube);
	m_enemyList.push_back(new Hinokokko);
	m_enemyList[0]->SetEnemyPos({ -400,250 });
	m_enemyList[1]->SetEnemyPos({ 350,100 });
	m_enemyList[2]->SetEnemyPos({ 0,120 });
	m_effectList.clear();

	//�ő�HP���v�Z
	int HPMax = std::accumulate(m_manumalList.begin(), m_manumalList.end(), 0,
		[](int HP, ManumalBase* manumalBase) { return HP + manumalBase->GetManumalData().HP; });
	m_calculateHP->SetHPMax(HPMax);

	//�}�j���}���֌W
	m_nowMoveManumalNum = 0;
	m_shotedFlg = false;

	//�}�E�X
	m_baseMousePos = { 1280 / 2, 720 / 2 };
	ScreenToClient(APP.m_window.GetWndHandle(), &m_mousePos);
	SetCursorPos(m_baseMousePos.x, m_baseMousePos.y);
}

BattleScene::~BattleScene()
{
	delete m_mouseProcess;
	delete m_firstShotProcess;
	delete m_reflectorProcess;
	delete m_manumalMutualCollision;
	delete m_manumalEnemyCollison;
	delete m_hitManumalwallProcess;
	delete m_hitManumalReflectorProcess;
	delete m_drawProcess;
	delete m_manumalAttackCircle;

	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		delete* iter;
	}
	m_manumalList.clear();

	for (auto iter = m_enemyList.begin(); iter != m_enemyList.end(); ++iter)
	{
		delete* iter;
	}
	m_enemyList.clear();

	for (auto iter = m_effectList.begin(); iter != m_effectList.end(); ++iter)
	{
		delete* iter;
	}
	m_effectList.clear();
}

void BattleScene::Update()
{
	//�}�E�X�̏���
	m_mousePos = m_mouseProcess->Update(m_mousePos);

	//HP�̏���
	bool aliveFlg = HPProcess();	//�v���C���[�������Ă��邩�̃t���O
	if (!aliveFlg)return;			//����ł����瑁�����^�[��

	//�}�j���}�����ł��o���ꂽ��t���O�𗧂Ă�
	bool shotFlg = m_firstShotProcess->DoCalculateArrowMat() && !GetAsyncKeyState(MK_LBUTTON);
	if (shotFlg)
	{
		m_shotedFlg = true;
	}

	//�ł��o����}�j���}���ɉ~�̃G�t�F�N�g��t����
	if (!m_shotedFlg)
	{
		m_manumalAttackCircle->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalData());
	}

	//�ŏ��ɑł��o������
	FirstShotProcessBattleScene();

	//���˔̏���
	m_reflectorProcess->Update(m_firstShotProcess->GetClickFlg());

	//�X�s�[�h�̌v�Z
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		m_calculateSpeed->Update((*iter)->GetManumalDataKinetic());
	}

	//�S�Ẵ}�j���}�����~�܂��Ă��邩
	m_allManumalStopFlg = std::all_of(m_manumalList.begin(), m_manumalList.end(),
		[](ManumalBase* manumalBase) {return manumalBase->GetManumalData().nowSpeed <= 0; });

	//���̃}�j���}���̔��˂Ɉڂ�
	NextManumalProcess();

	//�}�j���}���̈ړ�����
	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::MoveProcess));

	//�}�j���}�����m�̓����蔻��
	ManumalMutualCollisionProcess();

	//�}�j���}���ƓG�̓����蔻��
	ManumalEnemyCollisonProcess();

	//���˔Œ��˕Ԃ鏈��
	HitManumalReflectorProcessBattleScene();

	//�ǂŒ��˕Ԃ鏈��
	HitManumalwallProcessBattleScene();

	//�}�j���}���̍s��̌v�Z
	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::CalculateMatrix));

	//HP�̃Z�b�g
	m_drawProcess->SetHPRaito(m_calculateHP->GetHPRaito());

	//UI�֌W�̏���
	m_drawProcess->Update();

	//�G�t�F�N�g�֌W
	EffectProcess();
}

void BattleScene::Draw2D()
{
	SHADER.m_spriteShader.Begin();

	m_drawProcess->Draw();

	if (!m_shotedFlg)
	{
		m_manumalAttackCircle->Draw();
	}

	for (auto iter = m_enemyList.begin(); iter != m_enemyList.end(); ++iter)
	{
		if (!(*iter)->GetAliveFlg())continue;

		(*iter)->Draw();
	}

	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::Draw));

	m_reflectorProcess->Draw();

	if (m_firstShotProcess->GetArrowDrawFlg())
	{
		m_firstShotProcess->DrawArrow();
	}

	std::for_each(m_effectList.begin(), m_effectList.end(),
		std::mem_fun(&EffectBase::Draw));

	SHADER.m_spriteShader.End();
}

const bool BattleScene::HPProcess()
{
	m_calculateHP->Update();
	if (!m_calculateHP->GetAliveFlg())
	{
		CalculateHPDeath();
		return false;
	}

	return true;
}

void BattleScene::CalculateHPDeath()
{
	m_drawProcess->SetHPRaito(m_calculateHP->GetHPRaito());
	m_drawProcess->Update();
}

void BattleScene::FirstShotProcessBattleScene()
{
	bool moveFlg = m_manumalList[m_nowMoveManumalNum]->GetManumalData().nowSpeed > 0;	//�ł��o���}�j���}���������Ă��邩

	//�}�j���}�����~�܂��Ă�����
	if (!moveFlg)
	{
		//�ŏ��ɑł��o������
		m_firstShotProcess->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalDataKinetic(), m_mousePos);

		//�x�N�g���̌v�Z
		m_manumalList[m_nowMoveManumalNum]->CalculateMoveVec();
	}
}

void BattleScene::NextManumalProcess()
{
	bool nextManumalFlg = m_shotedFlg && m_allManumalStopFlg;
	if (!nextManumalFlg)return;

	m_shotedFlg = false;

	//�F��R���{�I���̃t���O������
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		(*iter)->GetManumalDataKinetic().friendFinishFlg = false;
	}

	//�G�̍U���̏���
	EnemyAttackProcess();

	//�ł��o���}�j���}���̉~�̃G�t�F�N�g�̏���
	ShotCircleProcess();

	return;
}

void BattleScene::EnemyAttackProcess()
{
	for (auto iter = m_enemyList.begin(); iter != m_enemyList.end(); ++iter)
	{
		//�G������ł�����ʂ���
		if (!(*iter)->GetAliveFlg())continue;

		//�U���̃^�[���������炷
		(*iter)->GetEnemyDataKinetic().nowAttackTurn--;

		//�܂��U������^�[�����ł͂Ȃ��ꍇ�ʂ���
		if ((*iter)->GetEnemyDataKinetic().nowAttackTurn != 0)continue;

		//�^�[�������ő�l�ɖ߂�
		(*iter)->GetEnemyDataKinetic().nowAttackTurn = (*iter)->GetEnemyData().attackTurn;

		//�G�̍U�����Z�b�g����
		SetEnemyAttack((*iter)->GetEnemyData().attackType, (*iter)->GetEnemyData().pos);
		if (m_enemyAttack != nullptr)
		{
			//�_���[�W���Z�o����
			m_enemyAttack->Update((*iter)->GetEnemyDataKinetic(), m_manumalList);
			m_calculateHP->SetDamage(m_enemyAttack->GetDamage());
		}

		//�f���[�g
		delete m_enemyAttack;
		m_enemyAttack = nullptr;
	}
}

void BattleScene::SetEnemyAttack(enemyAttackType _enemyAttackType, const Math::Vector2& _pos)
{
	switch (_enemyAttackType)
	{
	case enemyAttackType::BEAM:
		m_enemyAttack = nullptr;
		break;

	case enemyAttackType::EXPLOSION:
		m_enemyAttack = new Explosion;
		m_effectList.push_back(new ExplosionEffect);
		break;

	case enemyAttackType::BIGEXPLOSION:
		m_enemyAttack = new BigExplosion;
		m_effectList.push_back(new ExplosionEffect);
		break;

	default:
		m_frendshipCombo = nullptr;
		assert(!"�G�̍U���^�C�v�ɕs���Ȓl");
		break;
	}

	m_effectList[m_effectList.size() - 1]->Init(_pos, m_enemyAttack->GetRange());
}

void BattleScene::ShotCircleProcess()
{
	//���̃}�j���}����ł��o��
	m_nowMoveManumalNum++;
	if (m_nowMoveManumalNum >= m_nowMoveManumalNumMax)
	{
		m_nowMoveManumalNum = 0;
	}

	//�~�̃G�t�F�N�g�̏������s��
	m_manumalAttackCircle->Init();
	m_manumalAttackCircle->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalData());
}

void BattleScene::ManumalMutualCollisionProcess()
{
	//�����Ă���}�j���}���Ǝ~�܂��Ă���}�j���}���̓����蔻��
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		//����̃}�j���}���̏ꍇ�͏��O����
		if (m_manumalList[m_nowMoveManumalNum] == *iter)continue;

		//�����蔻��
		m_manumalMutualCollision->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalData(), (*iter)->GetManumalDataKinetic());

		//�������Ă��Ȃ�Ώ���
		if (!m_manumalMutualCollision->GetHitManumalMutualFlg())continue;

		//�������Ă������̏���
		HitedManumalMutualCollisionProcess(iter);
	}

	//�~�܂��Ă���}�j���}�����m�̓����蔻��
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		for (auto iter2 = m_manumalList.begin(); iter2 != m_manumalList.end(); ++iter2)
		{
			//�����Ă���}�j���}���͏���
			if (m_manumalList[m_nowMoveManumalNum] == *iter)continue;

			//�����Ă���}�j���}���͏���
			if (m_manumalList[m_nowMoveManumalNum] == *iter2)continue;

			//����̃}�j���}���̏ꍇ�͏��O����
			if (iter == iter2)continue;

			//�����蔻��
			m_manumalMutualCollision->Update((*iter)->GetManumalDataKinetic(), (*iter2)->GetManumalDataKinetic());

			//�������Ă��Ȃ���Ώ���
			if (!m_manumalMutualCollision->GetHitManumalMutualFlg())continue;

			//�������Ă������̏���
			(*iter)->CalculateMoveVec();
			(*iter2)->CalculateMoveVec();

		}
	}
}

void BattleScene::HitedManumalMutualCollisionProcess(std::vector<ManumalBase*>::iterator _iter)
{
	//�F��R���{�̏���
	//���łɗF��R���{�𔭓����Ă����烊�^�[��
	if ((*_iter)->GetManumalData().friendFinishFlg)return;

	//�F��R���{�t���O�����Ă�
	(*_iter)->GetManumalDataKinetic().friendFinishFlg = true;

	//�F��R���{���Z�b�g����
	SetFriendshipCombo((*_iter)->GetManumalData().frendshipType, (*_iter)->GetManumalData().pos);
	if (m_frendshipCombo != nullptr)
	{
		//�F��R���{�̏���
		m_frendshipCombo->Update((*_iter)->GetManumalDataKinetic(), m_enemyList);
	}

	//�x�N�g���̌v�Z
	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::CalculateMoveVec));

	//�f���[�g
	delete m_frendshipCombo;
	m_frendshipCombo = nullptr;
}

void BattleScene::SetFriendshipCombo(frendshipComboType _frendshipComboType, const Math::Vector2& _pos)
{
	switch (_frendshipComboType)
	{
	case frendshipComboType::BEAM:
		m_enemyAttack = nullptr;
		break;

	case frendshipComboType::EXPLOSION:
		m_frendshipCombo = new FriendExplosion;
		m_effectList.push_back(new ExplosionEffect);
		break;

	default:
		m_enemyAttack = nullptr;
		assert(!"�G�̍U���^�C�v�ɕs���Ȓl");
		break;
	}

	m_effectList[m_effectList.size() - 1]->Init(_pos, m_frendshipCombo->GetRange());
}

void BattleScene::ManumalEnemyCollisonProcess()
{
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		for (auto iterE = m_enemyList.begin(); iterE != m_enemyList.end(); ++iterE)
		{
			//�G������ł����珜��
			if (!(*iterE)->GetAliveFlg())continue;

			//�}�j���}���ƓG�̓����蔻��
			m_manumalEnemyCollison->Update((*iter)->GetManumalDataKinetic(), (*iterE)->GetEnemyData());

			//�������Ă��Ȃ���Ώ���
			if (!m_manumalEnemyCollison->GetHitManumalEnemyFlg())continue;

			//�s��̌v�Z
			(*iter)->CalculateMoveVec();

			//���������}�j���}���������Ă��Ȃ��Ȃ珜�O
			if (m_manumalList[m_nowMoveManumalNum] != *iter)continue;

			//���������}�j���}���������Ă�����_���[�W�̏���
			(*iterE)->SetDamage((int)(*iter)->GetManumalData().attack);
		}
	}
}

void BattleScene::HitManumalReflectorProcessBattleScene()
{
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		//���˔Œ��˕Ԃ鏈��
		m_hitManumalReflectorProcess->Update((*iter)->GetManumalDataKinetic(), m_reflectorProcess);

		//���˔ɓ������Ă��Ȃ������珜�O
		if (!m_hitManumalReflectorProcess->GetHitReflectorFlg())continue;

		//���˔ɓ������Ă���Ƃ��̏���
		(*iter)->CalculateMoveVec();
	}
}

void BattleScene::HitManumalwallProcessBattleScene()
{
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		//�ǂŒ��˕Ԃ鏈��
		m_hitManumalwallProcess->Update((*iter)->GetManumalDataKinetic());

		//�ǂɓ������Ă��Ȃ������珜�O
		if (!m_hitManumalwallProcess->GetHitWallFlg())continue;

		//�ǂɓ������Ă���Ƃ��̏���
		(*iter)->CalculateMoveVec();
	}
}

void BattleScene::EffectProcess()
{
	//�G�t�F�N�g�̃A�b�v�f�[�g
	std::for_each(m_effectList.begin(), m_effectList.end(),
		std::mem_fun(&EffectBase::Update));

	for (UINT i = 0; i < m_effectList.size(); i++)
	{
		//�G�t�F�N�g���I����ĂȂ������珜�O
		if (!m_effectList[i]->GetEffectFinishFlg())continue;

		//�G�t�F�N�g����������
		delete m_effectList[i];
		m_effectList = UNIQUELIBRARY.DeleteList(i, m_effectList);
	}
}
