#include "fileio.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

void GetPlayerSavePath(char* buffer, size_t bufSize, const char* playerName) {
    snprintf(buffer, bufSize, "data/%s/player.txt", playerName);
}

void GetSceneSavePath(char* buffer, size_t bufSize, const char* playerName) {
    snprintf(buffer, bufSize, "data/%s/save.dat", playerName);
}

void GetProgressSavePath(char* buffer, size_t bufSize, const char* playerName) {
    snprintf(buffer, bufSize, "data/%s/progress.dat", playerName);
}

int CreatePlayerSaveFolder(const char* playerName) {
    char path[64];
    snprintf(path, sizeof(path), "data/%s", playerName);
#if defined(_WIN32)
    return _mkdir(path) == 0;
#else
    return mkdir(path, 0755) == 0;
#endif
}

int GetSavedPlayerList(char names[][32], int maxCount) {
    DIR* dir = opendir("data");
    if (!dir) return 0;

    struct dirent* entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL && count < maxCount) {
        if (entry->d_name[0] == '.') continue;
        
        /* 디렉터리인지 확인 */
        char path[128];
        struct stat statbuf;
        snprintf(path, sizeof(path), "data/%s", entry->d_name);
        
        if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            /* player.txt 파일 존재 확인 */
            char playerFilePath[256];
            snprintf(playerFilePath, sizeof(playerFilePath), 
                     "data/%s/player.txt", entry->d_name);
            
            FILE* checkFile = fopen(playerFilePath, "r");
            if (checkFile) {
                fclose(checkFile);
                strncpy(names[count], entry->d_name, 31);
                names[count][31] = '\0';
                count++;
            }
        }
    }
    closedir(dir);
    return count;
}

int SavePlayer(const CharacterData* player, const char* playerName) {
    if (!player || !playerName) return 0;

    char path[64];
    GetPlayerSavePath(path, sizeof(path), playerName);

    FILE* fp = fopen(path, "w");
    if (!fp) return 0;

    // 기본 정보
    fprintf(fp, "%s\n", player->name);
    fprintf(fp, "%d\n", player->job);
    fprintf(fp, "%d\n", player->level);
    
    // 경험치/골드/스탯포인트
    fprintf(fp, "%d %d %d\n", player->exp, player->gold, player->statPoints);
    
    // HP/MP
    fprintf(fp, "%d %d %d %d\n",
        player->hp, player->maxHp, player->mp, player->maxMp);
    
    // 공격력/방어력/마법방어력
    fprintf(fp, "%d %d %d\n", player->attack, player->defense, player->magicDefense);
    
    // 추가 스탯
    fprintf(fp, "%d %d %d %d\n",
        player->str, player->dex, player->intel, player->luk);
    
    // 장비
    fprintf(fp, "%d %d %d %d %d %d\n",
        player->weaponId, player->helmetId, player->armorId,
        player->pantsId, player->glovesId, player->bootsId);
    
    // 인벤토리
    fprintf(fp, "%d\n", player->inventoryCount);
    for (int i = 0; i < player->inventoryCount; i++) {
        fprintf(fp, "%d ", player->inventory[i]);
    }
    fprintf(fp, "\n");
    
    // 현재 챕터
    fprintf(fp, "%d\n", player->currentChapter);

    fclose(fp);
    return 1;
}

int LoadPlayer(CharacterData* outPlayer, const char* playerName) {
    if (!outPlayer || !playerName) return 0;

    char path[64];
    GetPlayerSavePath(path, sizeof(path), playerName);

    FILE* fp = fopen(path, "r");
    if (!fp) return 0;

    // 기본 정보
    if (fgets(outPlayer->name, sizeof(outPlayer->name), fp) == NULL) {
        fclose(fp);
        return 0;
    }
    outPlayer->name[strcspn(outPlayer->name, "\n")] = '\0';

    int tempJob;
    fscanf(fp, "%d", &tempJob);
    outPlayer->job = (JobType)tempJob;
    
    fscanf(fp, "%d", &outPlayer->level);
    
    // 경험치/골드/스탯포인트
    fscanf(fp, "%d %d %d", &outPlayer->exp, &outPlayer->gold, &outPlayer->statPoints);
    
    // HP/MP
    fscanf(fp, "%d %d %d %d",
        &outPlayer->hp, &outPlayer->maxHp, &outPlayer->mp, &outPlayer->maxMp);
    
    // 공격력/방어력/마법방어력
    fscanf(fp, "%d %d %d", &outPlayer->attack, &outPlayer->defense, &outPlayer->magicDefense);
    
    // 추가 스탯
    fscanf(fp, "%d %d %d %d",
        &outPlayer->str, &outPlayer->dex, &outPlayer->intel, &outPlayer->luk);
    
    // 장비
    fscanf(fp, "%d %d %d %d %d %d",
        &outPlayer->weaponId, &outPlayer->helmetId, &outPlayer->armorId,
        &outPlayer->pantsId, &outPlayer->glovesId, &outPlayer->bootsId);
    
    // 인벤토리
    fscanf(fp, "%d", &outPlayer->inventoryCount);
    for (int i = 0; i < outPlayer->inventoryCount; i++) {
        fscanf(fp, "%d", &outPlayer->inventory[i]);
    }
    
    // 현재 챕터
    if (fscanf(fp, "%d", &outPlayer->currentChapter) != 1) {
        outPlayer->currentChapter = 1; // 기본값
    }

    fclose(fp);
    return 1;
}

