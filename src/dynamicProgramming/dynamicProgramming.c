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