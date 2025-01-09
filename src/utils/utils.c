#include "utils.h"

void printDungeon(Dungeon *dungeon, int path[][2], int path_length) {
    printf("\nCaverna:\n");
    for (int i = 0; i < dungeon->height; i++) {
        for (int j = 0; j < dungeon->width; j++) {
            int isPath = 0;

            // Verificar se a célula faz parte do caminho
            for (int k = 0; k < path_length; k++) {
                if (path[k][0] == i && path[k][1] == j) {
                    isPath = 1;
                    break;
                }
            }

            if (isPath) {
                printf(BLUE "[ E ]" RESET " "); // Azul para células percorridas
            } else if (i == dungeon->start_x && j == dungeon->start_y) {
                printf(BLUE "[ I ]" RESET " "); // Azul para posição inicial
            } else if (i == dungeon->end_x && j == dungeon->end_y) {
                printf(YELLOW "[ F ]" RESET " "); // Amarelo para posição final
            } else if (dungeon->grid[i][j] == 20) {
                printf(GREEN "[+20]" RESET " "); // Verde para +20
            } else if (dungeon->grid[i][j] == -20) {
                printf(RED "[-20]" RESET " "); // Vermelho para -20
            } else if (dungeon->grid[i][j] == -10) {
                printf(YELLOW "[-10]" RESET " "); // Amarelo para -10
            } else {
                printf(WHITE "[ 0 ]" RESET " "); // Branco para 0
            }
        }
        printf("\n");
    }
}

void printResultsToTerminal(Dungeon *dungeon, Cell **dp) {
    if (dp[dungeon->end_x][dungeon->end_y].health < 0) {
        printf("impossível\n");
        return;
    }

    int path[dungeon->height * dungeon->width][2];
    int path_length = 0;

    int x = dungeon->end_x;
    int y = dungeon->end_y;

    path[path_length][0] = x;
    path[path_length][1] = y;
    while (x != dungeon->start_x || y != dungeon->start_y) {
        path_length++;
        int next_x = dp[x][y].from_x;
        int next_y = dp[x][y].from_y;
        x = next_x;
        y = next_y;
        path[path_length][0] = x;
        path[path_length][1] = y;
    }

    printf("\nCaminho percorrido (marcado como [E]):\n");
    printDungeon(dungeon, path, path_length + 1);
}
