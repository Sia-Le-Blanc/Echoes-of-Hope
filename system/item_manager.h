#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include "../core/game.h"

// 아이템 데이터 로드
ItemData LoadItemData(int itemId);

// 인벤토리 관리
void AddItemToInventory(PlayerData* player, int itemId);
void RemoveItemFromInventory(PlayerData* player, int itemId);
void ClearInventory(PlayerData* player);

// 아이템 사용
void UseItem(PlayerData* player, int inventoryIndex);

// 인벤토리 조회
int GetItemCount(PlayerData* player, int itemId);
int HasItem(PlayerData* player, int itemId);

#endif