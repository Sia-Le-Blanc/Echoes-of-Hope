#include "combat_system.h"
#include "../system/stat_calculator.h"
#include <stdlib.h>
#include <time.h>

// 플레이어 → 몬스터 공격
AttackResult CalculateAttack(CharacterData* attacker, MonsterData* target) {
    AttackResult result = {0, 0, 0, 0};
    
    // 기본 데미지 계산
    int totalAttack = GetTotalAttack(attacker);
    int damage = totalAttack - target->defense;
    
    if (damage < 1) damage = 1;
    
    // 치명타 판정 (LUK 기반)
    float critChance = GetCritChance(attacker);
    float critRoll = (float)(rand() % 100);
    
    if (critRoll < critChance) {
        result.isCritical = 1;
        damage = (int)(damage * 1.5f);
    }
    
    result.actualDamage = damage;
    
    // 몬스터 HP 감소
    target->hp -= damage;
    if (target->hp < 0) target->hp = 0;
    
    return result;
}

// 몬스터 → 플레이어 공격
AttackResult CalculateMonsterAttack(MonsterData* attacker, CharacterData* target) {
    AttackResult result = {0, 0, 0, 0};
    
    // 회피 판정 (DEX 기반)
    float dodgeChance = GetDodgeChance(target);
    float dodgeRoll = (float)(rand() % 100);
    
    if (dodgeRoll < dodgeChance) {
        result.isDodged = 1;
        result.actualDamage = 0;
        return result;
    }
    
    // 기본 데미지 계산
    int totalDefense = GetTotalDefense(target);
    int damage = attacker->attack - totalDefense;
    
    if (damage < 1) damage = 1;
    
    result.actualDamage = damage;
    
    // 플레이어 HP 감소
    target->hp -= damage;
    if (target->hp < 0) target->hp = 0;
    
    return result;
}