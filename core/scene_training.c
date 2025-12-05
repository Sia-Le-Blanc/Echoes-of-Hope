#include <stdio.h>
#include <string.h>
#include "../system/utils.h"
#include "scene_training.h"
#include "game.h"

void ShowTraining() {
    char input[32];
    int trainingCost = 100; // 훈련 비용
    
    while (1) {
        ClearScreen();
        
        printf("=================================================\n");
        printf("                  [ 훈련소 ]\n");
        printf("=================================================\n");
        printf(" 훈련교관: 훈련을 통해 더 강해질 수 있소!\n");
        printf(" 공격력 또는 방어력을 영구적으로 증가시킵니다.\n\n");
        printf(" 비용: %d Gold (임시)\n", trainingCost);
        printf("-------------------------------------------------\n");
        printf(" 현재 상태:\n");
        printf("   공격력: %d\n", g_CurrentPlayer.attack);
        printf("   방어력: %d\n", g_CurrentPlayer.defense);
        printf("   HP: %d/%d\n", g_CurrentPlayer.hp, g_CurrentPlayer.maxHp);
        printf("=================================================\n");
        printf(" [ 1 ] 공격력 훈련 (+2 공격력)\n");
        printf(" [ 2 ] 방어력 훈련 (+2 방어력)\n");
        printf(" [ 3 ] 체력 훈련 (+20 최대 HP)\n");
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
            printf("\n강도 높은 공격 훈련을 받았다!\n");
            g_CurrentPlayer.attack += 2;
            printf("공격력이 2 증가했습니다! (현재: %d)\n", g_CurrentPlayer.attack);
            Pause();
        }
        else if (strcmp(input, "2") == 0) {
            printf("\n방어 자세를 집중 훈련했다!\n");
            g_CurrentPlayer.defense += 2;
            printf("방어력이 2 증가했습니다! (현재: %d)\n", g_CurrentPlayer.defense);
            Pause();
        }
        else if (strcmp(input, "3") == 0) {
            printf("\n체력 단련 훈련을 받았다!\n");
            g_CurrentPlayer.maxHp += 20;
            g_CurrentPlayer.hp += 20;
            printf("최대 HP가 20 증가했습니다! (현재: %d)\n", g_CurrentPlayer.maxHp);
            Pause();
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
    }
}