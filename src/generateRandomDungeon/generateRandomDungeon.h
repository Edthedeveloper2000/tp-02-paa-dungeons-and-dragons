#include "../types/dungeon/dungeon.h"
#include "../utils/utils.h"

/**
 * @brief Gera uma caverna aleatória com posições inicial e final definidas.
 *
 * @param height Número de linhas da caverna.
 * @param width Número de colunas da caverna.
 * @param initial_health Pontos de vida iniciais do estudante.
 * @return Ponteiro para a estrutura `Dungeon` representando a caverna gerada.
 */
Dungeon *generateRandomDungeon(int height, int width, int initial_health);