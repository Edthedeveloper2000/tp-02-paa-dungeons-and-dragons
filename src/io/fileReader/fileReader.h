#include "../../../common.h"
#include "../../types/dungeon/dungeon.h"

#ifndef FILE_READER_H
#define FILE_READER_H


Dungeon *readDungeon(char *path);

void freeDungeon(Dungeon *dungeon);

#endif