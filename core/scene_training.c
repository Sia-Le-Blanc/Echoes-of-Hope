#include <stdio.h>
#include <string.h>
#include "../system/utils.h"
#include "scene_training.h"
#include "game.h"

void ShowTraining() {
    char input[32];
    int trainingCost = 100;
    
    while (1) {
        ClearScreen();
        
        printf("=================================================\n");
        printf("                  [ 훈련소 ]\n");
        printf("=================================================\n");
        printf(" 훈련교관: 훈련을 통해 더 강해질 수 있소!\n");
        printf(" 스탯을 영구적으로 증가시킵니다.\n\n");
        printf(" 비용: %d Gold\n", trainingCost);
        printf("-------------------------------------------------\n");
        printf(" 현재 상태:\n");
        printf("   STR (힘): %d\n", g_CurrentPlayer.str);
        printf("   DEX (민첩): %d\n", g_CurrentPlayer.dex);
        printf("   INT (지능): %d\n", g_CurrentPlayer.intel);
        printf("   LUK (행운): %d\n", g_CurrentPlayer.luk);
        printf("   공격력: %d | 방어력: %d\n", 
               g_CurrentPlayer.attack, g_CurrentPlayer.defense);
        printf("=================================================\n");
        printf(" [ 1 ] STR 훈련 (+2 힘)\n");
        printf(" [ 2 ] DEX 훈련 (+2 민첩)\n");
        printf(" [ 3 ] INT 훈련 (+2 지능)\n");
        printf(" [ 4 ] LUK 훈련 (+2 행운)\n");
        printf(" [ 5 ] 체력 훈련 (+20 최대 HP)\n");
        printf(" [ 0 ] 나가기\n");
        printf("=================================================\n");
        printf(" 현재 Gold: %d\n", g_CurrentPlayer.gold);
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
        
        // Gold 체크
        if (g_CurrentPlayer.gold < trainingCost) {
            printf("\nGold가 부족합니다! (필요: %d Gold)\n", trainingCost);
            Pause();
            continue;
        }
        
        if (strcmp(input, "1") == 0) {
            printf("\n강도 높은 힘 훈련을 받았다!\n");
            g_CurrentPlayer.str += 2;
            g_CurrentPlayer.gold -= trainingCost;
            printf("STR +2 (현재: %d)\n", g_CurrentPlayer.str);
            printf("공격력과 HP가 증가합니다!\n");
            Pause();
        }
        else if (strcmp(input, "2") == 0) {
            printf("\n민첩 훈련을 받았다!\n");
            g_CurrentPlayer.dex += 2;
            g_CurrentPlayer.gold -= trainingCost;
            printf("DEX +2 (현재: %d)\n", g_CurrentPlayer.dex);
            printf("회피율과 방어력이 증가합니다!\n");
            Pause();
        }
        else if (strcmp(input, "3") == 0) {
            printf("\n마법 지식 훈련을 받았다!\n");
            g_CurrentPlayer.intel += 2;
            g_CurrentPlayer.gold -= trainingCost;
            printf("INT +2 (현재: %d)\n", g_CurrentPlayer.intel);
            printf("마법 공격력과 MP가 증가합니다!\n");
            Pause();
        }
        else if (strcmp(input, "4") == 0) {
            printf("\n행운 훈련을 받았다!\n");
            g_CurrentPlayer.luk += 2;
            g_CurrentPlayer.gold -= trainingCost;
            printf("LUK +2 (현재: %d)\n", g_CurrentPlayer.luk);
            printf("치명타율과 드랍률이 증가합니다!\n");
            Pause();
        }
        else if (strcmp(input, "5") == 0) {
            printf("\n체력 단련 훈련을 받았다!\n");
            g_CurrentPlayer.maxHp += 20;
            g_CurrentPlayer.hp += 20;
            g_CurrentPlayer.gold -= trainingCost;
            printf("최대 HP +20 (현재: %d)\n", g_CurrentPlayer.maxHp);
            Pause();
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
    }
}