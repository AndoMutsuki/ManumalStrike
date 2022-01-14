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
#include"BattleProcess/CalculateHP/CalculateHP.h"
#include"BattleProcess/DrawProcess/BattleStatusBarProcess/BattleStatusBarProcess.h"

//�o�g���̏���
#include"BattleProcess/FirstShotProcess/FirstShotProcess.h"
#include"BattleProcess/CalculateSpeed/CalculateSpeed.h"
#include"BattleProcess/ReflectorProcess/ReflectorProcess.h"
#include"BattleProcess/ManumalMutualCollision/ManumalMutualCollision.h"
#include"BattleProcess/ManumalEnemyCollison/ManumalEnemyCollison.h"
#include"BattleProcess/HitManumalReflectorProcess/HitManumalReflectorProcess.h"
#include"BattleProcess/HitManumalwallProcess/HitManumalwallProcess.h"
#include"BattleProcess/DrawProcess/DrawProcess.h"
#include"BattleProcess/ManumalAttackCircle/ManumalAttackCircle.h"

//�}�j���}���֌W
#include"Manumal/ManumalBase.h"
#include"Manumal/Morumon.h"
#include"Manumal/Raibit.h"
#include"Manumal/Pebrat.h"

//�G�֌W
#include"Enemy/EnemyBase.h"
#include"Enemy/FireCube.h"
#include"Enemy/Hinokokko.h"

//�F��R���{
#include"FriendshipCombo/FriendshipComboBase.h"
#include"FriendshipCombo/FriendExplosion.h"

//�G�̍U��
#include"EnemyAttack/EnemyAttackBase.h"
#include"EnemyAttack/Explosion.h"
#include"EnemyAttack/BigExplosion.h"

//�G�t�F�N�g�֌W
#include"Effect/EffectBase.h"
#include"Effect/ReflectWallEffect.h"
#include"Effect/ExplosionEffect.h"

//�V�[���֌W
#include "SceneBase/SceneBase.h"
#include "SceneBase/BattleScene/BattleScene.h"
#include "Scene.h"