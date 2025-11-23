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
        if (entry->d_type == DT_DIR) {
            strncpy(names[count], entry->d_name, 31);
            names[count][31] = '\0';
            count++;
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

    fprintf(fp, "%s\n", player->name);
    fprintf(fp, "%d\n", player->job);
    fprintf(fp, "%d %d %d %d %d\n",
        player->level, player->exp, player->hp,
        player->maxHp, player->attack
    );

    fclose(fp);
    return 1;
}

int LoadPlayer(CharacterData* outPlayer, const char* playerName) {
    if (!outPlayer || !playerName) return 0;

    char path[64];
    GetPlayerSavePath(path, sizeof(path), playerName);

    FILE* fp = fopen(path, "r");
    if (!fp) return 0;

    if (fgets(outPlayer->name, sizeof(outPlayer->name), fp) == NULL) {
        fclose(fp);
        return 0;
    }
    outPlayer->name[strcspn(outPlayer->name, "\n")] = '\0';

    int tempJob;
    fscanf(fp, "%d", &tempJob);
    outPlayer->job = (JobType)tempJob;

    fscanf(fp, "%d %d %d %d %d",
        &outPlayer->level, &outPlayer->exp,
        &outPlayer->hp, &outPlayer->maxHp, &outPlayer->attack
    );

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

    fgetc(fp);  // 개행 제거
    fgets(outEquip->lore, sizeof(outEquip->lore), fp);
    outEquip->lore[strcspn(outEquip->lore, "\n")] = '\0';  // 오타 수정됨

    fclose(fp);
    return 1;
}