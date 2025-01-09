#include "../../../common.h"
#include "../../types/dungeon/dungeon.h"

#ifndef FILE_READER_H
#define FILE_READER_H


/**
 * @brief Lê os dados de uma caverna a partir de um arquivo.
 *
 * @param filePath Caminho do arquivo de entrada.
 * @return Ponteiro para a estrutura `Dungeon` representando a caverna lida.
 *         Retorna `NULL` em caso de erro na leitura ou alocação.
 */
Dungeon *readDungeon(char *filePath);

/**
 * @brief Libera a memória alocada para uma estrutura `Dungeon`.
 *
 * @param dungeon Ponteiro para a estrutura `Dungeon` a ser liberada.
 */
void freeDungeon(Dungeon *dungeon);


#endif