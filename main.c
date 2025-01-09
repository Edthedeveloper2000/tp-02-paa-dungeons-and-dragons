#include "src/io/fileReader/fileReader.h"
#include "src/io/fileWriter/fileWriter.h"
#include "src/dynamicProgramming/dynamicProgramming.h"
#include "src/generateRandomDungeon/generateRandomDungeon.h"
#include <time.h> 
#include "common.h"
#include "src/utils/utils.h"


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
