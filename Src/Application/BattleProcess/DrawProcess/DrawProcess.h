#pragma once

//�X�e�[�W�̕`��Ɋւ��鏈��
class DrawProcess
{
public:

	DrawProcess();

	~DrawProcess();

	void Update();

	void Draw();

	void SetHPRaito(const float _HPRaito);

private:

	StageDataBase* m_stageDataBase;

	BattleStatusBarProcess* m_battleStatusBarProcess;

	float m_HPRaito;

};