#include <stdio.h>
#include <string.h>
#include "../system/utils.h"
#include "scene_shop.h"
#include "game.h"

void ShowShop() {
    char input[32];
    
    // 챕터1 포션 가격 (임시)
    int smallPotionPrice = 10;
    int bandagePrice = 5;
    
    while (1) {
        ClearScreen();
        
        printf("=================================================\n");
        printf("                   [ 상점 ]\n");
        printf("=================================================\n");
        printf(" 상인: 어서오세요! 필요한 물건이 있으신가요?\n\n");
        printf(" [ 1 ] 소형 회복 물약 - %d Gold (HP +100)\n", smallPotionPrice);
        printf(" [ 2 ] 붕대 - %d Gold (5턴 HP +20)\n", bandagePrice);
        printf(" [ 3 ] 장비 보기 (미구현)\n");
        printf(" [ 0 ] 나가기\n");
        printf("-------------------------------------------------\n");
        printf(" 현재 Gold: %d (임시)\n", g_CurrentPlayer.exp);
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
            printf("\n소형 회복 물약 구매 (미구현)\n");
            Pause();
        }
        else if (strcmp(input, "2") == 0) {
            printf("\n붕대 구매 (미구현)\n");
            Pause();
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
    }
}