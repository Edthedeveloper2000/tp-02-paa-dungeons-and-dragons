#include "../../../common.h"
#include "../../types/dungeon/dungeon.h"
#include "../../dynamicProgramming/dynamicProgramming.h"

#ifndef FILE_WRITER_H
#define FILE_WRITER_H


/**
 * @brief Escreve o caminho calculado na matriz DP em um arquivo de saída.
 *
 * @param dungeon Ponteiro para a estrutura `Dungeon` com os dados da caverna.
 * @param dp Ponteiro duplo (`Cell **`) para a matriz DP com os valores calculados.
 * @param outputFile Caminho do arquivo onde o resultado será salvo.
 */
void fileWriter(Dungeon *dungeon, Cell **dp, const char *outputFile);


#endif