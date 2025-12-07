#include "item_manager.h"
#include "../core/game.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

ItemData LoadItemData(int itemId) {
    ItemData item = {0};
    
    char path[128];
    snprintf(path, sizeof(path), "data/items/item_%d.txt", itemId);
    
    FILE* fp = fopen(path, "r");
    if (!fp) {
        snprintf(item.name, sizeof(item.name), "알 수 없는 아이템");
        snprintf(item.description, sizeof(item.description), "아이템 데이터를 찾을 수 없습니다.");
        item.price = 0;
        item.healAmount = 0;
        return item;
    }
    
    // 아이템 이름
    fgets(item.name, sizeof(item.name), fp);
    item.name[strcspn(item.name, "\n")] = 0;
    
    // 아이템 설명
    fgets(item.description, sizeof(item.description), fp);
    item.description[strcspn(item.description, "\n")] = 0;
    
    // 가격
    fscanf(fp, "%d", &item.price);
    
    // 회복량
    fscanf(fp, "%d", &item.healAmount);
    
    fclose(fp);
    return item;
}

void AddItemToInventory(PlayerData* player, int itemId) {
    if (player->inventoryCount >= 20) {
        printf("인벤토리가 가득 찼습니다!\n");
        return;
    }
    
    player->inventory[player->inventoryCount] = itemId;
    player->inventoryCount++;
}

void UseItem(PlayerData* player, int inventoryIndex) {
    if (inventoryIndex < 0 || inventoryIndex >= player->inventoryCount) {
        printf("잘못된 아이템입니다.\n");
        return;
    }
    
    int itemId = player->inventory[inventoryIndex];
    ItemData item = LoadItemData(itemId);
    
    // 회복 처리
    if (item.healAmount > 0) {
        int healedAmount = item.healAmount;
        
        // 최대 HP를 넘지 않도록
        if (player->hp + healedAmount > player->maxHp) {
            healedAmount = player->maxHp - player->hp;
        }
        
        player->hp += healedAmount;
        
        printf("\n'%s'을(를) 사용했습니다!\n", item.name);
        printf("HP가 %d 회복되었습니다! (현재 HP: %d/%d)\n", 
               healedAmount, player->hp, player->maxHp);
    } else {
        printf("\n'%s'은(는) 사용할 수 없는 아이템입니다.\n", item.name);
        return;
    }
    
    // 인벤토리에서 제거
    for (int i = inventoryIndex; i < player->inventoryCount - 1; i++) {
        player->inventory[i] = player->inventory[i + 1];
    }
    player->inventoryCount--;
}

void ShowInventory(PlayerData* player) {
    ClearScreen();
    printf("=================================================\n");
    printf("                [ 인벤토리 ]\n");
    printf("=================================================\n");
    
    if (player->inventoryCount == 0) {
        printf(" (비어있음)\n");
    } else {
        for (int i = 0; i < player->inventoryCount; i++) {
            ItemData item = LoadItemData(player->inventory[i]);
            printf(" [%d] %s\n", i + 1, item.name);
            printf("     %s\n", item.description);
            if (item.healAmount > 0) {
                printf("     회복량: %d\n", item.healAmount);
            }
            printf("\n");
        }
    }
    
    printf("=================================================\n");
    printf(" 사용 중인 슬롯: %d/20\n", player->inventoryCount);
    printf("=================================================\n");
}

int GetItemCount(PlayerData* player, int itemId) {
    int count = 0;
    for (int i = 0; i < player->inventoryCount; i++) {
        if (player->inventory[i] == itemId) {
            count++;
        }
    }
    return count;
}

void RemoveItemFromInventory(PlayerData* player, int itemId) {
    for (int i = 0; i < player->inventoryCount; i++) {
        if (player->inventory[i] == itemId) {
            // 아이템 제거
            for (int j = i; j < player->inventoryCount - 1; j++) {
                player->inventory[j] = player->inventory[j + 1];
            }
            player->inventoryCount--;
            return;
        }
    }
}

void ClearInventory(PlayerData* player) {
    player->inventoryCount = 0;
}

int HasItem(PlayerData* player, int itemId) {
    for (int i = 0; i < player->inventoryCount; i++) {
        if (player->inventory[i] == itemId) {
            return 1;
        }
    }
    return 0;
}