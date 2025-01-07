#include "fileWriter.h"


void fileWriter(Dungeon *dungeon, Cell **dp, const char *outputFile) {
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

    for (int i = path_length; i >= 0; i--) {
        fprintf(output, "%d %d\n", path[i][0], path[i][1]);
    }

    fclose(output);
}