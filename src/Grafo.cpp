#include "../include/Grafo.h"

// Construtor
Grafo::Grafo()
{
    /*this->ordem = ordem;
    this->numAresta = numAresta;
    this->digrafo = digrafo;
    this->weigthNo = weigthNo;
    this->weightArc = weightArc;*/
}

// Destrutor
Grafo::~Grafo()
{
    // Faça qualquer limpeza de memória necessária aqui, se aplicável
}

No * Grafo::insereNo(int idNo){


    No *novoNo = new No(idNo);

    if(this->noRaiz == nullptr){
        this->noRaiz = novoNo;
        this->ultimoNo = novoNo;
        return novoNo;
    }

    this->ultimoNo->setProxNo(novoNo);
    this->ultimoNo = novoNo;
    this->ultimoNo->setProxNo(nullptr);

    return novoNo;

}



