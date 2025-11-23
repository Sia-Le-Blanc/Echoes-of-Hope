#include <stdio.h>
#include <string.h>
#include "../system/utils.h"
#include "scene_town.h"
#include "scene_battle.h"
#include "game.h"

void ShowTown() {
    char input[32];

    while (1) {
        ClearScreen();

        printf("=================================================\n");
        printf("             [ 마을 : 평온의 숲 ]\n");
        printf("=================================================\n");
        printf(" [ 1 ] 훈련소 (미구현)\n");
        printf(" [ 2 ] 상점 (미구현)\n");
        printf(" [ 3 ] 휴식 (미구현)\n");
        printf(" [ 4 ] 장비 정비 (미구현)\n");
        printf(" [ 5 ] 던전으로 출발\n");
        printf(" [ 0 ] 메인 메뉴로 돌아가기\n");
        printf("-------------------------------------------------\n");
        printf(" 현재 상태: %s | LV.%d | HP %d/%d | MP %d/%d\n",
               g_CurrentPlayer.name,
               g_CurrentPlayer.level,
               g_CurrentPlayer.hp, g_CurrentPlayer.maxHp,
               g_CurrentPlayer.mp, g_CurrentPlayer.maxMp);
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
        else if (strcmp(input, "5") == 0) {
            ShowBattle();
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
    }
}
