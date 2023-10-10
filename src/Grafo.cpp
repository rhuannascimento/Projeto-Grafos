#include "../include/Grafo.h"

// Construtor
Grafo::Grafo(bool digrafo)
{
    this->digrafo = digrafo;
    /*this->ordem = ordem;
    this->numAresta = numAresta;
    
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
        novoNo->setProxNo(nullptr);
        return novoNo;
    }

    this->ultimoNo->setProxNo(novoNo);
    this->ultimoNo = novoNo;
    novoNo->setProxNo(nullptr);

    return novoNo;

}


void Grafo::imprimeGrafo(){

        if(this->noRaiz == nullptr){
            return;
        }
        
        No * proxNo = this->noRaiz;
        Aresta *aresta = proxNo->getPrimeiraAresta();

        while(proxNo != nullptr){
            cout<<proxNo->getIdNo()<<" - ";

            aresta = proxNo->getPrimeiraAresta();
            while (aresta != nullptr)
            {
                 cout<<aresta->getidNoDestino()<<" - ";
                 aresta = aresta->getProxAresta();
            }

            cout<<endl;
            
            proxNo = proxNo->getProxNo();
        }

}


No *Grafo::buscaNo(int no){

    if(this->noRaiz == nullptr){
        insereNo(no);
    }

    if(this->noRaiz->getIdNo() == no){
        return this->noRaiz;
    }

    No * noBusca = this->noRaiz->getProxNo();

    while(noBusca != nullptr && noBusca->getIdNo() != no){
        noBusca = noBusca->getProxNo();
    }

    return noBusca;

}


bool Grafo::insereAresta(int noOrigem, int noDestino){

    No *origem = this->buscaNo(noOrigem);
    No *destino = this->buscaNo(noDestino);

    if(origem==nullptr){
        origem = insereNo(noOrigem);
    }

    if(destino==nullptr){
        destino = insereNo(noDestino);
    }

    if(this->isDIgrafo()){
        origem->insertAresta(noDestino);
    }else{
        origem->insertAresta(noDestino);
        destino->insertAresta(noOrigem);
    }

    return true;


}