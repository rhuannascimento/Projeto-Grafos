#include "../include/Grafo.h"
#include "../include/Aresta.h"


// Construtor
Grafo::Grafo(bool digrafo, bool ponderado, int ordem)
{
    this->digrafo = digrafo;
    this->ponderado = ponderado;
    this->ordem = ordem;
    /*
    this->numAresta = numAresta;
    this->weigthNo = weigthNo;
    this->weightArc = weightArc;
    */
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

            cout << "|" << proxNo->getIdNo()<<"| => ";

            aresta = proxNo->getPrimeiraAresta();
            while (aresta != nullptr)
            {
                if(this->ponderado){
                    cout << aresta->getIdNoDestino() << " (p:" << aresta->getPesoAresta() << ") => ";
                    aresta = aresta->getProxAresta();
                }else{
                    cout<< aresta->getIdNoDestino()<<" => ";
                    aresta = aresta->getProxAresta();
                }
                 
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

bool Grafo::insereAresta(int noOrigem, int noDestino, int peso){

    No *origem = this->buscaNo(noOrigem);
    No *destino = this->buscaNo(noDestino);

    if(origem==nullptr){
        origem = insereNo(noOrigem);
    }

    if(destino==nullptr){
        destino = insereNo(noDestino);
    }

    if(this->isDIgrafo()){
        origem->insertAresta(noDestino, peso);
    }else{
        origem->insertAresta(noDestino, peso);
        destino->insertAresta(noOrigem, peso);
    }

    return true;


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

void Grafo::fechoTransitivoDireto(int idNo) {
    No* noOrigem = buscaNo(idNo);

    if (noOrigem == nullptr) {
        cout << "Nó de origem não encontrado." << endl;
        return;
    }

    // Usando uma pilha para a busca em profundidade
    stack<No*> pilha;
    pilha.push(noOrigem);

    // Vetor para marcar nós visitados
    vector<bool> visitados(ordem, false);

    cout << "Fecho Transitivo Direto do nó " << idNo << ": ";

    while (!pilha.empty()) {
        No* noAtual = pilha.top();
        pilha.pop();

        // Marcar o nó como visitado
        visitados[noAtual->getIdNo()] = true;

        cout << noAtual->getIdNo() << " ";

        // Percorrer as arestas saindo desse nó
        Aresta* aresta = noAtual->getPrimeiraAresta();
        while (aresta != nullptr) {
            No* noDestino = buscaNo(aresta->getIdNoDestino());

            if (!visitados[noDestino->getIdNo()]) {
                pilha.push(noDestino);
            }

            aresta = aresta->getProxAresta();
        }
    }

    cout << endl;
}