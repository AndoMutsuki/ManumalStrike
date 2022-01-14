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
		delete *iter;
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
	m_mousePos = m_mouseProcess->Update(m_mousePos);

	//HP�̌v�Z
	m_calculateHP->Update();
	if (!m_calculateHP->GetAliveFlg())
	{
		m_drawProcess->SetHPRaito(m_calculateHP->GetHPRaito());
		m_drawProcess->Update();
		return;
	}

	//�ł��o���ꂽ��t���O�𗧂Ă�
	if (m_firstShotProcess->DoCalculateArrowMat() && !GetAsyncKeyState(MK_LBUTTON))
	{
		m_shotedFlg = true;
	}

	//�ł��o����}�j���}��������
	if (!m_shotedFlg)
	{
		m_manumalAttackCircle->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalData());
	}

	//�ŏ��ɑł��o������
	if (m_manumalList[m_nowMoveManumalNum]->GetManumalData().nowSpeed <= 0)
	{
		m_firstShotProcess->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalDataKinetic(), m_mousePos);
		m_manumalList[m_nowMoveManumalNum]->CalculateMoveVec();
	}

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
	if (m_shotedFlg && m_allManumalStopFlg)
	{
		for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
		{
			(*iter)->GetManumalDataKinetic().frendFlg = false;
		}

		for (auto iter = m_enemyList.begin(); iter != m_enemyList.end(); ++iter)
		{
			if (!(*iter)->GetAliveFlg())continue;

			(*iter)->GetEnemyDataKinetic().nowAttackTurn--;

			if ((*iter)->GetEnemyDataKinetic().nowAttackTurn != 0)continue;

			(*iter)->GetEnemyDataKinetic().nowAttackTurn = (*iter)->GetEnemyData().attackTurn;

			SetEnemyAttack((*iter)->GetEnemyData().attackType, (*iter)->GetEnemyData().pos);
			if (m_enemyAttack != nullptr)
			{
				m_enemyAttack->Update((*iter)->GetEnemyDataKinetic(), m_manumalList);
				m_calculateHP->SetDamage(m_enemyAttack->GetDamage());
			}
			delete m_enemyAttack;
			m_enemyAttack = nullptr;
		}

		m_shotedFlg = false;
		m_manumalAttackCircle->Init();
		m_nowMoveManumalNum++;
		if (m_nowMoveManumalNum >= m_nowMoveManumalNumMax)
		{
			m_nowMoveManumalNum = 0;
		}
		m_manumalAttackCircle->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalData());
		return;
	}

	//�}�j���}���̈ړ�����
	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::MoveProcess));

	//�}�j���}�����m�̓����蔻��
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		if (m_manumalList[m_nowMoveManumalNum] == *iter)continue;

		m_manumalMutualCollision->Update(m_manumalList[m_nowMoveManumalNum]->GetManumalData(), (*iter)->GetManumalDataKinetic());
		if (m_manumalMutualCollision->GetmHitManumalMutualFlg())
		{
			std::for_each(m_manumalList.begin(), m_manumalList.end(),
				std::mem_fun(&ManumalBase::CalculateMoveVec));

			if ((*iter)->GetManumalData().frendFlg)continue;

			(*iter)->GetManumalDataKinetic().frendFlg = true;

			SetFriendshipCombo((*iter)->GetManumalData().frendshipType, (*iter)->GetManumalData().pos);
			if (m_frendshipCombo != nullptr)
			{
				m_frendshipCombo->Update((*iter)->GetManumalDataKinetic(), m_enemyList);
			}
			delete m_frendshipCombo;
			m_frendshipCombo = nullptr;
		}
	}

	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		for (auto iter2 = m_manumalList.begin(); iter2 != m_manumalList.end(); ++iter2)
		{
			if (m_manumalList[m_nowMoveManumalNum] == *iter)continue;
			if (m_manumalList[m_nowMoveManumalNum] == *iter2)continue;
			if (iter == iter2)continue;

			m_manumalMutualCollision->Update((*iter)->GetManumalDataKinetic(), (*iter2)->GetManumalDataKinetic());
			if (m_manumalMutualCollision->GetmHitManumalMutualFlg())
			{
				(*iter)->CalculateMoveVec();
				(*iter2)->CalculateMoveVec();
			}
		}
	}

	//�}�j���}���ƓG�̓����蔻��
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		for (auto iterE = m_enemyList.begin(); iterE != m_enemyList.end(); ++iterE)
		{
			if (!(*iterE)->GetAliveFlg())continue;

			m_manumalEnemyCollison->Update((*iter)->GetManumalDataKinetic(), (*iterE)->GetEnemyData());
			if (m_manumalEnemyCollison->GetHitManumalEnemyFlg())
			{
				(*iter)->CalculateMoveVec();

				if (m_manumalList[m_nowMoveManumalNum] == *iter)
				{
					(*iterE)->SetDamage((int)(*iter)->GetManumalData().attack);
				}
			}
		}
	}

	//���˔Œ��˕Ԃ鏈��
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		m_hitManumalReflectorProcess->Update((*iter)->GetManumalDataKinetic(), m_reflectorProcess);
		if (m_hitManumalReflectorProcess->GetHitReflectorFlg())
		{
			(*iter)->CalculateMoveVec();
		}
	}

	//�ǂŒ��˕Ԃ鏈��
	for (auto iter = m_manumalList.begin(); iter != m_manumalList.end(); ++iter)
	{
		m_hitManumalwallProcess->Update((*iter)->GetManumalDataKinetic());
		if (m_hitManumalwallProcess->GetHitWallFlg())
		{
			(*iter)->CalculateMoveVec();
		}
	}

	//�}�j���}���̍s��̌v�Z
	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::CalculateMatrix));

	//HP�̃Z�b�g
	m_drawProcess->SetHPRaito(m_calculateHP->GetHPRaito());

	//UI�֌W�̏���
	m_drawProcess->Update();

	//�G�t�F�N�g�֌W
	std::for_each(m_effectList.begin(), m_effectList.end(),
		std::mem_fun(&EffectBase::Update));

	for (UINT i = 0; i < m_effectList.size(); i++)
	{
		if (m_effectList[i]->GetEffectFinishFlg())
		{
			delete m_effectList[i];
			m_effectList = UNIQUELIBRARY.DeleteList(i, m_effectList);
		}
	}
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
