#include <stdio.h>
#include <string.h>
#include "../system/utils.h"
#include "scene_settings.h"
#include "game.h"

void ShowSettings() {
    char input[32];

    while (1) {
        ClearScreen();

        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│ ECHOES OF VALOR - 설정                                           │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│                                                                  │\n");
        printf("│  [ 1 ]  난이도 변경                                              │\n");
        printf("│  [ 2 ]  이름 변경 (미구현)                                       │\n");
        printf("│  [ 3 ]  사운드 설정 (미구현)                                     │\n");
        printf("│  [ 0 ]  돌아가기                                                 │\n");
        printf("│                                                                  │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        
        const char* difficultyName = "보통";
        if (g_GameProgress.difficulty == DIFFICULTY_EASY) difficultyName = "쉬움";
        else if (g_GameProgress.difficulty == DIFFICULTY_HARD) difficultyName = "어려움";
        
        printf("│ 현재 난이도: %s                                                  │\n", difficultyName);
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│ 선택하세요 > ");

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            continue;
        }

        if (strcmp(input, "0") == 0) {
            return;
        }
        else if (strcmp(input, "1") == 0) {
            ClearScreen();
            printf("┌──────────────────────────────────────────────────────────────────┐\n");
            printf("│ 난이도 선택                                                      │\n");
            printf("├──────────────────────────────────────────────────────────────────┤\n");
            printf("│                                                                  │\n");
            printf("│  [ 1 ]  쉬움   - 적 HP 70%%, 받는 데미지 80%%                    │\n");
            printf("│  [ 2 ]  보통   - 기본 밸런스                                     │\n");
            printf("│  [ 3 ]  어려움 - 적 HP 130%%, 받는 데미지 120%%                  │\n");
            printf("│  [ 0 ]  취소                                                     │\n");
            printf("│                                                                  │\n");
            printf("├──────────────────────────────────────────────────────────────────┤\n");
            printf("│ 선택하세요 > ");
            
            char diffInput[32];
            fgets(diffInput, sizeof(diffInput), stdin);
            diffInput[strcspn(diffInput, "\n")] = 0;
            
            if (strcmp(diffInput, "1") == 0) {
                g_GameProgress.difficulty = DIFFICULTY_EASY;
                printf("│ 난이도가 '쉬움'으로 변경되었습니다.                              │\n");
            }
            else if (strcmp(diffInput, "2") == 0) {
                g_GameProgress.difficulty = DIFFICULTY_NORMAL;
                printf("│ 난이도가 '보통'으로 변경되었습니다.                              │\n");
            }
            else if (strcmp(diffInput, "3") == 0) {
                g_GameProgress.difficulty = DIFFICULTY_HARD;
                printf("│ 난이도가 '어려움'으로 변경되었습니다.                            │\n");
            }
            printf("└──────────────────────────────────────────────────────────────────┘\n");
            Pause();
        }
        else if (strcmp(input, "2") == 0) {
            ClearScreen();
            printf("┌──────────────────────────────────────────────────────────────────┐\n");
            printf("│ 이름 변경 - 미구현                                               │\n");
            printf("│ 추후 캐릭터 이름 변경 기능 추가 예정                             │\n");
            printf("└──────────────────────────────────────────────────────────────────┘\n");
            Pause();
        }
        else if (strcmp(input, "3") == 0) {
            ClearScreen();
            printf("┌──────────────────────────────────────────────────────────────────┐\n");
            printf("│ 사운드 설정 - 미구현                                             │\n");
            printf("│ 콘솔 게임이므로 사운드 기능은 제한적입니다.                      │\n");
            printf("└──────────────────────────────────────────────────────────────────┘\n");
            Pause();
        }
        else {
            printf("\n잘못된 입력입니다.\n");
            printf("└──────────────────────────────────────────────────────────────────┘\n");
            Pause();
        }
    }
}