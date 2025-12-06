#include "game.h"

// 전역 변수 정의
SceneType g_CurrentScene = SCENE_TITLE;
CharacterData g_CurrentPlayer = {0};
GameProgress g_GameProgress = {1, 0, 0, {0}, DIFFICULTY_NORMAL, 0, 0};