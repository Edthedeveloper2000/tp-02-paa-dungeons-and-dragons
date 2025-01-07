#include "fileReader.h"

Dungeon *readDungeon(char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filePath);
        return NULL;
    }

    Dungeon *dungeon = malloc(sizeof(Dungeon));
    if (!dungeon) {
        fprintf(stderr, "Error allocating memory for the dungeon.\n");
        fclose(file);
        return NULL;
    }

    fscanf(file, "%d %d %d", &dungeon->height, &dungeon->width, &dungeon->initial_health);

    dungeon->grid = malloc(dungeon->height * sizeof(int *));
    for (int i = 0; i < dungeon->height; i++) {
        dungeon->grid[i] = malloc(dungeon->width * sizeof(int));
    }

  
    dungeon->start_x = dungeon->start_y = -1;
    dungeon->end_x = dungeon->end_y = -1;

    for (int i = 0; i < dungeon->height; i++) {
        for (int j = 0; j < dungeon->width; j++) {
            char buffer[10];
            fscanf(file, "%s", buffer);

            if (strcmp(buffer, "I") == 0) {
                dungeon->start_x = i;
                dungeon->start_y = j;
                dungeon->grid[i][j] = -1; 
            } else if (strcmp(buffer, "F") == 0) {
                dungeon->end_x = i;
                dungeon->end_y = j;
                dungeon->grid[i][j] = -1; 
            } else {
                dungeon->grid[i][j] = atoi(buffer); 
            }
        }
    }

    fclose(file);
    return dungeon;
}

void freeDungeon(Dungeon *dungeon) {
    if (!dungeon) return;

    for (int i = 0; i < dungeon->height; i++) {
        free(dungeon->grid[i]);
    }
    free(dungeon->grid);
    free(dungeon);
}
