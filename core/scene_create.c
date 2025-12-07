#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "../system/utils.h"
#include "../system/fileio.h"
#include "../story/scene_story.h"
#include "scene_create.h"
#include "scene_town.h"

void InitializeCharacter(CharacterData* player, const char* name, JobType job) {
    strcpy(player->name, name);
    player->job = job;
    player->level = 1;
    player->exp = 0;
    player->gold = 0;
    player->statPoints = 0;
    
    // 직업별 초기 스탯 (PDF 기준)
    switch(job) {
        case JOB_WARRIOR:
            player->maxHp = 80;
            player->maxMp = 20;
            player->attack = 7;
            player->defense = 5;
            player->magicDefense = 1;
            player->str = 10;
            player->dex = 5;
            player->intel = 5;
            player->luk = 5;
            break;
        case JOB_MAGE:
            player->maxHp = 60;
            player->maxMp = 50;
            player->attack = 0;
            player->defense = 1;
            player->magicDefense = 5;
            player->str = 5;
            player->dex = 5;
            player->intel = 10;
            player->luk = 5;
            break;
        case JOB_ARCHER:
            player->maxHp = 70;
            player->maxMp = 30;
            player->attack = 6;
            player->defense = 4;
            player->magicDefense = 2;
            player->str = 5;
            player->dex = 10;
            player->intel = 5;
            player->luk = 5;
            break;
    }
    
    player->hp = player->maxHp;
    player->mp = player->maxMp;
    player->inventoryCount = 0;
    player->currentChapter = 1;
    
    // 장비 초기화
    player->weaponId = 0;
    player->helmetId = 0;
    player->armorId = 0;
    player->pantsId = 0;
    player->glovesId = 0;
    player->bootsId = 0;
}

void ShowCharacterCreate() {
    char jobInput[32];
    JobType selectedJob;

    while (1) {
        ClearScreen();

        printf("=================================================\n");
        printf("                 [ 캐릭터 생성 ]\n");
        printf("=================================================\n");
        printf("당신의 직업을 선택하세요.\n");
        printf(" [ 1 ] 전사  (HP 80, MP 20, 공격 7, 방어 5)\n");
        printf("       STR 10 | DEX 5 | INT 5 | LUK 5\n");
        printf(" [ 2 ] 마법사 (HP 60, MP 50, 공격 0, 방어 1)\n");
        printf("       STR 5 | DEX 5 | INT 10 | LUK 5\n");
        printf(" [ 3 ] 궁수  (HP 70, MP 30, 공격 6, 방어 4)\n");
        printf("       STR 5 | DEX 10 | INT 5 | LUK 5\n");
        printf(" [ 0 ] 취소\n");
        printf("-------------------------------------------------\n");
        printf(" 선택 > ");

        fgets(jobInput, sizeof(jobInput), stdin);
        jobInput[strcspn(jobInput, "\n")] = 0;

        if (strlen(jobInput) == 0) {
            printf("잘못된 입력입니다.\n");
            Pause();
            continue;
        }

        if (strcmp(jobInput, "0") == 0)
            return;
        else if (strcmp(jobInput, "1") == 0) {
            selectedJob = JOB_WARRIOR;
            break;
        }
        else if (strcmp(jobInput, "2") == 0) {
            selectedJob = JOB_MAGE;
            break;
        }
        else if (strcmp(jobInput, "3") == 0) {
            selectedJob = JOB_ARCHER;
            break;
        }

        printf("잘못된 입력입니다. 다시 선택하세요.\n");
        Pause();
    }

    char name[32];

    while (1) {
        ClearScreen();
        printf("이름을 입력하세요.\n→ ");

        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        if (strlen(name) == 0) {
            printf("이름은 비워둘 수 없습니다.\n");
            Pause();
            continue;
        }

        break;
    }

    // 전역 플레이어 초기화
    InitializeCharacter(&g_CurrentPlayer, name, selectedJob);
    
    // 저장 폴더 생성
    if (!CreatePlayerSaveFolder(name)) {
        printf("저장 폴더 생성 실패. data 폴더가 있는지 확인하세요.\n");
        Pause();
        return;
    }
    
    // 캐릭터 저장
    if (SavePlayer(&g_CurrentPlayer, name)) {
        printf("'%s' 캐릭터가 생성되었습니다!\n", name);
        
        // 현재 씬을 마을로 설정하고 저장
        g_CurrentScene = SCENE_TOWN;
        SaveScene(g_CurrentScene, name);
        
        // GameProgress 저장
        SaveProgress(&g_GameProgress, name);
        
        Pause();
        
        // 스토리는 던전 입장 시 자동 재생되므로 여기서는 제거
        
        ShowTown();
    } else {
        printf("캐릭터 저장 실패\n");
        Pause();
    }
}