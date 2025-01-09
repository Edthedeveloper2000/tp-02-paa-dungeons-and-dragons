#include "../../common.h"
#include "../types/dungeon/dungeon.h"

#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

Cell **initializeDP(Dungeon *dungeon);

void freeDP(Cell **dp, int height);

void calculateDP(Dungeon *dungeon, Cell **dp, int i, int j);


#endif