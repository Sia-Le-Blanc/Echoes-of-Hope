#ifndef EQUIPMENT_MANAGER_H
#define EQUIPMENT_MANAGER_H

#include "../model/character.h"
#include "../model/equipment.h"

// 장비 착용
// 반환: 성공 1, 실패 0
int EquipItem(CharacterData* player, int equipId);

// 장비 해제
// 반환: 성공 1, 실패 0
int UnequipItem(CharacterData* player, EquipmentSlot slot);

// 장비 효과 적용 (공격력/방어력 재계산)
void RecalculateStats(CharacterData* player);

// 장비 내구도 감소 (전투 시)
void DecreaseDurability(CharacterData* player, int amount);

#endif