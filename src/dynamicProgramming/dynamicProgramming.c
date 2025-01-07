#include "dynamicProgramming.h"

Cell **initializeDP(Dungeon *dungeon) {
    Cell **dp = malloc(dungeon->height * sizeof(Cell *));
    for (int i = 0; i < dungeon->height; i++) {
        dp[i] = malloc(dungeon->width * sizeof(Cell));
        for (int j = 0; j < dungeon->width; j++) {
            if(dungeon->grid[i][j] == 0) {
                dp[i][j].health = 0;
            } else {
                dp[i][j].health = INT_MIN;
            }
        }
    }
    dp[dungeon->start_x][dungeon->start_y].health = dungeon->initial_health;
    return dp;
}


void freeDP(Cell **dp, int height) {
    for (int i = 0; i < height; i++) {
        free(dp[i]);
    }
    free(dp);
}

void calculateDP(Dungeon *dungeon, Cell **dp, int i, int j) {
    if(i != dungeon->start_x || j != dungeon->start_y) {
        if( i + 1 == dungeon->height  && j + 1 < dungeon->width) {
            dp[i][j].health = dp[i][j + 1].health + dungeon->grid[i][j];
            dp[i][j].from_x = i;
            dp[i][j].from_y = j + 1;

        } else if(i + 1 < dungeon->height  && j + 1 == dungeon->width) {
            dp[i][j].health = dp[i + 1][j].health + dungeon->grid[i][j];
            dp[i][j].from_x = i + 1;
            dp[i][j].from_y = j;

        } else if(i + 1 < dungeon->height  && j + 1 < dungeon->width) {
            if(dp[i][j+1].health == INT_MIN) return;

            if(dp[i + 1][j].health > dp[i][j+1].health) {
                dp[i][j].health = dp[i + 1][j].health + dungeon->grid[i][j];
                dp[i][j].from_x = i + 1;
                dp[i][j].from_y = j;
            } else {
                dp[i][j].health = dp[i][j + 1].health + dungeon->grid[i][j];
                dp[i][j].from_x = i;
                dp[i][j].from_y = j + 1;
            }
        }
    }
    
    if(j > 0) calculateDP(dungeon, dp, i, j - 1);

    if(i > 0) calculateDP(dungeon, dp, i - 1, j);
}


void reconstructPath(Dungeon *dungeon, Cell **dp, const char *outputFile) {
    FILE *output = fopen(outputFile, "w");
    if (!output) {
        fprintf(stderr, "Error opening output file: %s\n", outputFile);
        return;
    }
    if (dp[dungeon->end_x][dungeon->end_y].health < 0) {
        fprintf(output, "impossível\n");
        fclose(output);
        return;
    }
    // Reconstruct the path
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

    // Write the path to the output file
    for (int i = path_length; i >= 0; i--) {
        fprintf(output, "%d %d\n", path[i][0], path[i][1]);
    }

    fclose(output);
}
