#include "scene_town.h"
#include "scene_shop.h"
#include "scene_training.h"
#include "scene_rest.h"
#include "scene_dungeon.h"
#include "scene_inventory.h"
#include "game.h"
#include "../system/item_manager.h"
#include "../system/utils.h"
#include "../system/fileio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ShowTown() {
    char input[32];
    
    while (1) {
        ClearScreen();
        
        printf("=================================================\n");
        printf("              [ 마을 - 평온의 숲 ]\n");
        printf("=================================================\n");
        printf(" %s (LV.%d)\n", g_CurrentPlayer.name, g_CurrentPlayer.level);
        printf(" HP: %d/%d | MP: %d/%d\n",
               g_CurrentPlayer.hp, g_CurrentPlayer.maxHp,
               g_CurrentPlayer.mp, g_CurrentPlayer.maxMp);
        printf(" Gold: %d | EXP: %d/%d\n",
               g_CurrentPlayer.gold, g_CurrentPlayer.exp,
               g_CurrentPlayer.level * 100);
        printf("=================================================\n");
        printf(" [ 1 ] 훈련소\n");
        printf(" [ 2 ] 상점\n");
        printf(" [ 3 ] 여관 (휴식)\n");
        printf(" [ 4 ] 인벤토리\n");
        printf(" [ 5 ] 장비 관리\n");
        printf(" [ 6 ] 던전 입장\n");
        printf(" [ 0 ] 저장하고 나가기\n");
        printf("=================================================\n");
        printf(" 선택 > ");
        
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strlen(input) == 0) {
            continue;
        }
        
        if (strcmp(input, "0") == 0) {
            SavePlayer(&g_CurrentPlayer, g_CurrentPlayer.name);
            SaveProgress(&g_GameProgress, g_CurrentPlayer.name);
            SaveScene(SCENE_TOWN, g_CurrentPlayer.name);
            printf("\n저장 완료!\n");
            Pause();
            return;
        }
        else if (strcmp(input, "1") == 0) {
            ShowTraining();
            SavePlayer(&g_CurrentPlayer, g_CurrentPlayer.name);
        }
        else if (strcmp(input, "2") == 0) {
            ShowShop();
            SavePlayer(&g_CurrentPlayer, g_CurrentPlayer.name);
        }
        else if (strcmp(input, "3") == 0) {
            ShowRest();
            SavePlayer(&g_CurrentPlayer, g_CurrentPlayer.name);
        }
        else if (strcmp(input, "4") == 0) {
            ShowInventory();
            SavePlayer(&g_CurrentPlayer, g_CurrentPlayer.name);
        }
        else if (strcmp(input, "5") == 0) {
            ShowEquipment();
            SavePlayer(&g_CurrentPlayer, g_CurrentPlayer.name);
        }
        else if (strcmp(input, "6") == 0) {
            ShowDungeon();
            SavePlayer(&g_CurrentPlayer, g_CurrentPlayer.name);
            SaveProgress(&g_GameProgress, g_CurrentPlayer.name);
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
    }
}

void ShowShop() {
    char input[32];
    
    while (1) {
        ClearScreen();
        printf("=================================================\n");
        printf("                [ 상점 ]\n");
        printf("=================================================\n");
        printf(" 소지금: %dG\n", g_CurrentPlayer.gold);
        printf("=================================================\n");
        printf(" [ 1 ] 구매하기\n");
        printf(" [ 2 ] 판매하기\n");
        printf(" [ 0 ] 나가기\n");
        printf("=================================================\n");
        printf(" 선택 > ");
        
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "1") == 0) {
            ShowBuyMenu();
        }
        else if (strcmp(input, "2") == 0) {
            ShowSellMenu();
        }
        else if (strcmp(input, "0") == 0) {
            break;
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
    }
}

