/**
 * @file Aresta.cpp
 * @brief Este arquivo contém a implementação das funções da classe Aresta.
 */

#include "../include/Aresta.h"

/**
 * @brief Construtor da classe Aresta, que inicializa uma aresta sem peso.
 * @param idNoDestino O ID do nó de destino da aresta.
 */
Aresta::Aresta(int idNoDestino) {
    this->idNoDestino = idNoDestino;
}

/**
 * @brief Construtor da classe Aresta, que inicializa uma aresta com peso.
 * @param idNoDestino O ID do nó de destino da aresta.
 * @param pesoAresta O peso da aresta.
 */
Aresta::Aresta(int idNoDestino, int pesoAresta) {
    this->idNoDestino = idNoDestino;
    this->pesoAresta = pesoAresta;
}

/**
 * @brief Define a próxima aresta na lista de adjacência.
 * @param aresta Ponteiro para a próxima aresta.
 */
void Aresta::setProxAresta(Aresta *aresta) {
    this->proxAresta = aresta;
}

/**
 * @brief Obtém o peso da aresta.
 * @return O peso da aresta.
 */
int Aresta::getPesoAresta() {
    return this->pesoAresta;
}
