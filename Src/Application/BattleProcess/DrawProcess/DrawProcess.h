#pragma once

//�X�e�[�W�̕`��Ɋւ��鏈��
class DrawProcess
{
public:

	DrawProcess();

	~DrawProcess();

	void Update();

	void Draw();

private:

	StageDataBase* m_stageDataBase;
	BattleStatusBarProcess* m_battleStatusBarProcess;

};