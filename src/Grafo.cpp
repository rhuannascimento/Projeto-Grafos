#include "../include/Grafo.h"

// Construtor
Grafo::Grafo(int ordem = 0)
{
    this->ordem = ordem;
    /*this->numAresta = numAresta;
    this->digrafo = digrafo;
    this->weigthNo = weigthNo;
    this->weightArc = weightArc;*/
}

// Destrutor
Grafo::~Grafo()
{
    // Faça qualquer limpeza de memória necessária aqui, se aplicável
}

// Função para incrementar a ordem