int SaveScene(SceneType scene, const char* playerName) {
    char path[64];
    GetSceneSavePath(path, sizeof(path), playerName);

    FILE* fp = fopen(path, "w");
    if (!fp) return 0;

    fprintf(fp, "%d\n", scene);
    fclose(fp);
    return 1;
}

int LoadScene(SceneType* outScene, const char* playerName) {
    if (!outScene || !playerName) return 0;

    char path[64];
    GetSceneSavePath(path, sizeof(path), playerName);

    FILE* fp = fopen(path, "r");
    if (!fp) return 0;

    int tempScene;
    fscanf(fp, "%d", &tempScene);
    *outScene = (SceneType)tempScene;

    fclose(fp);
    return 1;
}

int LoadMonster(MonsterData* outMonster, int monsterId) {
    if (!outMonster || monsterId <= 0) return 0;

    char path[64];
    snprintf(path, sizeof(path), "data/monster_%d.txt", monsterId);

    FILE* fp = fopen(path, "r");
    if (!fp) return 0;

    fgets(outMonster->name, sizeof(outMonster->name), fp);
    outMonster->name[strcspn(outMonster->name, "\n")] = '\0';

    fscanf(fp, "%d %d %d %d %d",
        &outMonster->level, &outMonster->hp,
        &outMonster->attack, &outMonster->defense,
        &outMonster->dropItemId
    );
    outMonster->id = monsterId;

    fclose(fp);
    return 1;
}

int LoadEquipment(EquipmentData* outEquip, int equipId) {
    if (!outEquip || equipId <= 0) return 0;

    char path[64];
    snprintf(path, sizeof(path), "data/equipment_%d.txt", equipId);

    FILE* fp = fopen(path, "r");
    if (!fp) return 0;

    fgets(outEquip->name, sizeof(outEquip->name), fp);
    outEquip->name[strcspn(outEquip->name, "\n")] = '\0';

    int slotTemp;
    fscanf(fp, "%d %d %d %d %d",
        &slotTemp, &outEquip->attack,
        &outEquip->defense, &outEquip->price,
        &outEquip->id
    );
    outEquip->slot = (EquipmentSlot)slotTemp;

    fgetc(fp);
    fgets(outEquip->lore, sizeof(outEquip->lore), fp);
    outEquip->lore[strcspn(outEquip->lore, "\n")] = '\0';

    fclose(fp);
    return 1;
}

int SaveProgress(const GameProgress* progress, const char* playerName) {
    if (!progress || !playerName) return 0;
    
    char path[64];
    GetProgressSavePath(path, sizeof(path), playerName);
    
    FILE* fp = fopen(path, "w");
    if (!fp) return 0;
    
    fprintf(fp, "%d %d %d %d\n",
        progress->currentChapter,
        progress->storyProgress,
        progress->monstersDefeated,
        progress->difficulty);
    
    // 챕터 클리어 여부
    for (int i = 0; i < 5; i++) {
        fprintf(fp, "%d ", progress->chapterCleared[i]);
    }
    fprintf(fp, "\n");
    
    fprintf(fp, "%d %d\n", progress->totalPlayTime, progress->deaths);
    
    fclose(fp);
    return 1;
}

int LoadProgress(GameProgress* outProgress, const char* playerName) {
    if (!outProgress || !playerName) return 0;
    
    char path[64];
    GetProgressSavePath(path, sizeof(path), playerName);
    
    FILE* fp = fopen(path, "r");
    if (!fp) return 0;
    
    int tempDifficulty;
    fscanf(fp, "%d %d %d %d",
        &outProgress->currentChapter,
        &outProgress->storyProgress,
        &outProgress->monstersDefeated,
        &tempDifficulty);
    outProgress->difficulty = (Difficulty)tempDifficulty;
    
    // 챕터 클리어 여부
    for (int i = 0; i < 5; i++) {
        fscanf(fp, "%d", &outProgress->chapterCleared[i]);
    }
    
    fscanf(fp, "%d %d", &outProgress->totalPlayTime, &outProgress->deaths);
    
    fclose(fp);
    return 1;
}