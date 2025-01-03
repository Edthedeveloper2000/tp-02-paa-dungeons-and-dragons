#include "dynamicProgramming.h"

#include "../../common.h"
#include <limits.h>
#include "../io/fileReader/fileReader.h"

Cell **initializeDP(Dungeon *dungeon) {
    Cell **dp = malloc(dungeon->height * sizeof(Cell *));
    for (int i = 0; i < dungeon->height; i++) {
        dp[i] = malloc(dungeon->width * sizeof(Cell));
        for (int j = 0; j < dungeon->width; j++) {
            dp[i][j].health = INT_MIN; // Start with unreachable state
            dp[i][j].from_x = -1;
            dp[i][j].from_y = -1;
        }
    }
    return dp;
}

void freeDP(Cell **dp, int height) {
    for (int i = 0; i < height; i++) {
        free(dp[i]);
    }
    free(dp);
}

void calculateDP(Dungeon *dungeon, Cell **dp) {
    // Initialize starting position
    dp[dungeon->start_x][dungeon->start_y].health = dungeon->initial_health;

    // Iterate through the dungeon grid
    for (int i = 0; i < dungeon->height; i++) {
        for (int j = 0; j < dungeon->width; j++) {
            if (dp[i][j].health <= 0) continue; // Skip unreachable cells

            int current_value = dungeon->grid[i][j];

            // Update cell below (i+1, j)
            if (i + 1 < dungeon->height && dungeon->grid[i + 1][j] != '0') {
                int new_health = dp[i][j].health + current_value;
                if (new_health > dp[i + 1][j].health) {
                    dp[i + 1][j].health = new_health;
                    dp[i + 1][j].from_x = i;
                    dp[i + 1][j].from_y = j;
                }
            }

            // Update cell to the right (i, j+1)
            if (j + 1 < dungeon->width && dungeon->grid[i][j + 1] != '0') {
                int new_health = dp[i][j].health + current_value;
                if (new_health > dp[i][j + 1].health) {
                    dp[i][j + 1].health = new_health;
                    dp[i][j + 1].from_x = i;
                    dp[i][j + 1].from_y = j;
                }
            }
        }
    }
}

void reconstructPath(Dungeon *dungeon, Cell **dp, const char *outputFile) {
    FILE *output = fopen(outputFile, "w");
    if (!output) {
        fprintf(stderr, "Error opening output file: %s\n", outputFile);
        return;
    }

    int x = dungeon->end_x;
    int y = dungeon->end_y;

    if (dp[x][y].health <= 0) {
        fprintf(output, "impossível\n");
        fclose(output);
        return;
    }

    // Reconstruct the path
    int path[dungeon->height * dungeon->width][2];
    int path_length = 0;

    while (x != -1 && y != -1) {
        path[path_length][0] = x;
        path[path_length][1] = y;
        path_length++;
        int next_x = dp[x][y].from_x;
        int next_y = dp[x][y].from_y;
        x = next_x;
        y = next_y;
    }

    // Write the path to the output file
    for (int i = path_length - 1; i >= 0; i--) {
        fprintf(output, "%d %d\n", path[i][0], path[i][1]);
    }

    fclose(output);
}
