#include "../../common.h"
#include "../types/dungeon/dungeon.h"

#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

/**
 * @brief Inicializa a matriz de programação dinâmica (DP).
 * 
 * @param dungeon Ponteiro para a estrutura `Dungeon`, contendo os dados da caverna.
 * @return Ponteiro duplo (`Cell **`) para a matriz DP inicializada.
 */
Cell **initializeDP(Dungeon *dungeon);

/**
 * @brief Libera a memória alocada para a matriz DP.
 * 
 * @param dp Ponteiro duplo (`Cell **`) para a matriz DP.
 * @param height Número de linhas da matriz DP.
 */
void freeDP(Cell **dp, int height);


/**
 * @brief Calcula a matriz de programação dinâmica (DP) para encontrar o melhor caminho.
 * 
 * @param dungeon Ponteiro para a estrutura `Dungeon`, contendo os dados da caverna.
 * @param dp Ponteiro duplo (`Cell **`) para a matriz DP.
 * @param i Índice da linha atual.
 * @param j Índice da coluna atual.
 */
void calculateDP(Dungeon *dungeon, Cell **dp, int i, int j);


#endif