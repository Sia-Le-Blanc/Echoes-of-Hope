#include "chapter_data.h"

// 챕터별 일반 몬스터 (최대 7종)
const char* CHAPTER_MONSTERS[4][7] = {
    // 챕터1: 5종
    {"ch1_hunter", "ch1_hound", "ch1_soul", "ch1_vine", "ch1_marauder", 0, 0},
    // 챕터2: 5종
    {"ch2_villager", "ch2_fanatic", "ch2_sentinel", "ch2_thief", "ch2_phantom", 0, 0},
    // 챕터3: 5종
    {"ch3_steel", "ch3_mage", "ch3_wanderer", "ch3_golem", "ch3_archer", 0, 0},
    // 챕터4: 7종
    {"ch4_swarm", "ch4_legion_archer", "ch4_legion_charger", "ch4_legion_mage", 
     "ch4_phantom", "ch4_guardian", "ch4_predator"}
};

// 챕터별 보스
const char* CHAPTER_BOSSES[5] = {
    "ch1_boss_ervin",      // 에르빈
    "ch2_boss_isabel",     // 이자벨
    "ch3_boss_septimus",   // 셉티무스
    "ch4_boss_shell",      // 껍데기 기사
    "ch5_boss_acheron"     // 아케론 (최종보스)
};

// 챕터별 스토리 파트 (순서대로 출력)
const char* CHAPTER1_STORIES[6] = {
    "intro", "village", "rumor", "expedition", "forest", "boss"
};

const char* CHAPTER2_STORIES[5] = {
    "intro", "journey", "attack", "border", "church"
};

const char* CHAPTER3_STORIES[6] = {
    "intro", "sewer", "note", "mage", "palace", "boss"
};

const char* CHAPTER4_STORIES[3] = {
    "intro", "swarm", "ending"
};

// 챕터별 일반 몬스터 종류 수
const int CHAPTER_MONSTER_COUNTS[4] = {5, 5, 5, 7};