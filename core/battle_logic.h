#ifndef BATTLE_LOGIC_H
#define BATTLE_LOGIC_H

#include "../model/character.h"
#include "../model/monster.h"

// 데미지 계산 
int CalculateDamage(int attack, int defense);

// 플레이어 공격 
int PlayerAttack(CharacterData* player, MonsterData* monster);

// 몬스터 공격
int MonsterAttack(MonsterData* monster, CharacterData* player);

// 경험치 획득 및 레벨업 체크
void GainExp(CharacterData* player, int exp);

// 필요 경험치 계산
int GetRequiredExp(int level);

#endif