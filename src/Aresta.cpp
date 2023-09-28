#include "../include/Aresta.h"

Aresta::Aresta(int idNoDestino){
    this->idNoDestino = idNoDestino;
}


Aresta::Aresta(int idNoDestino, int pesoAresta){
    this->idNoDestino = idNoDestino;
    this->pesoAresta = pesoAresta;
}

void Aresta::setProxAresta(Aresta *aresta){
    this->proxAresta = aresta;
}

int Aresta::getPesoAresta(){
    return this->pesoAresta;
}