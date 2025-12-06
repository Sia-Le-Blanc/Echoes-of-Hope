#include <stdio.h>
#include <string.h>
#include "../system/utils.h"
#include "scene_town.h"
#include "scene_dungeon.h"
#include "scene_training.h"
#include "scene_shop.h"
#include "scene_rest.h"
#include "scene_inventory.h"
#include "game.h"

void ShowTown() {
    char input[32];

    while (1) {
        ClearScreen();

        printf("=================================================\n");
        printf("             [ 마을 : 평온의 숲 ]\n");
        printf("=================================================\n");
        printf(" [ 1 ] 훈련소\n");
        printf(" [ 2 ] 상점\n");
        printf(" [ 3 ] 휴식\n");
        printf(" [ 4 ] 장비 관리\n");
        printf(" [ 5 ] 인벤토리\n");
        printf(" [ 6 ] 던전으로 출발\n");
        printf(" [ 0 ] 메인 메뉴로 돌아가기\n");
        printf("-------------------------------------------------\n");
        printf(" 현재 상태: %s | LV.%d | HP %d/%d | MP %d/%d\n",
               g_CurrentPlayer.name,
               g_CurrentPlayer.level,
               g_CurrentPlayer.hp, g_CurrentPlayer.maxHp,
               g_CurrentPlayer.mp, g_CurrentPlayer.maxMp);
        printf(" Gold: %d | 챕터: %d\n",
               g_CurrentPlayer.gold,
               g_GameProgress.currentChapter);
        printf("=================================================\n");
        printf(" 선택 > ");

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            printf("잘못된 입력입니다.\n");
            Pause();
            continue;
        }

        if (strcmp(input, "0") == 0) return;
        else if (strcmp(input, "1") == 0) {
            ShowTraining();
        }
        else if (strcmp(input, "2") == 0) {
            ShowShop();
        }
        else if (strcmp(input, "3") == 0) {
            ShowRest();
        }
        else if (strcmp(input, "4") == 0) {
            ShowEquipment();
        }
        else if (strcmp(input, "5") == 0) {
            ShowInventory();
        }
        else if (strcmp(input, "6") == 0) {
            ShowDungeon();
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
    }
}