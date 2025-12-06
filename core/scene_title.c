#include <stdio.h>
#include "scene_title.h"
#include "../system/utils.h"

void ShowTitle() {
    ClearScreen();

    printf("┌───────────────────────────────────────────────────────────────────────┐\n");
    printf("│                                                                       │\n");
    printf("│          ███████╗ ███████╗██╗  ██╗ ██████╗ ███████╗                   │\n");
    printf("│          ██╔════╝ ██╔════╝██║  ██║██╔════╝ ██╔════╝                   │\n");
    printf("│          ███████╗ █████╗  ███████║██║  ███╗█████╗                     │\n");
    printf("│          ╚════██║ ██╔══╝  ██╔══██║██║   ██║██╔══╝                     │\n");
    printf("│          ███████║ ███████╗██║  ██║╚██████╔╝███████╗                   │\n");
    printf("│          ╚══════╝ ╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝                   │\n");
    printf("│                                                                       │\n");
    printf("│                  E C H O E S   O F   V A L O R                        │\n");
    printf("│                                                                       │\n");
    printf("│          \"In the silence of the past, courage still echoes...\"        │\n");
    printf("│                                                                       │\n");
    printf("│                   Press  [ Enter ]  to continue...                    │\n");
    printf("│                                                                       │\n");
    printf("│                            v1.0 (Test)                                │\n");
    printf("│               Team: 1000110101  |  Build: 2025-12-07                  │\n");
    printf("└───────────────────────────────────────────────────────────────────────┘\n");

    getchar();
}