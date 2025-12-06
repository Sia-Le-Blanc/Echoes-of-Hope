#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../system/utils.h"
#include "../system/item_manager.h"
#include "../system/equipment_manager.h"
#include "scene_inventory.h"
#include "game.h"

void ShowInventory() {
    char input[32];
    
    while (1) {
        ClearScreen();
        
        printf("=================================================\n");
        printf("                 [ 인벤토리 ]\n");
        printf("=================================================\n");
        
        if (g_CurrentPlayer.inventoryCount == 0) {
            printf(" 인벤토리가 비어있습니다.\n");
        } else {
            printf(" 보유 아이템:\n");
            for (int i = 0; i < g_CurrentPlayer.inventoryCount; i++) {
                ItemData item = LoadItemData(g_CurrentPlayer.inventory[i]);
                printf(" [%d] %s - %s\n", 
                       i + 1, item.name, item.description);
            }
        }
        
        printf("-------------------------------------------------\n");
        printf(" 인벤토리: %d/20\n", g_CurrentPlayer.inventoryCount);
        printf("=================================================\n");
        printf(" [ 숫자 ] 아이템 사용\n");
        printf(" [ 0 ] 나가기\n");
        printf("=================================================\n");
        printf(" 선택 > ");
        
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "0") == 0) {
            return;
        }
        
        int choice = atoi(input);
        if (choice > 0 && choice <= g_CurrentPlayer.inventoryCount) {
            UseItem(&g_CurrentPlayer, choice - 1);
            Pause();
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
    }
}

void ShowEquipment() {
    char input[32];
    
    while (1) {
        ClearScreen();
        
        printf("=================================================\n");
        printf("                 [ 장비 관리 ]\n");
        printf("=================================================\n");
        printf(" 현재 장착 중인 장비:\n\n");
        printf(" 무기: %s\n", g_CurrentPlayer.weaponId > 0 ? "장착됨" : "없음");
        printf(" 투구: %s\n", g_CurrentPlayer.helmetId > 0 ? "장착됨" : "없음");
        printf(" 상의: %s\n", g_CurrentPlayer.armorId > 0 ? "장착됨" : "없음");
        printf(" 하의: %s\n", g_CurrentPlayer.pantsId > 0 ? "장착됨" : "없음");
        printf(" 장갑: %s\n", g_CurrentPlayer.glovesId > 0 ? "장착됨" : "없음");
        printf(" 신발: %s\n", g_CurrentPlayer.bootsId > 0 ? "장착됨" : "없음");
        printf("-------------------------------------------------\n");
        printf(" 총 공격력: %d | 총 방어력: %d\n",
               g_CurrentPlayer.attack, g_CurrentPlayer.defense);
        printf("=================================================\n");
        printf(" [ 1 ] 무기 해제\n");
        printf(" [ 2 ] 투구 해제\n");
        printf(" [ 3 ] 상의 해제\n");
        printf(" [ 4 ] 하의 해제\n");
        printf(" [ 5 ] 장갑 해제\n");
        printf(" [ 6 ] 신발 해제\n");
        printf(" [ 0 ] 나가기\n");
        printf("=================================================\n");
        printf(" 선택 > ");
        
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "0") == 0) {
            return;
        }
        else if (strcmp(input, "1") == 0) {
            UnequipItem(&g_CurrentPlayer, EQUIP_WEAPON);
            Pause();
        }
        else if (strcmp(input, "2") == 0) {
            UnequipItem(&g_CurrentPlayer, EQUIP_HELMET);
            Pause();
        }
        else if (strcmp(input, "3") == 0) {
            UnequipItem(&g_CurrentPlayer, EQUIP_ARMOR);
            Pause();
        }
        else if (strcmp(input, "4") == 0) {
            UnequipItem(&g_CurrentPlayer, EQUIP_PANTS);
            Pause();
        }
        else if (strcmp(input, "5") == 0) {
            UnequipItem(&g_CurrentPlayer, EQUIP_GLOVES);
            Pause();
        }
        else if (strcmp(input, "6") == 0) {
            UnequipItem(&g_CurrentPlayer, EQUIP_BOOTS);
            Pause();
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
    }
}