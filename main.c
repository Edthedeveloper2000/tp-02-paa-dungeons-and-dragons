#include "src/io/fileReader/fileReader.h"
#include "src/io/fileWriter/fileWriter.h"
#include "common.h"


int main() {
    char filePath[256];

    printf("Enter the path to the dungeon file: ");
    scanf("%255s", filePath);

    Dungeon *dungeon = readDungeon(filePath);
    if (!dungeon) {
        return 1;
    }

    printf("Dungeon successfully read!\nDimensions: %d x %d\nInitial Health: %d\n",
           dungeon->width, dungeon->height, dungeon->initial_health);

    printf("Start Point: (%d, %d)\n", dungeon->start_x, dungeon->start_y);
    printf("End Point: (%d, %d)\n", dungeon->end_x, dungeon->end_y);

    freeDungeon(dungeon);
    return 0;
}