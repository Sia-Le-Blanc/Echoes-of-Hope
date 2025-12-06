#include "stat_calculator.h"

// 총 공격력 계산 (기본 + 장비 + STR * 0.5)
int GetTotalAttack(CharacterData* player) {
    int baseAttack = player->attack;
    int strBonus = (int)(player->str * 0.5f);
    return baseAttack + strBonus;
}

// 총 방어력 계산 (기본 + 장비 + DEX * 0.2)
int GetTotalDefense(CharacterData* player) {
    int baseDefense = player->defense;
    int dexBonus = (int)(player->dex * 0.2f);
    return baseDefense + dexBonus;
}

// 치명타 확률 계산 (LUK * 0.1%)
float GetCritChance(CharacterData* player) {
    return (float)player->luk * 0.1f;
}

// 회피 확률 계산 (DEX * 0.1%)
float GetDodgeChance(CharacterData* player) {
    return (float)player->dex * 0.1f;
}

// 최대 HP 보너스 계산 (STR * 2)
int GetHpBonus(CharacterData* player) {
    return player->str * 2;
}

// 최대 MP 보너스 계산 (INT * 2)
int GetMpBonus(CharacterData* player) {
    return player->intel * 2;
}