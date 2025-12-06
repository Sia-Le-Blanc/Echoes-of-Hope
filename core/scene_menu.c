#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../system/utils.h"
#include "../system/fileio.h"
#include "scene_menu.h"
#include "scene_create.h"
#include "scene_town.h"
#include "scene_admin.h"
#include "scene_settings.h"
#include "game.h"

void ShowLoadMenu() {
    char savedPlayers[10][32];
    int count = GetSavedPlayerList(savedPlayers, 10);
    
    if (count == 0) {
        ClearScreen();
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│ ECHOES OF VALOR - 불러오기                                         │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│                                                                  │\n");
        printf("│  저장된 캐릭터가 없습니다.                                             │\n");
        printf("│  먼저 새 게임을 시작해주세요.                                           │\n");
        printf("│                                                                  │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│ [ Enter ]를 눌러 돌아가기                                            │\n");
        printf("└──────────────────────────────────────────────────────────────────┘\n");
        getchar();
        return;
    }
    
    while (1) {
        ClearScreen();
        printf("┌──────────────────────────────────────────────────────────────────┐\n");
        printf("│ ECHOES OF VALOR - 불러오기                                       │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│                                                                  │\n");
        
        for (int i = 0; i < count; i++) {
            printf("│  [ %d ]  %-55s │\n", i + 1, savedPlayers[i]);
        }
        printf("│  [ 0 ]  취소                                                     │\n");
        printf("│                                                                  │\n");
        printf("├──────────────────────────────────────────────────────────────────┤\n");
        printf("│ 선택하세요 > ");
        
        char input[32];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "0") == 0) {
            return;
        }
        
        int choice = atoi(input);
        if (choice >= 1 && choice <= count) {
            char* selectedName = savedPlayers[choice - 1];
            
            if (LoadPlayer(&g_CurrentPlayer, selectedName)) {
                SceneType loadedScene;
                if (LoadScene(&loadedScene, selectedName)) {
                    g_CurrentScene = loadedScene;
                } else {
                    g_CurrentScene = SCENE_TOWN;
                }
                
                if (LoadProgress(&g_GameProgress, selectedName)) {
                    /* 진행도 로드 성공 */
                } else {
                    /* 기본값 유지 */
                }
                
                printf("\n'%s' 캐릭터를 불러왔습니다!\n", selectedName);
                printf("│                                                                  │\n");
                printf("└──────────────────────────────────────────────────────────────────┘\n");
                Pause();
                
                if (g_CurrentScene == SCENE_TOWN) {
                    ShowTown();
                }
                return;
            } else {
                printf("\n캐릭터 로드 실패\n");
                Pause();
            }
        } else {
            printf("\n잘못된 선택입니다.\n");
            printf("└──────────────────────────────────────────────────────────────────┘\n");
            Pause();
        }
    }
}

void ShowMainMenu() {
    char input[32];

    while (1) {
        ClearScreen();
        
        printf("┌──────────────────────────────────────────────────────────────────────┐\n");
        printf("│ ECHOES OF VALOR                            [v1.0 • Test • 1000110101] │\n");
        printf("├──────────────────────────────────────────────────────────────────────┤\n");
        printf("│ \"In the silence of the past, courage still echoes...\"               │\n");
        printf("│                                                                      │\n");
        printf("│  [ 1 ]  새로 시작하기                                                │\n");
        printf("│  [ 2 ]  불러오기                                                      │\n");
        printf("│  [ 3 ]  설정                                                          │\n");
        printf("│  [ 4 ]  게임 종료                                                     │\n");
        printf("│                                                                      │\n");
        printf("│  ───────────────────────────────────────────────────────────────────│\n");
        printf("│                                                                      │\n");
        printf("├──────────────────────────────────────────────────────────────────────┤\n");
        printf("│ 선택하세요 > ");

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            continue;
        }

        if (strcmp(input, "1") == 0) {
            ShowCharacterCreate();
        }
        else if (strcmp(input, "2") == 0) {
            ShowLoadMenu();
        }
        else if (strcmp(input, "3") == 0) {
            ShowSettings();
        }
        else if (strcmp(input, "4") == 0) {
            ClearScreen();
            printf("┌──────────────────────────────────────────────────────────────────┐\n");
            printf("│                                                                  │\n");
            printf("│              게임을 종료합니다. 안녕히 가세요!                   │\n");
            printf("│                                                                  │\n");
            printf("└──────────────────────────────────────────────────────────────────┘\n");
            return;
        }
        else if (strcmp(input, "1000110101") == 0) {
            ShowAdmin();
        }
        else {
            ClearScreen();
            printf("┌──────────────────────────────────────────────────────────────────┐\n");
            printf("│  잘못된 입력입니다. 다시 시도하세요.                             │\n");
            printf("└──────────────────────────────────────────────────────────────────┘\n");
            Pause();
        }
    }
}