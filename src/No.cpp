#include "../include/No.h"

No::No(int idNo){
    this->idNo = idNo;
}


void No::setProxNo(No *no){
    this->proxNo = no;
}

No * No::getProxNo(){
    return this->proxNo;
}

Aresta * No::insertAresta(int destino){
    Aresta *novaAresta = new Aresta(destino);

    if(this->primeiraAresta == nullptr){
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


Aresta * No::insertArestaPonderada(int destino, int peso){
    Aresta *novaAresta = new Aresta(destino, peso);

    if(this->primeiraAresta == nullptr){
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