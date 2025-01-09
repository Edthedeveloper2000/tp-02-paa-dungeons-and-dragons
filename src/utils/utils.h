#include "../../common.h"
#include "../types/dungeon/dungeon.h"

void printDungeon(Dungeon *dungeon, int path[][2], int path_length);

void printResultsToTerminal(Dungeon *dungeon, Cell **dp);