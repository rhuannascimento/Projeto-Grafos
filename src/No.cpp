/**
 * @file No.cpp
 * @brief Este arquivo contém a implementação das funções da classe No.
 */

#include "../include/No.h"

/**
 * @brief Construtor da classe No.
 * @param idNo O ID do nó.
 */
No::No(int idNo) {
    this->idNo = idNo;
    this->primeiraAresta = nullptr;
    this->ultimaAresta = nullptr;
    this->proxNo = nullptr;
}

/**
 * @brief Obtém o ID do nó.
 * @return O ID do nó.
 */
int No::getIdNo() {
    return idNo;
}

/**
 * @brief Define o próximo nó na lista de nós.
 * @param no Um ponteiro para o próximo nó.
 */
void No::setProxNo(No* no) {
    this->proxNo = no;
}

/**
 * @brief Obtém o próximo nó na lista de nós.
 * @return Um ponteiro para o próximo nó.
 */
No* No::getProxNo() {
    return this->proxNo;
}

/**
 * @brief Insere uma nova aresta no nó.
 * @param destino O ID do nó de destino da aresta.
 * @return Um ponteiro para a aresta recém-inserida.
 */
Aresta* No::insertAresta(int destino) {
    Aresta* novaAresta = new Aresta(destino);

    if (this->primeiraAresta == nullptr) {
        this->primeiraAresta = novaAresta;
        this->ultimaAresta = novaAresta;
        novaAresta->setProxAresta(nullptr);
        return novaAresta;
    }

    this->ultimaAresta->setProxAresta(novaAresta);
    this->ultimaAresta = novaAresta;
    novaAresta->setProxAresta(nullptr);

    return novaAresta;
}

/**
 * @brief Insere uma nova aresta ponderada no nó.
 * @param destino O ID do nó de destino da aresta.
 * @param peso O peso da aresta.
 * @return Um ponteiro para a aresta recém-inserida.
 */
Aresta* No::insertAresta(int destino, int peso) {
    Aresta* novaAresta = new Aresta(destino, peso);

    if (this->primeiraAresta == nullptr) {
        this->primeiraAresta = novaAresta;
        this->ultimaAresta = novaAresta;
        novaAresta->setProxAresta(nullptr);
        return novaAresta;
    }

    this->ultimaAresta->setProxAresta(novaAresta);
    this->ultimaAresta = novaAresta;
    novaAresta->setProxAresta(nullptr);

    return novaAresta;
}
