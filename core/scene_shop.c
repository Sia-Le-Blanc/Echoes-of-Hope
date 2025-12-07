#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../system/utils.h"
#include "../system/item_manager.h"
#include "scene_shop.h"
#include "game.h"

void SellItem(PlayerData* player, int inventoryIndex) {
    if (inventoryIndex < 0 || inventoryIndex >= player->inventoryCount) {
        printf("\n잘못된 아이템입니다.\n");
        Pause();
        return;
    }
    
    int itemId = player->inventory[inventoryIndex];
    ItemData item = LoadItemData(itemId);
    int sellPrice = item.price / 2;
    
    // 판매 처리
    player->gold += sellPrice;
    
    // 인벤토리에서 제거
    for (int i = inventoryIndex; i < player->inventoryCount - 1; i++) {
        player->inventory[i] = player->inventory[i + 1];
    }
    player->inventoryCount--;
    
    printf("\n'%s'을(를) %dG에 판매했습니다!\n", item.name, sellPrice);
}

void ShowShop() {
    char input[32];
    
    // 챕터1 기본 아이템
    int smallPotionPrice = 50;
    int bandagePrice = 30;
    
    while (1) {
        ClearScreen();
        
        printf("=================================================\n");
        printf("                   [ 상점 ]\n");
        printf("=================================================\n");
        printf(" 상인: 어서오세요! 필요한 물건이 있으신가요?\n\n");
        printf(" [ 1 ] 소형 회복 물약 - %d Gold (HP +50)\n", smallPotionPrice);
        printf(" [ 2 ] 붕대 - %d Gold (HP +30)\n", bandagePrice);
        printf(" [ 3 ] 아이템 판매\n");
        printf(" [ 0 ] 나가기\n");
        printf("-------------------------------------------------\n");
        printf(" 현재 Gold: %d\n", g_CurrentPlayer.gold);
        printf(" 인벤토리: %d/20\n", g_CurrentPlayer.inventoryCount);
        printf("=================================================\n");
        printf(" 선택 > ");
        
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strlen(input) == 0) {
            printf("잘못된 입력입니다.\n");
            Pause();
            continue;
        }
        
        if (strcmp(input, "0") == 0) {
            return;
        }
        else if (strcmp(input, "1") == 0) {
            if (g_CurrentPlayer.gold < smallPotionPrice) {
                printf("\nGold가 부족합니다!\n");
                Pause();
                continue;
            }
            
            if (g_CurrentPlayer.inventoryCount >= 20) {
                printf("\n인벤토리가 가득 찼습니다!\n");
                Pause();
                continue;
            }
            
            g_CurrentPlayer.gold -= smallPotionPrice;
            AddItemToInventory(&g_CurrentPlayer, 1);
            printf("\n소형 회복 물약을 구매했습니다!\n");
            Pause();
        }
        else if (strcmp(input, "2") == 0) {
            if (g_CurrentPlayer.gold < bandagePrice) {
                printf("\nGold가 부족합니다!\n");
                Pause();
                continue;
            }
            
            if (g_CurrentPlayer.inventoryCount >= 20) {
                printf("\n인벤토리가 가득 찼습니다!\n");
                Pause();
                continue;
            }
            
            g_CurrentPlayer.gold -= bandagePrice;
            AddItemToInventory(&g_CurrentPlayer, 2);
            printf("\n붕대를 구매했습니다!\n");
            Pause();
        }
        else if (strcmp(input, "3") == 0) {
            if (g_CurrentPlayer.inventoryCount == 0) {
                printf("\n판매할 아이템이 없습니다.\n");
                Pause();
                continue;
            }
            
            ClearScreen();
            printf("=================================================\n");
            printf("              [ 아이템 판매 ]\n");
            printf("=================================================\n");
            for (int i = 0; i < g_CurrentPlayer.inventoryCount; i++) {
                ItemData item = LoadItemData(g_CurrentPlayer.inventory[i]);
                int sellPrice = item.price / 2;
                printf(" [%d] %s - %dG\n", i + 1, item.name, sellPrice);
            }
            printf(" [ 0 ] 취소\n");
            printf("=================================================\n");
            printf(" 판매할 아이템 번호 > ");
            
            char sellInput[32];
            fgets(sellInput, sizeof(sellInput), stdin);
            sellInput[strcspn(sellInput, "\n")] = 0;
            
            int sellChoice = atoi(sellInput);
            if (sellChoice > 0 && sellChoice <= g_CurrentPlayer.inventoryCount) {
                SellItem(&g_CurrentPlayer, sellChoice - 1);
                Pause();
            }
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
    }
}