#include "src/io/fileReader/fileReader.h"
#include "src/io/fileWriter/fileWriter.h"
#include "src/dynamicProgramming/dynamicProgramming.h"
#include "src/generateRandomDungeon/generateRandomDungeon.h"
#include <time.h> 
#include "common.h"


int main() {
    int cavernaOption, outputOption;
    Dungeon *dungeon = NULL;

    srand(time(NULL));

    printf("Bem-vindo ao Dungeon Solver!\n");

    printf("\nEscolha como obter a caverna:\n");
    printf("1. Carregar caverna de um arquivo\n");
    printf("2. Gerar uma caverna aleatória\n");
    printf("Opção: ");
    scanf("%d", &cavernaOption);

    if (cavernaOption == 1) {
        char inputFile[256];
        printf("Digite o caminho para o arquivo da caverna: ");
        scanf("%s", inputFile);

        dungeon = readDungeon(inputFile);
        if (!dungeon) {
            fprintf(stderr, "Erro ao carregar a caverna do arquivo.\n");
            return 1;
        }
    } else if (cavernaOption == 2) {
        int height, width, initial_health;
        printf("Digite a altura, largura e pontos de vida iniciais da caverna: ");
        scanf("%d %d %d", &height, &width, &initial_health);

        dungeon = generateRandomDungeon(height, width, initial_health);
        if (!dungeon) {
            fprintf(stderr, "Erro ao gerar a caverna aleatória.\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Opção inválida para a caverna.\n");
        return 1;
    }

    printf("\nEscolha como exibir os resultados:\n");
    printf("1. Salvar os resultados em um arquivo\n");
    printf("2. Exibir os resultados no terminal\n");
    printf("Opção: ");
    scanf("%d", &outputOption);

    Cell **dp = initializeDP(dungeon);
    calculateDP(dungeon, dp, dungeon->start_x, dungeon->start_y);

    if (outputOption == 1) {
        char outputFile[256];
        printf("Digite o caminho para o arquivo de saída: ");
        scanf("%s", outputFile);

        fileWriter(dungeon, dp, outputFile);
        printf("Resultados salvos em: %s\n", outputFile);
    } else if (outputOption == 2) {
        printResultsToTerminal(dungeon, dp);
    } else {
        fprintf(stderr, "Opção inválida para os resultados.\n");
        freeDP(dp, dungeon->height);
        freeDungeon(dungeon);
        return 1;
    }

    freeDP(dp, dungeon->height);
    freeDungeon(dungeon);

    return 0;
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



void printDungeon(Dungeon *dungeon, int path[][2], int path_length) {
    printf("\nCaverna:\n");
    for (int i = 0; i < dungeon->height; i++) {
        for (int j = 0; j < dungeon->width; j++) {
            int isPath = 0;

            for (int k = 0; k < path_length; k++) {
                if (path[k][0] == i && path[k][1] == j) {
                    isPath = 1;
                    break;
                }
            }

            if (isPath) {
                printf("\033[1;34m[E]\033[0m ");
            } else if (i == dungeon->start_x && j == dungeon->start_y) {
                printf("\033[1;34m[I]\033[0m ");
            } else if (i == dungeon->end_x && j == dungeon->end_y) {
                printf("\033[1;93m[F]\033[0m ");
            } else if (dungeon->grid[i][j] == 20) {
                printf("\033[1;32m[+20]\033[0m ");
            } else if (dungeon->grid[i][j] == -20) {
                printf("\033[1;31m[-20]\033[0m ");
            } else if (dungeon->grid[i][j] == -10) {
                printf("\033[1;33m[-10]\033[0m ");
            } else {
                printf("[0] ");
            }
        }
        printf("\n");
    }
}
