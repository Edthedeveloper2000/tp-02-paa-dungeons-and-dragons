#include "../../common.h"
#include "../types/dungeon/dungeon.h"

#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

typedef struct {
    int health;  
    int from_x;   
    int from_y;   
} Cell;

Cell **initializeDP(Dungeon *dungeon);

void freeDP(Cell **dp, int height);

void calculateDP(Dungeon *dungeon, Cell **dp, int i, int j);


#endif