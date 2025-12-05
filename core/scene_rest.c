#include <stdio.h>
#include <string.h>
#include "../system/utils.h"
#include "scene_rest.h"
#include "game.h"

void ShowRest() {
    char input[32];
    int restCost = 50; // 휴식 비용
    
    while (1) {
        ClearScreen();
        
        printf("=================================================\n");
        printf("                  [ 여관 휴식 ]\n");
        printf("=================================================\n");
        printf(" 여관 주인: 휴식하시겠습니까?\n");
        printf(" HP/MP가 전부 회복됩니다.\n\n");
        printf(" 비용: %d Gold\n", restCost);
        printf("-------------------------------------------------\n");
        printf(" 현재 Gold: %d\n", g_CurrentPlayer.exp); // 임시로 exp 사용
        printf(" 현재 상태: HP %d/%d | MP %d/%d\n",
               g_CurrentPlayer.hp, g_CurrentPlayer.maxHp,
               g_CurrentPlayer.mp, g_CurrentPlayer.maxMp);
        printf("=================================================\n");
        printf(" [ 1 ] 휴식하기 (%d Gold)\n", restCost);
        printf(" [ 0 ] 나가기\n");
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
            if (g_CurrentPlayer.hp >= g_CurrentPlayer.maxHp && 
                g_CurrentPlayer.mp >= g_CurrentPlayer.maxMp) {
                printf("\n이미 최대 체력/마나입니다!\n");
                Pause();
                continue;
            }
            
            // Gold 체크는 나중에 구현
            printf("\n푹 쉬었습니다...\n");
            g_CurrentPlayer.hp = g_CurrentPlayer.maxHp;
            g_CurrentPlayer.mp = g_CurrentPlayer.maxMp;
            printf("HP/MP가 전부 회복되었습니다!\n");
            Pause();
            return;
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
    }
}