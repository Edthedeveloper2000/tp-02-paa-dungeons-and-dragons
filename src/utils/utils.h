#include "../../common.h"
#include "../types/dungeon/dungeon.h"

/**
 * @brief Exibe a matriz da caverna no terminal com formatação e cores.
 *
 * @param dungeon Ponteiro para a estrutura `Dungeon`, contendo os dados da caverna.
 * @param path Matriz de coordenadas representando o caminho percorrido.
 * @param path_length Número de células no caminho percorrido.
 */
void printDungeon(Dungeon *dungeon, int path[][2], int path_length);

/**
 * @brief Exibe o caminho percorrido pelo estudante na caverna no terminal.
 *
 * @param dungeon Ponteiro para a estrutura `Dungeon`, contendo os dados da caverna.
 * @param dp Ponteiro duplo (`Cell **`) para a matriz DP com os valores calculados.
 */
void printResultsToTerminal(Dungeon *dungeon, Cell **dp);
