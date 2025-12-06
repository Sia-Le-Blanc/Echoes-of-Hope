#ifndef MODEL_GAME_PROGRESS_H
#define MODEL_GAME_PROGRESS_H

typedef enum {
    DIFFICULTY_EASY = 1,
    DIFFICULTY_NORMAL,
    DIFFICULTY_HARD
} Difficulty;

typedef struct {
    int currentChapter;        // 1~5
    int storyProgress;         // 0~10 (챕터 내 스토리 진행도)
    int monstersDefeated;      // 현재 던전에서 처치한 일반 몬스터
    int chapterCleared[5];     // 각 챕터 클리어 여부
    Difficulty difficulty;     // 난이도
    int totalPlayTime;         // 초 단위
    int deaths;                // 사망 횟수
} GameProgress;

#endif