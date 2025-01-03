#include "fileReader.h"

Dungeon *readDungeon(char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filePath);
        return NULL;
    }

    // Allocate memory for the dungeon structure
    Dungeon *dungeon = malloc(sizeof(Dungeon));
    if (!dungeon) {
        fprintf(stderr, "Error allocating memory for the dungeon.\n");
        fclose(file);
        return NULL;
    }

    // Read dimensions and initial health points
    fscanf(file, "%d %d %d", &dungeon->width, &dungeon->height, &dungeon->initial_health);

    // Allocate memory for the grid
    dungeon->grid = malloc(dungeon->width * sizeof(int *));
    for (int i = 0; i < dungeon->width; i++) {
        dungeon->grid[i] = malloc(dungeon->height * sizeof(int));
    }

    // Initialize start and end points as invalid
    dungeon->start_x = dungeon->start_y = -1;
    dungeon->end_x = dungeon->end_y = -1;

    // Read the grid values
    for (int i = 0; i < dungeon->width; i++) {
        for (int j = 0; j < dungeon->height; j++) {
            char buffer[10];
            fscanf(file, "%s", buffer);

            if (strcmp(buffer, "I") == 0) {
                dungeon->start_x = i;
                dungeon->start_y = j;
                dungeon->grid[i][j] = 0; // Set to zero to avoid affecting calculations
            } else if (strcmp(buffer, "F") == 0) {
                dungeon->end_x = i;
                dungeon->end_y = j;
                dungeon->grid[i][j] = 0; // Set to zero to avoid affecting calculations
            } else {
                dungeon->grid[i][j] = atoi(buffer); // Convert the value to an integer
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
