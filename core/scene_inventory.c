#include <stdio.h>
#include <string.h>
#include "../system/utils.h"
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
                printf(" [%d] 아이템 ID: %d\n", i + 1, g_CurrentPlayer.inventory[i]);
            }
        }
        
        printf("-------------------------------------------------\n");
        printf(" 인벤토리: %d/20\n", g_CurrentPlayer.inventoryCount);
        printf("=================================================\n");
        printf(" [ 0 ] 나가기\n");
        printf("=================================================\n");
        printf(" 선택 > ");
        
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "0") == 0) {
            return;
        }
        
        printf("아이템 사용 기능은 미구현입니다.\n");
        Pause();
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
        printf(" [ 1 ] 장비 해제 (미구현)\n");
        printf(" [ 0 ] 나가기\n");
        printf("=================================================\n");
        printf(" 선택 > ");
        
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "0") == 0) {
            return;
        }
        
        printf("장비 해제 기능은 미구현입니다.\n");
        Pause();
    }
}