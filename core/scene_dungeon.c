#include "scene_dungeon.h"
#include "chapter_data.h"
#include "game.h"
#include "../story/scene_story.h"
#include "../system/utils.h"
#include "../system/fileio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

MonsterData LoadRandomMonster(int chapter) {
    MonsterData monster = {0};
    
    // 챕터별 몬스터 수
    int count = CHAPTER_MONSTER_COUNTS[chapter - 1];
    int randomIndex = rand() % count;
    
    const char* monsterName = CHAPTER_MONSTERS[chapter - 1][randomIndex];
    
    char path[64];
    snprintf(path, sizeof(path), "data/monsters/%s.txt", monsterName);
    
    FILE* fp = fopen(path, "r");
    if (!fp) {
        printf("몬스터 로드 실패: %s\n", path);
        Pause();
        return monster;
    }
    
    fgets(monster.name, sizeof(monster.name), fp);
    monster.name[strcspn(monster.name, "\n")] = 0;
    
    fscanf(fp, "%d %d %d %d %d %d",
        &monster.level, &monster.hp, &monster.defense,
        &monster.attack, &monster.attack, &monster.dropItemId);
    
    fclose(fp);
    return monster;
}

MonsterData LoadBoss(int chapter) {
    MonsterData boss = {0};
    
    const char* bossName = CHAPTER_BOSSES[chapter - 1];
    
    char path[64];
    snprintf(path, sizeof(path), "data/monsters/%s.txt", bossName);
    
    FILE* fp = fopen(path, "r");
    if (!fp) {
        printf("보스 로드 실패: %s\n", path);
        Pause();
        return boss;
    }
    
    fgets(boss.name, sizeof(boss.name), fp);
    boss.name[strcspn(boss.name, "\n")] = 0;
    
    fscanf(fp, "%d %d %d %d %d %d",
        &boss.level, &boss.hp, &boss.defense,
        &boss.attack, &boss.attack, &boss.dropItemId);
    
    fclose(fp);
    return boss;
}

int BattleWithMonster(MonsterData* monster, int isBoss) {
    // TODO: scene_battle.c의 전투 로직을 여기로 이동
    // 지금은 임시로 1 반환
    return 1;
}

void ShowDungeon() {
    srand(time(NULL));
    
    int chapter = g_GameProgress.currentChapter;
    
    // 1. 챕터 인트로 스토리
    if (g_GameProgress.storyProgress == 0) {
        if (chapter == 1) ShowStory(1, "intro");
        else if (chapter == 2) ShowStory(2, "intro");
        else if (chapter == 3) ShowStory(3, "intro");
        else if (chapter == 4) ShowStory(4, "intro");
        g_GameProgress.storyProgress = 1;
    }
    
    // 2. 일반 몬스터 5마리
    while (g_GameProgress.monstersDefeated < 5) {
        MonsterData monster = LoadRandomMonster(chapter);
        
        if (!BattleWithMonster(&monster, 0)) {
            // 패배 또는 도망
            printf("\n던전을 빠져나왔습니다...\n");
            Pause();
            g_GameProgress.monstersDefeated = 0;
            g_GameProgress.storyProgress = 0;
            return;
        }
        
        g_GameProgress.monstersDefeated++;
        
        // 중간 스토리
        if (chapter == 1 && g_GameProgress.monstersDefeated == 2) {
            ShowStory(1, "village");
        }
        else if (chapter == 1 && g_GameProgress.monstersDefeated == 4) {
            ShowStory(1, "rumor");
        }
    }
    
    // 3. 보스 등장 스토리
    if (chapter == 1) ShowStory(1, "boss");
    else if (chapter == 2) ShowStory(2, "church");
    else if (chapter == 3) ShowStory(3, "boss");
    else if (chapter == 4) ShowStory(4, "ending");
    
    // 4. 보스 전투
    MonsterData boss = LoadBoss(chapter);
    
    if (!BattleWithMonster(&boss, 1)) {
        printf("\n보스에게 패배했습니다...\n");
        Pause();
        g_GameProgress.monstersDefeated = 0;
        g_GameProgress.storyProgress = 0;
        return;
    }
    
    // 5. 챕터 클리어
    printf("\n★★★ 챕터 %d 클리어! ★★★\n", chapter);
    g_GameProgress.chapterCleared[chapter - 1] = 1;
    g_GameProgress.monstersDefeated = 0;
    g_GameProgress.storyProgress = 0;
    
    if (chapter < 4) {
        g_GameProgress.currentChapter++;
        printf("다음 챕터가 해금되었습니다!\n");
    } else if (chapter == 4) {
        // 최종 챕터 해금
        printf("최종 챕터가 해금되었습니다!\n");
        g_GameProgress.currentChapter = 5;
    } else {
        // 게임 클리어
        ShowStory(5, "ending");
        printf("\n\n★★★ 게임 클리어! ★★★\n");
    }
    
    Pause();
}