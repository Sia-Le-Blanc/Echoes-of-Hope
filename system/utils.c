#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Pause() {
    printf("\n계속하려면 Enter를 누르세요...");
    getchar();
}