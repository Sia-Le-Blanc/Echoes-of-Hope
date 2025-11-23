#include <stdio.h>
#include <string.h>
#include "../system/utils.h"
#include "scene_battle.h"
#include "game.h"

void ShowBattle() {
    char input[32];

    while (1) {
        ClearScreen();

        printf("=================================================\n");
        printf("             [ 전투 : 슬라임 등장 ]\n");
        printf("=================================================\n");
        printf(" 슬라임이 당신에게 다가온다!\n\n");
        printf(" [ 1 ] 공격하기 (미구현)\n");
        printf(" [ 2 ] 스킬 사용 (미구현)\n");
        printf(" [ 3 ] 방어하기 (미구현)\n");
        printf(" [ 4 ] 도망가기\n");
        printf("=================================================\n");
        printf(" %s HP %d/%d | 슬라임 HP 50/50\n", 
            g_CurrentPlayer.name,
            g_CurrentPlayer.hp, 
            g_CurrentPlayer.maxHp);
        printf("=================================================\n");
        printf(" 선택 > ");

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            printf("잘못된 입력입니다.\n");
            Pause();
            continue;
        }

        if (strcmp(input, "4") == 0) {
            printf("도망쳤습니다!\n");
            Pause();
            return;
        }

        printf("잘못된 입력입니다.\n");
        Pause();
    }
}