#ifndef SCENE_DUNGEON_H
#define SCENE_DUNGEON_H

#include "../model/monster.h"

// 던전 입장 및 진행
void ShowDungeon();

// 범용 전투 함수 (반환: 1=승리, 0=패배/도망)
int BattleWithMonster(MonsterData* monster, int isBoss);

// 챕터별 랜덤 몬스터 로드
MonsterData LoadRandomMonster(int chapter);

// 챕터별 보스 로드
MonsterData LoadBoss(int chapter);

#endif