#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include "../model/character.h"
#include "../model/monster.h"

// 공격 결과 구조체
typedef struct {
    int isCritical;         // 치명타 여부
    int isDodged;           // 회피 여부
    int actualDamage;       // 실제 데미지
    int statusEffect;       // 부여된 상태이상 ID (0=없음)
} AttackResult;

// 고급 전투 계산 (치명타/회피 포함)
AttackResult CalculateAttack(CharacterData* attacker, MonsterData* target);

// 몬스터 → 플레이어 공격
AttackResult CalculateMonsterAttack(MonsterData* attacker, CharacterData* target);

#endif