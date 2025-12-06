#ifndef MODEL_MONSTER_H
#define MODEL_MONSTER_H

// 몬스터 데이터 구조 (저장/로드용)
typedef struct {
    int id;             // 몬스터 고유 번호 (파일 구분용)
    char name[32];      // 몬스터 이름
    int level;
    int hp;             // 체력
    int attack;         // 공격력
    int defense;        // 방어력
    int dropItemId;     // 드랍 아이템 ID (장비 or 일반 아이템과 연결)
} MonsterData;

#endif