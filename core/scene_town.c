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