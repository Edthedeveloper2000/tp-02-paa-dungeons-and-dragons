#include "../../../common.h"
#include "../../types/dungeon/dungeon.h"
#include "../../dynamicProgramming/dynamicProgramming.h"

#ifndef FILE_WRITER_H
#define FILE_WRITER_H


void fileWriter(Dungeon *dungeon, Cell **dp, const char *outputFile);

#endif