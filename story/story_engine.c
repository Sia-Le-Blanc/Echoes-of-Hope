#define _POSIX_C_SOURCE 199309L
#include "story_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#define SLEEP_MS(ms) Sleep(ms)
#define KBHIT() _kbhit()
#define GETCH() _getch()
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
static int kbhit(void) {
    struct termios oldt, newt;
    int ch, oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
#define KBHIT() kbhit()
#define GETCH() getchar()
#endif

int ShowStoryText(const char* path, int delay_ms) {
    FILE* fp = fopen(path, "r");
    if (!fp) {
        printf("스토리 파일을 찾을 수 없습니다: %s\n", path);
        return 0;
    }

    int ch;
    int skipped = 0;

    while ((ch = fgetc(fp)) != EOF) {
        if (KBHIT()) {
            GETCH();
            skipped = 1;
            break;
        }
        
        putchar(ch);
        fflush(stdout);
        
        if (ch != '\n' && ch != ' ') {
            SLEEP_MS(delay_ms);
        }
    }

    if (skipped) {
        while ((ch = fgetc(fp)) != EOF) {
            putchar(ch);
        }
    }

    fclose(fp);
    printf("\n");
    return 1;
}

int ShowStoryTextInstant(const char* path) {
    FILE* fp = fopen(path, "r");
    if (!fp) {
        printf("스토리 파일을 찾을 수 없습니다: %s\n", path);
        return 0;
    }

    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);
    printf("\n");
    return 1;
}