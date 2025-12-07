#ifndef GAME_H
#define GAME_H

// 직업 타입
typedef enum {
    JOB_WARRIOR = 1,
    JOB_MAGE = 2,
    JOB_ARCHER = 3
} JobType;

// 플레이어 데이터
typedef struct {
    char name[50];
    JobType job;
    int level;
    int exp;
    int gold;
    
    int hp;
    int maxHp;
    int mp;
    int maxMp;
    
    int attack;
    int defense;
    int magicDefense;
    
    int str;
    int dex;
    int intel;
    int luk;
    
    int statPoints;
    
    int inventory[20];
    int inventoryCount;
    
    int currentChapter;
} CharacterData;

// PlayerData는 CharacterData의 별칭
typedef CharacterData PlayerData;

// 게임 진행 데이터
typedef struct {
    int currentChapter;
    int monstersDefeated;
    int storyProgress;
    int chapterCleared[5];
    int deaths;
} GameProgress;

// 몬스터 데이터
typedef struct {
    char name[64];
    int level;
    int hp;
    int defense;
    int attack;
    int dropItemId;
} MonsterData;

// 아이템 데이터
typedef struct {
    char name[64];
    char description[128];
    int price;
    int healAmount;
} ItemData;

// 전역 변수 선언
extern CharacterData g_CurrentPlayer;
extern GameProgress g_GameProgress;

#endif