#ifndef SYSTEM_FILEIO_H
#define SYSTEM_FILEIO_H

#include "../model/character.h"
#include "../model/monster.h"
#include "../model/equipment.h"
#include "../model/game_progress.h"
#include "../core/game.h"
#include <stddef.h>

// 경로 생성 함수
void GetPlayerSavePath(char* buffer, size_t bufSize, const char* playerName);
void GetSceneSavePath(char* buffer, size_t bufSize, const char* playerName);
void GetProgressSavePath(char* buffer, size_t bufSize, const char* playerName);

// 플레이어 폴더 생성
int CreatePlayerSaveFolder(const char* playerName);

// 저장된 플레이어 목록
int GetSavedPlayerList(char names[][32], int maxCount);

// 캐릭터 저장/로드
int SavePlayer(const CharacterData* player, const char* playerName);
int LoadPlayer(CharacterData* outPlayer, const char* playerName);

// 씬 저장/로드
int SaveScene(SceneType scene, const char* playerName);
int LoadScene(SceneType* outScene, const char* playerName);

// GameProgress 저장/로드
int SaveProgress(const GameProgress* progress, const char* playerName);
int LoadProgress(GameProgress* outProgress, const char* playerName);

// 몬스터/장비 로드
int LoadMonster(MonsterData* outMonster, int monsterId);
int LoadEquipment(EquipmentData* outEquip, int equipId);

#endif