void ShowBuyMenu() {
    char input[32];
    
    while (1) {
        ClearScreen();
        printf("=================================================\n");
        printf("              [ 상점 - 구매 ]\n");
        printf("=================================================\n");
        printf(" 소지금: %dG\n", g_CurrentPlayer.gold);
        printf("=================================================\n");
        
        // 챕터별 아이템 표시
        int chapter = g_CurrentPlayer.currentChapter;
        
        if (chapter >= 1) {
            printf(" [ 1 ] 소형 회복 물약 - 10G (HP +100)\n");
            printf(" [ 2 ] 붕대 - 5G (HP +100, 5턴)\n");
        }
        if (chapter >= 2) {
            printf(" [ 3 ] 중형 회복 물약 - 20G (HP +200)\n");
            printf(" [ 4 ] 아스피린 - 8G (HP +200, 5턴)\n");
        }
        if (chapter >= 3) {
            printf(" [ 5 ] 대형 회복 물약 - 40G (HP +400)\n");
            printf(" [ 6 ] 모르핀 - 15G (HP +200, 2턴)\n");
        }
        if (chapter >= 4) {
            printf(" [ 7 ] 소형 치유 물약 - 60G (HP +600)\n");
            printf(" [ 8 ] 프로피탈 - 100G (HP +100, 10턴)\n");
        }
        if (chapter >= 5) {
            printf(" [ 9 ] 중형 치유 물약 - 120G (HP +1000)\n");
            printf(" [ 10 ] 성수 - 350G (부활 30%%)\n");
        }
        
        printf(" [ 0 ] 뒤로가기\n");
        printf("=================================================\n");
        printf(" 구매할 아이템 번호 > ");
        
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "0") == 0) {
            break;
        }
        
        int choice = atoi(input);
        if (choice > 0 && choice <= 10) {
            BuyItem(choice);
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
    }
}

void ShowSellMenu() {
    if (g_CurrentPlayer.inventoryCount == 0) {
        printf("\n판매할 아이템이 없습니다!\n");
        Pause();
        return;
    }
    
    char input[32];
    
    while (1) {
        ClearScreen();
        printf("=================================================\n");
        printf("              [ 상점 - 판매 ]\n");
        printf("=================================================\n");
        printf(" 소지금: %dG\n", g_CurrentPlayer.gold);
        printf("=================================================\n");
        printf(" 보유 아이템:\n");
        printf("-------------------------------------------------\n");
        
        for (int i = 0; i < g_CurrentPlayer.inventoryCount; i++) {
            ItemData item = LoadItemData(g_CurrentPlayer.inventory[i]);
            int sellPrice = item.price / 2; // 판매가는 구매가의 50%
            
            printf(" [%d] %s - %dG\n", 
                   i + 1, item.name, sellPrice);
            printf("     %s\n", item.description);
        }
        
        printf("-------------------------------------------------\n");
        printf(" [ 0 ] 뒤로가기\n");
        printf("=================================================\n");
        printf(" 판매할 아이템 번호 > ");
        
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "0") == 0) {
            break;
        }
        
        int choice = atoi(input);
        if (choice > 0 && choice <= g_CurrentPlayer.inventoryCount) {
            SellItem(choice - 1);
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
        
        // 아이템을 모두 팔았으면 자동으로 나가기
        if (g_CurrentPlayer.inventoryCount == 0) {
            printf("\n모든 아이템을 판매했습니다.\n");
            Pause();
            break;
        }
    }
}

void BuyItem(int itemId) {
    ItemData item = LoadItemData(itemId);
    
    if (item.price == 0) {
        printf("\n해당 아이템은 구매할 수 없습니다.\n");
        Pause();
        return;
    }
    
    if (g_CurrentPlayer.gold < item.price) {
        printf("\n골드가 부족합니다! (필요: %dG, 보유: %dG)\n", 
               item.price, g_CurrentPlayer.gold);
        Pause();
        return;
    }
    
    if (g_CurrentPlayer.inventoryCount >= 20) {
        printf("\n인벤토리가 가득 찼습니다!\n");
        Pause();
        return;
    }
    
    // 구매 처리
    g_CurrentPlayer.gold -= item.price;
    AddItemToInventory(&g_CurrentPlayer, itemId);
    
    printf("\n'%s'을(를) 구매했습니다! (-%dG)\n", item.name, item.price);
    Pause();
}

void SellItem(int inventoryIndex) {
    if (inventoryIndex < 0 || inventoryIndex >= g_CurrentPlayer.inventoryCount) {
        printf("\n잘못된 아이템입니다.\n");
        Pause();
        return;
    }
    
    int itemId = g_CurrentPlayer.inventory[inventoryIndex];
    ItemData item = LoadItemData(itemId);
    int sellPrice = item.price / 2;
    
    // 판매 처리
    g_CurrentPlayer.gold += sellPrice;
    
    // 인벤토리에서 제거
    for (int i = inventoryIndex; i < g_CurrentPlayer.inventoryCount - 1; i++) {
        g_CurrentPlayer.inventory[i] = g_CurrentPlayer.inventory[i + 1];
    }
    g_CurrentPlayer.inventoryCount--;
    
    printf("\n'%s'을(를) %dG에 판매했습니다!\n", item.name, sellPrice);
    Pause();
}