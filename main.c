#include "src/io/fileReader/fileReader.h"
#include "src/io/fileWriter/fileWriter.h"
#include "src/dynamicProgramming/dynamicProgramming.h"
#include "common.h"

int main() {
    char inputFile[256];
    char outputFile[256];

    // Prompt the user for the input file path
    printf("Enter the path for the input dungeon file: ");
    if (!fgets(inputFile, sizeof(inputFile), stdin)) {
        fprintf(stderr, "Error reading input file path.\n");
        return 1;
    }
    // Remove trailing newline character if present
    inputFile[strcspn(inputFile, "\n")] = '\0';

    // Prompt the user for the output file path
    printf("Enter the path for the output file: ");
    if (!fgets(outputFile, sizeof(outputFile), stdin)) {
        fprintf(stderr, "Error reading output file path.\n");
        return 1;
    }
    // Remove trailing newline character if present
    outputFile[strcspn(outputFile, "\n")] = '\0';

    // Read the dungeon from the input file
    Dungeon *dungeon = readDungeon(inputFile);
    if (!dungeon) {
        fprintf(stderr, "Failed to read dungeon from file: %s\n", inputFile);
        return 1;
    }

    // Initialize the DP matrix
    Cell **dp = initializeDP(dungeon);

    // Calculate the DP values and reconstruct the path
    calculateDP(dungeon, dp);
    reconstructPath(dungeon, dp, outputFile);

    printf("Dungeon processed successfully. Results saved to: %s\n", outputFile);

    // Free allocated memory
    freeDP(dp, dungeon->height);
    freeDungeon(dungeon);

    return 0;
}