#include "item_manager.h"
#include <stdio.h>
#include <string.h>

// 아이템 데이터 로드
ItemData LoadItemData(int itemId) {
    ItemData item = {0};
    
    char path[64];
    snprintf(path, sizeof(path), "data/items/item_%d.txt", itemId);
    
    FILE* fp = fopen(path, "r");
    if (!fp) {
        printf("아이템 로드 실패: %s\n", path);
        return item;
    }
    
    fgets(item.name, sizeof(item.name), fp);
    item.name[strcspn(item.name, "\n")] = 0;
    
    fgets(item.description, sizeof(item.description), fp);
    item.description[strcspn(item.description, "\n")] = 0;
    
    fscanf(fp, "%d %d", &item.price, &item.heal);
    item.id = itemId;
    
    fclose(fp);
    return item;
}

// 아이템을 인벤토리에 추가
int AddItemToInventory(CharacterData* player, int itemId) {
    if (player->inventoryCount >= 20) {
        printf("인벤토리가 가득 찼습니다!\n");
        return 0;
    }
    
    player->inventory[player->inventoryCount] = itemId;
    player->inventoryCount++;
    return 1;
}

// 아이템 사용
int UseItem(CharacterData* player, int inventoryIndex) {
    if (inventoryIndex < 0 || inventoryIndex >= player->inventoryCount) {
        return 0;
    }
    
    int itemId = player->inventory[inventoryIndex];
    ItemData item = LoadItemData(itemId);
    
    if (item.id == 0) {
        return 0;
    }
    
    // 회복 아이템 사용
    if (item.heal > 0) {
        player->hp += item.heal;
        if (player->hp > player->maxHp) {
            player->hp = player->maxHp;
        }
        
        printf("\n%s을(를) 사용했습니다!\n", item.name);
        printf("HP +%d 회복! (현재 HP: %d/%d)\n", 
               item.heal, player->hp, player->maxHp);
    }
    
    // 아이템 제거 (인벤토리에서 삭제)
    for (int i = inventoryIndex; i < player->inventoryCount - 1; i++) {
        player->inventory[i] = player->inventory[i + 1];
    }
    player->inventoryCount--;
    
    return 1;
}

// 아이템 판매
int SellItem(CharacterData* player, int inventoryIndex) {
    if (inventoryIndex < 0 || inventoryIndex >= player->inventoryCount) {
        return 0;
    }
    
    int itemId = player->inventory[inventoryIndex];
    ItemData item = LoadItemData(itemId);
    
    if (item.id == 0) {
        return 0;
    }
    
    // 판매 가격 (구매가의 50%)
    int sellPrice = item.price / 2;
    player->gold += sellPrice;
    
    // 아이템 제거
    for (int i = inventoryIndex; i < player->inventoryCount - 1; i++) {
        player->inventory[i] = player->inventory[i + 1];
    }
    player->inventoryCount--;
    
    printf("\n%s을(를) %d Gold에 판매했습니다!\n", item.name, sellPrice);
    
    return sellPrice;
}