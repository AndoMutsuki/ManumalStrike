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
	m_manumalList.clear();
	m_manumalList.push_back(new Raibit);
	m_manumalList.push_back(new Morumon);
	m_manumalList.push_back(new Pebrat);
	m_manumalList[0]->SetPos({ -200,-100 });
	m_manumalList[1]->SetPos({ 0,-120 });
	m_manumalList[2]->SetPos({ 200,-100 });
	m_enemyList.clear();
	m_enemyList.push_back(new FireCube);
	m_enemyList.push_back(new FireCube);
	m_enemyList.push_back(new Hinokokko);
	m_enemyList[0]->SetEnemyPos({ -400,250 });
	m_enemyList[1]->SetEnemyPos({ 350,100 });
	m_enemyList[2]->SetEnemyPos({ 0,120 });

	//�ő�HP���v�Z
	int HPMax = std::accumulate(m_manumalList.begin(), m_manumalList.end(), 0,
		[](int HP, ManumalBase* manumalBase) { return HP + manumalBase->GetManumalData().HP; });
	m_calculateHP->SetHPMax(HPMax);

	//�}�j���}���֌W
	m_nowMoveManumalNum = 0;
	m_shotedFlg = false;

	//�G�t�F�N�V�A
	m_effect = *(EFFEKSEER.GetEffect(uR"(Data/Effect/reflectWall/reflectWall.efk)"));
	m_handle = 0;
	m_effectFlg = false;

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
	m_manumalList.clear();
}

void BattleScene::Update()
{
	m_mousePos = m_mouseProcess->Update(m_mousePos);

	//�ł��o���ꂽ��t���O�𗧂Ă�
	if (m_firstShotProcess->DoCalculateArrowMat() && !GetAsyncKeyState(MK_LBUTTON))
	{
		m_shotedFlg = true;
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
		m_shotedFlg = false;
		m_nowMoveManumalNum++;
		if (m_nowMoveManumalNum >= m_nowMoveManumalNumMax)
		{
			m_nowMoveManumalNum = 0;
		}
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
			m_manumalEnemyCollison->Update((*iter)->GetManumalDataKinetic(), (*iterE)->GetEnemyData());
			if (m_manumalEnemyCollison->GetHitManumalEnemyFlg())
			{
				(*iter)->CalculateMoveVec();
			}
		}
	}

	//HP�̌v�Z
	m_calculateHP->Update();
	if (!m_calculateHP->GetAliveFlg())
	{
		return;
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
}

void BattleScene::Draw2D()
{
	SHADER.m_spriteShader.Begin();

	m_drawProcess->Draw();

	std::for_each(m_manumalList.begin(), m_manumalList.end(),
		std::mem_fun(&ManumalBase::Draw));

	std::for_each(m_enemyList.begin(), m_enemyList.end(),
		std::mem_fun(&EnemyBase::Draw));

	m_reflectorProcess->Draw();

	if (m_firstShotProcess->GetArrowDrawFlg())
	{
		m_firstShotProcess->DrawArrow();
	}

	EffectDraw();

	SHADER.m_spriteShader.End();
}

void BattleScene::EffectDraw()
{
	if (!m_effectFlg)
	{
		// �G�t�F�N�g�̍Đ�
		m_handle = EFFEKSEER.GetManager()->Play(m_effect, 0, 0, 0);
		m_effectFlg = true;
	}

	// �G�t�F�N�g�̈ړ�
	//EFFEKSEER.GetManager()->AddLocation(m_handle, ::Effekseer::Vector3D(0.2f, 0.0f, 0.0f));

	//EFFEKSEER.GetManager()->SetRotation(m_handle, 0,0,0);
	//EFFEKSEER.GetManager()->SetRotation(m_handle, {0,1,0}, 270);

	// �}�l�[�W���[�̍X�V
	EFFEKSEER.GetManager()->Update();

	// �G�t�F�N�g�̕`��J�n�������s���B
	EFFEKSEER.GetRenderer()->BeginRendering();

	// �G�t�F�N�g�̕`����s���B
	EFFEKSEER.GetManager()->Draw();

	// �G�t�F�N�g�̕`��I���������s���B
	EFFEKSEER.GetRenderer()->EndRendering();
}
