#ifndef MODEL_CHARACTER_H
#define MODEL_CHARACTER_H

// 직업 정의
typedef enum {
    JOB_WARRIOR = 1,   // 전사
    JOB_MAGE = 2,      // 마법사
    JOB_ARCHER = 3     // 궁수
} JobType;


// 저장/로드되는 캐릭터 데이터 구조
typedef struct {
    char name[32];        // 플레이어 이름
    JobType job;          // 직업 (1: 전사, 2: 마법사, 3: 궁수)

    int level;            // 레벨
    int exp;              // 경험치
    int gold;             // 골드

    int hp;               // 현재 HP
    int maxHp;            // 최대 HP
    int mp;               // 현재 MP
    int maxMp;            // 최대 MP

    int attack;           // 기본 공격력
    int defense;          // 기본 방어력

    // 추가 스탯
    int str;              // 힘 (공격력, HP)
    int dex;              // 민첩 (회피율, 방어력)
    int intel;            // 지능 (마법 공격, 마법 방어)
    int luk;              // 행운 (치명타율, 드랍률)
    
    int statPoints;       // 사용 가능한 스탯 포인트

    // 장비 슬롯 (장비 id 저장)
    int weaponId;
    int helmetId;
    int armorId;
    int pantsId;
    int glovesId;
    int bootsId;

    // 인벤토리: 최대 20개 (아이템 ID만 저장)
    int inventory[20];
    int inventoryCount;

} CharacterData;

#endif