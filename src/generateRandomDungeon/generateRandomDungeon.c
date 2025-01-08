#include "generateRandomDungeon.h"
#include "../../common.h"

Dungeon *generateRandomDungeon(int height, int width, int initial_health) {
    Dungeon *dungeon = malloc(sizeof(Dungeon));
    if (!dungeon) {
        fprintf(stderr, "Erro ao alocar memória para a caverna.\n");
        return NULL;
    }

    dungeon->height = height;
    dungeon->width = width;
    dungeon->initial_health = initial_health;

    dungeon->grid = malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++) {
        dungeon->grid[i] = malloc(width * sizeof(int));
        for (int j = 0; j < width; j++) {
            int values[] = {0, -10, -20, 20};
            dungeon->grid[i][j] = values[rand() % 4];
        }
    }

    dungeon->start_x = rand() % height;
    dungeon->start_y = rand() % width;

    do {
        dungeon->end_x = rand() % height;
        dungeon->end_y = rand() % width;
    } while (dungeon->end_x == dungeon->start_x && dungeon->end_y == dungeon->start_y);

    dungeon->grid[dungeon->start_x][dungeon->start_y] = -1; // I
    dungeon->grid[dungeon->end_x][dungeon->end_y] = -1;    // F

    printf("\nCaverna Gerada Aleatoriamente:\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == dungeon->start_x && j == dungeon->start_y) {
                printf("[I]");
            } else if (i == dungeon->end_x && j == dungeon->end_y) {
                printf("[F]");
            } else {
                if (dungeon->grid[i][j] >= 0) {
                    printf("[+%d]", dungeon->grid[i][j]);
                } else {
                    printf("[%d]", dungeon->grid[i][j]);
                }
            }
        }
        printf("\n");
    }

    return dungeon;
}