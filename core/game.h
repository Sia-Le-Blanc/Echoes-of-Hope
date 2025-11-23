#ifndef CORE_GAME_H
#define CORE_GAME_H

#include "../model/character.h"

typedef enum {
    SCENE_TITLE = 0,
    SCENE_CREATE,
    SCENE_MENU,
    SCENE_TOWN,
    SCENE_BATTLE
} SceneType;

extern SceneType g_CurrentScene;
extern CharacterData g_CurrentPlayer;

#endif