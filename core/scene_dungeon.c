#include "scene_dungeon.h"
#include "chapter_data.h"
#include "game.h"
#include "combat_system.h"
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
    if (!monster) return 0;
    
    int monsterMaxHp = monster->hp;
    char input[32];
    
    while (1) {
        ClearScreen();
        
        printf("=================================================\n");
        if (isBoss) {
            printf("          [ 보스 전투 : %s ]\n", monster->name);
        } else {
            printf("          [ 전투 : %s ]\n", monster->name);
        }
        printf("=================================================\n");
        printf(" %s이(가) 나타났다!\n\n", monster->name);
        printf(" [ 1 ] 공격하기\n");
        printf(" [ 2 ] 도망가기\n");
        printf("=================================================\n");
        printf(" %s HP %d/%d | %s HP %d/%d\n",
               g_CurrentPlayer.name, g_CurrentPlayer.hp, g_CurrentPlayer.maxHp,
               monster->name, monster->hp, monsterMaxHp);
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
            AttackResult playerAttack = CalculateAttack(&g_CurrentPlayer, monster);
            
            printf("\n→ %s을(를) 공격!\n", monster->name);
            if (playerAttack.isCritical) {
                printf("   ★ 치명타! %d 데미지!\n", playerAttack.actualDamage);
            } else {
                printf("   %d 데미지!\n", playerAttack.actualDamage);
            }
            
            if (monster->hp <= 0) {
                printf("\n★ %s을(를) 처치했다!\n", monster->name);
                int expGain = monster->level * 25;
                int goldGain = monster->level * 10;
                printf("경험치 +%d, Gold +%d\n", expGain, goldGain);
                
                g_CurrentPlayer.exp += expGain;
                g_CurrentPlayer.gold += goldGain;
                
                Pause();
                return 1;
            }
            
            AttackResult monsterAttack = CalculateMonsterAttack(monster, &g_CurrentPlayer);
            
            printf("← %s의 반격!\n", monster->name);
            if (monsterAttack.isDodged) {
                printf("   ◆ 회피했다!\n");
            } else {
                printf("   %d 데미지!\n", monsterAttack.actualDamage);
            }
            
            if (g_CurrentPlayer.hp <= 0) {
                printf("\n✖ 전투 패배...\n");
                g_CurrentPlayer.hp = 1;
                g_GameProgress.deaths++;
                Pause();
                return 0;
            }
            
            Pause();
        }
        else if (strcmp(input, "2") == 0) {
            if (isBoss) {
                printf("\n보스전에서는 도망갈 수 없습니다!\n");
                Pause();
            } else {
                printf("\n도망쳤습니다!\n");
                Pause();
                return 0;
            }
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
    }
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