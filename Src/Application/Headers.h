#pragma once

#define DEBUG

#include "main.h"

//�S�N���X���L
#include <numeric>
#include"UniqueLibrary/UniqueLibrary.h"
#include"TextureManager/TextureManager.h"
#include"ManumalStrikeNamespace.h"
#include<Effekseer.h>
#include<EffekseerRendererDX11.h>
#include"ImGuiManager/ImGuiManager.h"
#include"EffectManager/EffectManager.h"

using namespace ManumalStrikeNamespace;

//�}�E�X�̐���
#include"Mouse/MouseProcess.h"

//�X�e�[�W�֌W
#include"BattleProcess/DrawProcess/StageDataBase/StageDataBase.h"
#include"BattleProcess/DrawProcess/StageDataBase/Stage1/Stage1.h"

//�v���C���[�̃X�e�[�^�X�֌W
#include"BattleProcess/DrawProcess/BattleStatusBarProcess/BattleStatusBarProcess.h"

//�o�g���̏���
#include"BattleProcess/FirstShotProcess/FirstShotProcess.h"
#include"BattleProcess/ReflectorProcess/ReflectorProcess.h"
#include"BattleProcess/ManumalMutualCollision/ManumalMutualCollision.h"
#include"BattleProcess/ManumalEnemyCollison/ManumalEnemyCollison.h"
#include"BattleProcess/HitManumalReflectorProcess/HitManumalReflectorProcess.h"
#include"BattleProcess/HitManumalwallProcess/HitManumalwallProcess.h"
#include"BattleProcess/CalculateHP/CalculateHP.h"
#include"BattleProcess/DrawProcess/DrawProcess.h"

//�G�֌W
#include"Manumal/ManumalBase.h"
#include"Manumal/Morumon.h"

//�V�[���֌W
#include "SceneBase/SceneBase.h"
#include "SceneBase/BattleScene/BattleScene.h"
#include "Scene.h"