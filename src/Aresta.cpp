#include "../include/Aresta.h"

Aresta::Aresta(int idNoDestino){
    this->idNoDestino = idNoDestino;
}


Aresta::Aresta(int noDestino, int pesoAresta){
    this->idNoDestino = idNoDestino;
    this->pesoAresta = pesoAresta;
}

void Aresta::setProxAresta(Aresta *aresta){
    this->proxAresta = aresta;
}