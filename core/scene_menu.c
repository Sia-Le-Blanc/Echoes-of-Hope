#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../system/utils.h"
#include "../system/fileio.h"
#include "scene_menu.h"
#include "scene_create.h"
#include "scene_town.h"
#include "scene_admin.h"
#include "game.h"

void ShowLoadMenu() {
    char savedPlayers[10][32];
    int count = GetSavedPlayerList(savedPlayers, 10);
    
    if (count == 0) {
        printf("저장된 캐릭터가 없습니다.\n");
        Pause();
        return;
    }
    
    while (1) {
        ClearScreen();
        printf("=================================================\n");
        printf("                  [ 불러오기 ]\n");
        printf("=================================================\n");
        
        for (int i = 0; i < count; i++) {
            printf(" [ %d ] %s\n", i + 1, savedPlayers[i]);
        }
        printf(" [ 0 ] 취소\n");
        printf("=================================================\n");
        printf(" 선택 > ");
        
        char input[32];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "0") == 0) {
            return;
        }
        
        int choice = atoi(input);
        if (choice >= 1 && choice <= count) {
            char* selectedName = savedPlayers[choice - 1];
            
            // 플레이어 데이터 로드
            if (LoadPlayer(&g_CurrentPlayer, selectedName)) {
                // 씬 정보 로드
                SceneType loadedScene;
                if (LoadScene(&loadedScene, selectedName)) {
                    g_CurrentScene = loadedScene;
                } else {
                    g_CurrentScene = SCENE_TOWN;
                }
                
                printf("\n'%s' 캐릭터를 불러왔습니다!\n", selectedName);
                Pause();
                
                // 로드된 씬으로 이동
                if (g_CurrentScene == SCENE_TOWN) {
                    ShowTown();
                }
                return;
            } else {
                printf("캐릭터 로드 실패\n");
                Pause();
            }
        } else {
            printf("잘못된 선택입니다.\n");
            Pause();
        }
    }
}

void ShowMainMenu() {
    char input[32];

    while (1) {
        ClearScreen();

        printf("=================================================\n");
        printf("                    ECHOES OF VALOR\n");
        printf("=================================================\n");
        printf(" [ 1 ] 새로 시작하기\n");
        printf(" [ 2 ] 불러오기\n");
        printf(" [ 3 ] 설정 (미구현)\n");
        printf(" [ 4 ] 종료하기\n");
        printf("-------------------------------------------------\n");
        printf(" 개발자 모드 ▶ 1000110101\n");
        printf("=================================================\n");
        printf(" 선택 > ");

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            printf("잘못된 입력입니다.\n");
            Pause();
            continue;
        }

        if (strcmp(input, "1") == 0) {
            ShowCharacterCreate();
        }
        else if (strcmp(input, "2") == 0) {
            ShowLoadMenu();
        }
        else if (strcmp(input, "3") == 0) {
            ClearScreen();
            printf("설정 기능은 아직 미구현입니다.\n");
            Pause();
        }
        else if (strcmp(input, "4") == 0) {
            ClearScreen();
            printf("게임을 종료합니다.\n");
            return;
        }
        else if (strcmp(input, "1000110101") == 0) {
            ShowAdmin();
        }
        else {
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
            Pause();
        }
    }
}