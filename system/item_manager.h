#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include "../model/character.h"
#include "../model/item.h"

// 아이템을 인벤토리에 추가
// 반환: 성공 1, 실패 0 (인벤토리 가득 참)
int AddItemToInventory(CharacterData* player, int itemId);

// 아이템 사용 (포션 등)
// inventoryIndex: 인벤토리 슬롯 번호 (0~19)
// 반환: 성공 1, 실패 0
int UseItem(CharacterData* player, int inventoryIndex);

// 아이템 판매
// 반환: 판매 가격 (실패 시 0)
int SellItem(CharacterData* player, int inventoryIndex);

// 아이템 데이터 로드
ItemData LoadItemData(int itemId);

#endif