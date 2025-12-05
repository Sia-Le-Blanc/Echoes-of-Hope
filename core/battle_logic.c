#include "battle_logic.h"
#include <stdio.h>

int CalculateDamage(int attack, int defense) {
    int damage = attack - defense;
    return damage > 0 ? damage : 1; // 최소 1 데미지
}

int PlayerAttack(CharacterData* player, MonsterData* monster) {
    int damage = CalculateDamage(player->attack, monster->defense);
    monster->hp -= damage;
    if (monster->hp < 0) monster->hp = 0;
    return damage;
}

int MonsterAttack(MonsterData* monster, CharacterData* player) {
    int damage = CalculateDamage(monster->attack, player->defense);
    player->hp -= damage;
    if (player->hp < 0) player->hp = 0;
    return damage;
}

int GetRequiredExp(int level) {
    return level * 100; // 레벨 * 100
}

void GainExp(CharacterData* player, int exp) {
    player->exp += exp;
    
    while (player->exp >= GetRequiredExp(player->level)) {
        player->exp -= GetRequiredExp(player->level);
        player->level++;
        
        // 레벨업 시 스탯 증가
        switch(player->job) {
            case JOB_WARRIOR:
                player->maxHp += 10;
                player->attack += 3;
                player->defense += 2;
                break;
            case JOB_MAGE:
                player->maxHp += 10;
                player->attack += 3;
                player->defense += 1;
                break;
            case JOB_ARCHER:
                player->maxHp += 10;
                player->attack += 2;
                player->defense += 2;
                break;
        }
        
        player->hp = player->maxHp;
        player->mp = player->maxMp;
        
        printf("\n★ 레벨업! LV.%d → LV.%d\n", player->level - 1, player->level);
        printf("HP +10, 공격력/방어력 증가!\n");
    }
}