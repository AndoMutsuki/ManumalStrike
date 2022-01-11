#pragma once

#define DEBUG

#include "main.h"

//全クラス共有
#include <numeric>
#include"UniqueLibrary/UniqueLibrary.h"
#include"TextureManager/TextureManager.h"
#include"ManumalStrikeNamespace.h"
#include<Effekseer.h>
#include<EffekseerRendererDX11.h>
#include"ImGuiManager/ImGuiManager.h"
#include"EffectManager/EffectManager.h"

using namespace ManumalStrikeNamespace;

//マウスの制御
#include"Mouse/MouseProcess.h"

//ステージ関係
#include"BattleProcess/DrawProcess/StageDataBase/StageDataBase.h"
#include"BattleProcess/DrawProcess/StageDataBase/Stage1/Stage1.h"

//プレイヤーのステータス関係
#include"BattleProcess/DrawProcess/BattleStatusBarProcess/BattleStatusBarProcess.h"

//バトルの処理
#include"BattleProcess/FirstShotProcess/FirstShotProcess.h"
#include"BattleProcess/ReflectorProcess/ReflectorProcess.h"
#include"BattleProcess/ManumalMutualCollision/ManumalMutualCollision.h"
#include"BattleProcess/ManumalEnemyCollison/ManumalEnemyCollison.h"
#include"BattleProcess/HitManumalReflectorProcess/HitManumalReflectorProcess.h"
#include"BattleProcess/HitManumalwallProcess/HitManumalwallProcess.h"
#include"BattleProcess/CalculateHP/CalculateHP.h"
#include"BattleProcess/DrawProcess/DrawProcess.h"

//敵関係
#include"Manumal/ManumalBase.h"
#include"Manumal/Morumon.h"

//シーン関係
#include "SceneBase/SceneBase.h"
#include "SceneBase/BattleScene/BattleScene.h"
#include "Scene.h"