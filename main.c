#include "src/io/fileReader/fileReader.h"
#include "src/io/fileWriter/fileWriter.h"
#include "src/dynamicProgramming/dynamicProgramming.h"
#include "common.h"

int main() {
    char inputFile[256];
    char outputFile[256];

    printf("Enter the path for the input dungeon file: ");
    if (!fgets(inputFile, sizeof(inputFile), stdin)) {
        fprintf(stderr, "Error reading input file path.\n");
        return 1;
    }
    inputFile[strcspn(inputFile, "\n")] = '\0';

    printf("Enter the path for the output file: ");
    if (!fgets(outputFile, sizeof(outputFile), stdin)) {
        fprintf(stderr, "Error reading output file path.\n");
        return 1;
    }

    outputFile[strcspn(outputFile, "\n")] = '\0';

    Dungeon *dungeon = readDungeon(inputFile);
    if (!dungeon) {
        fprintf(stderr, "Failed to read dungeon from file: %s\n", inputFile);
        return 1;
    }

    Cell **dp = initializeDP(dungeon);

    calculateDP(dungeon, dp, dungeon->start_x, dungeon->start_y);
    fileWriter(dungeon, dp, outputFile);

    printf("Dungeon processed successfully. Results saved to: %s\n", outputFile);

    freeDP(dp, dungeon->height);
    freeDungeon(dungeon);

    return 0;
}