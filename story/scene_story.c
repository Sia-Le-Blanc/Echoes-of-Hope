#include "scene_story.h"
#include "story_engine.h"
#include "../system/utils.h"
#include <stdio.h>
#include <string.h>

void ShowStory(int chapter, const char* part) {
    char path[128];
    
    ClearScreen();
    
    snprintf(path, sizeof(path), "data/story/chapter%d_%s.txt", chapter, part);
    
    printf("=================================================\n");
    printf("              [ Chapter %d - %s ]\n", chapter, part);
    printf("=================================================\n\n");
    
    if (!ShowStoryText(path, 50)) {
        printf("스토리를 불러올 수 없습니다.\n");
        Pause();
        return;
    }
    
    printf("\n=================================================\n");
    printf(" 계속하려면 Enter를 누르세요...\n");
    printf("=================================================\n");
    getchar();
}