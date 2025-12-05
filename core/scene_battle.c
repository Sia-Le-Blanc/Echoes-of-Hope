#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../system/utils.h"
#include "../system/fileio.h"
#include "scene_battle.h"
#include "battle_logic.h"
#include "game.h"

void ShowBattle() {
    srand(time(NULL));
    
    // 챕터1 랜덤 몬스터 로드 (임시로 망자 사냥꾼)
    MonsterData monster;
    char monsterPath[64];
    snprintf(monsterPath, sizeof(monsterPath), "data/monsters/ch1_hunter.txt");
    
    FILE* fp = fopen(monsterPath, "r");
    if (!fp) {
        printf("몬스터 데이터 로드 실패!\n");
        Pause();
        return;
    }
    
    fgets(monster.name, sizeof(monster.name), fp);
    monster.name[strcspn(monster.name, "\n")] = 0;
    fscanf(fp, "%d %d %d %d %d %d",
        &monster.level, &monster.hp, &monster.defense,
        &monster.attack, &monster.attack, &monster.dropItemId);
    fclose(fp);
    
    int monsterMaxHp = monster.hp;
    char input[32];

    while (1) {
        ClearScreen();

        printf("=================================================\n");
        printf("             [ 전투 : %s 등장 ]\n", monster.name);
        printf("=================================================\n");
        printf(" %s이(가) 당신에게 다가온다!\n\n", monster.name);
        printf(" [ 1 ] 공격하기\n");
        printf(" [ 2 ] 스킬 사용 (미구현)\n");
        printf(" [ 3 ] 방어하기 (미구현)\n");
        printf(" [ 4 ] 도망가기\n");
        printf("=================================================\n");
        printf(" %s HP %d/%d | %s HP %d/%d\n", 
            g_CurrentPlayer.name,
            g_CurrentPlayer.hp, 
            g_CurrentPlayer.maxHp,
            monster.name,
            monster.hp,
            monsterMaxHp);
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
            // 플레이어 공격
            int damage = PlayerAttack(&g_CurrentPlayer, &monster);
            printf("\n→ %s을(를) 공격! %d 데미지!\n", monster.name, damage);
            
            if (monster.hp <= 0) {
                printf("\n★ %s을(를) 처치했다!\n", monster.name);
                int expGain = monster.level * 25;
                printf("경험치 +%d\n", expGain);
                GainExp(&g_CurrentPlayer, expGain);
                Pause();
                return;
            }
            
            // 몬스터 반격
            int monsterDmg = MonsterAttack(&monster, &g_CurrentPlayer);
            printf("← %s의 반격! %d 데미지!\n", monster.name, monsterDmg);
            
            if (g_CurrentPlayer.hp <= 0) {
                printf("\n✖ 전투 패배...\n");
                g_CurrentPlayer.hp = 1;
                Pause();
                return;
            }
            
            Pause();
        }
        else if (strcmp(input, "4") == 0) {
            printf("도망쳤습니다!\n");
            Pause();
            return;
        }
        else {
            printf("잘못된 입력입니다.\n");
            Pause();
        }
    }
}