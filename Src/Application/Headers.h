#pragma once

#include "main.h"

//全クラス共有
#include"UniqueLibrary/UniqueLibrary.h"
#include"TextureManager/TextureManager.h"
#include"ManumalStrikeNamespace.h"
#include<Effekseer.h>
#include<EffekseerRendererDX11.h>
#include"EffectManager/EffectManager.h"

using namespace ManumalStrikeNamespace;

//マウスの制御
#include"Mouse/MouseProcess.h"

//バトルの処理
#include"BattleProcess/FirstShotProcess/FirstShotProcess.h"
#include"BattleProcess/ReflectorProcess/ReflectorProcess.h"
#include"BattleProcess/ManumalMutualCollision/ManumalMutualCollision.h"
#include"BattleProcess/ManumalEnemyCollison/ManumalEnemyCollison.h"
#include"BattleProcess/HitManumalReflectorProcess/HitManumalReflectorProcess.h"
#include"BattleProcess/HitManumalwallProcess/HitManumalwallProcess.h"

//敵関係
#include"Manumal/ManumalBase.h"
#include"Manumal/Morumon.h"

//シーン関係
#include "SceneBase/SceneBase.h"
#include "SceneBase/BattleScene/BattleScene.h"
#include "Scene.h"