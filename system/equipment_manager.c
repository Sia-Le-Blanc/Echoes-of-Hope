#include "equipment_manager.h"
#include "fileio.h"
#include <stdio.h>

// 장비 착용
int EquipItem(CharacterData* player, int equipId) {
    EquipmentData equip;
    
    if (!LoadEquipment(&equip, equipId)) {
        printf("장비를 불러올 수 없습니다.\n");
        return 0;
    }
    
    // 슬롯에 따라 장착
    switch(equip.slot) {
        case EQUIP_WEAPON:
            if (player->weaponId > 0) {
                printf("이미 무기를 착용 중입니다. 먼저 해제하세요.\n");
                return 0;
            }
            player->weaponId = equipId;
            break;
        case EQUIP_HELMET:
            if (player->helmetId > 0) {
                printf("이미 투구를 착용 중입니다. 먼저 해제하세요.\n");
                return 0;
            }
            player->helmetId = equipId;
            break;
        case EQUIP_ARMOR:
            if (player->armorId > 0) {
                printf("이미 상의를 착용 중입니다. 먼저 해제하세요.\n");
                return 0;
            }
            player->armorId = equipId;
            break;
        case EQUIP_PANTS:
            if (player->pantsId > 0) {
                printf("이미 하의를 착용 중입니다. 먼저 해제하세요.\n");
                return 0;
            }
            player->pantsId = equipId;
            break;
        case EQUIP_GLOVES:
            if (player->glovesId > 0) {
                printf("이미 장갑을 착용 중입니다. 먼저 해제하세요.\n");
                return 0;
            }
            player->glovesId = equipId;
            break;
        case EQUIP_BOOTS:
            if (player->bootsId > 0) {
                printf("이미 신발을 착용 중입니다. 먼저 해제하세요.\n");
                return 0;
            }
            player->bootsId = equipId;
            break;
        default:
            return 0;
    }
    
    // 스탯 재계산
    RecalculateStats(player);
    
    printf("\n%s을(를) 착용했습니다!\n", equip.name);
    printf("공격력 +%d, 방어력 +%d\n", equip.attack, equip.defense);
    
    return 1;
}

// 장비 해제
int UnequipItem(CharacterData* player, EquipmentSlot slot) {
    int equipId = 0;
    
    switch(slot) {
        case EQUIP_WEAPON:
            equipId = player->weaponId;
            player->weaponId = 0;
            break;
        case EQUIP_HELMET:
            equipId = player->helmetId;
            player->helmetId = 0;
            break;
        case EQUIP_ARMOR:
            equipId = player->armorId;
            player->armorId = 0;
            break;
        case EQUIP_PANTS:
            equipId = player->pantsId;
            player->pantsId = 0;
            break;
        case EQUIP_GLOVES:
            equipId = player->glovesId;
            player->glovesId = 0;
            break;
        case EQUIP_BOOTS:
            equipId = player->bootsId;
            player->bootsId = 0;
            break;
        default:
            return 0;
    }
    
    if (equipId == 0) {
        printf("해당 슬롯에 장비가 없습니다.\n");
        return 0;
    }
    
    // 스탯 재계산
    RecalculateStats(player);
    
    printf("장비를 해제했습니다.\n");
    
    return 1;
}

// 장비 효과 적용 (공격력/방어력 재계산)
void RecalculateStats(CharacterData* player) {
    int totalAttack = 0;
    int totalDefense = 0;
    
    EquipmentData equip;
    
    // 각 장비의 스탯 합산
    if (player->weaponId > 0 && LoadEquipment(&equip, player->weaponId)) {
        totalAttack += equip.attack;
        totalDefense += equip.defense;
    }
    if (player->helmetId > 0 && LoadEquipment(&equip, player->helmetId)) {
        totalAttack += equip.attack;
        totalDefense += equip.defense;
    }
    if (player->armorId > 0 && LoadEquipment(&equip, player->armorId)) {
        totalAttack += equip.attack;
        totalDefense += equip.defense;
    }
    if (player->pantsId > 0 && LoadEquipment(&equip, player->pantsId)) {
        totalAttack += equip.attack;
        totalDefense += equip.defense;
    }
    if (player->glovesId > 0 && LoadEquipment(&equip, player->glovesId)) {
        totalAttack += equip.attack;
        totalDefense += equip.defense;
    }
    if (player->bootsId > 0 && LoadEquipment(&equip, player->bootsId)) {
        totalAttack += equip.attack;
        totalDefense += equip.defense;
    }
    
    player->attack = totalAttack;
    player->defense = totalDefense;
}

// 장비 내구도 감소 (미구현 - 나중에 추가)
void DecreaseDurability(CharacterData* player, int amount) {
    // TODO: 내구도 시스템 구현
}