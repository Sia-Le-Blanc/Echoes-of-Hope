#ifndef GAME_H
#define GAME_H

#include "../model/character.h"
#include "../model/game_progress.h"
#include "../model/monster.h"
#include "../model/item.h"
#include "../model/equipment.h"

// SceneType 정의
typedef enum {
    SCENE_TITLE = 1,
    SCENE_MENU,
    SCENE_TOWN,
    SCENE_DUNGEON,
    SCENE_BATTLE,
    SCENE_CREATE
} SceneType;

// 전역 변수 선언
extern SceneType g_CurrentScene;
extern CharacterData g_CurrentPlayer;
extern GameProgress g_GameProgress;

#endif