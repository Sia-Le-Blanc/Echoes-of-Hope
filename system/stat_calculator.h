#ifndef STAT_CALCULATOR_H
#define STAT_CALCULATOR_H

#include "../model/character.h"

// 총 공격력 계산 (기본 + 장비 + STR * 0.5)
int GetTotalAttack(CharacterData* player);

// 총 방어력 계산 (기본 + 장비 + DEX * 0.2)
int GetTotalDefense(CharacterData* player);

// 치명타 확률 계산 (LUK * 0.1%)
float GetCritChance(CharacterData* player);

// 회피 확률 계산 (DEX * 0.1%)
float GetDodgeChance(CharacterData* player);

// 최대 HP 보너스 계산 (STR * 2)
int GetHpBonus(CharacterData* player);

// 최대 MP 보너스 계산 (INT * 2)
int GetMpBonus(CharacterData* player);

#endif 