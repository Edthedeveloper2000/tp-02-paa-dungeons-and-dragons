#include "../../common.h"
#include "../types/dungeon/dungeon.h"

#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

typedef struct {
    int health;   // Maximum health at this cell
    int from_x;   // Predecessor's x coordinate
    int from_y;   // Predecessor's y coordinate
} Cell;

Cell **initializeDP(Dungeon *dungeon);

void freeDP(Cell **dp, int height);

void calculateDP(Dungeon *dungeon, Cell **dp);

void reconstructPath(Dungeon *dungeon, Cell **dp, const char *outputFile);


#endif