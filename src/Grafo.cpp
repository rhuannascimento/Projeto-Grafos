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


bool Grafo::existeCaminho(No* origem, No* destino) {
 
    vector<bool> visitados(ordem, false);

    return buscaEmProfundidade(origem, destino, visitados);
}

bool Grafo::buscaEmProfundidade(No* origem, No* destino, vector<bool>& visitados) {

    visitados[origem->getIdNo()] = true;

    if (origem == destino) {
        return true;
    }

    Aresta* aresta = origem->getPrimeiraAresta();
    while (aresta != nullptr) {
        No* proximoNo = buscaNo(aresta->getIdNoDestino());

        if (!visitados[proximoNo->getIdNo()] && buscaEmProfundidade(proximoNo, destino, visitados)) {
            return true;
        }

        aresta = aresta->getProxAresta();
    }

    return false;
}

void Grafo::fechoTransitivoIndireto(int idNo) {
    cout << "Fecho Transitivo Indireto do nó " << idNo << ": ";

    No* noOrigem = buscaNo(idNo);

    if (noOrigem == nullptr) {
        cout << "Nó de origem não encontrado." << endl;
        return;
    }

    No* proxNo = this->noRaiz;

    while (proxNo != nullptr) {
        if (proxNo->getIdNo() != noOrigem->getIdNo() && existeCaminho(noOrigem, proxNo)) {
            cout << proxNo->getIdNo() << " ";
        }
        proxNo = proxNo->getProxNo();
    }

    cout << endl;
}

//////////////////////////////////////////////////

#include <vector>
#include <queue>
#include <limits>

// ...

void Grafo::dijkstra(int origem, int destino) {
    // Verifique se os vértices de origem e destino existem no grafo
    No* noOrigem = buscaNo(origem);
    No* noDestino = buscaNo(destino);

    if (noOrigem == nullptr || noDestino == nullptr) {
        cout << "Nó de origem ou destino não encontrado." << endl;
        return;
    }

    // Vetor para rastrear as distâncias mínimas
    vector<int> distanciaMinima(ordem, numeric_limits<int>::max());

    // Defina a distância mínima para o vértice de origem como 0
    distanciaMinima[origem] = 0;

    // Use uma fila de prioridade para escolher os vértices com a menor distância
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaPrioridade;
    filaPrioridade.push(make_pair(0, origem));

    while (!filaPrioridade.empty()) {
        int u = filaPrioridade.top().second;
        filaPrioridade.pop();

        // Percorra as arestas do vértice atual
        Aresta* aresta = buscaNo(u)->getPrimeiraAresta();
        while (aresta != nullptr) {
            int v = aresta->getIdNoDestino();
            int peso = aresta->getPesoAresta();

            // Se a distância mínima até 'v' pode ser melhorada passando por 'u', atualize-a
            if (distanciaMinima[u] + peso < distanciaMinima[v]) {
                distanciaMinima[v] = distanciaMinima[u] + peso;
                filaPrioridade.push(make_pair(distanciaMinima[v], v));
            }

            aresta = aresta->getProxAresta();
        }
    }

    // A partir deste ponto, o vetor distanciaMinima contém as distâncias mínimas de 'origem' para todos os vértices.
    // Você pode usar esse vetor para determinar a distância mínima para o vértice de destino.

    int distanciaDestino = distanciaMinima[destino];
    if (distanciaDestino == numeric_limits<int>::max()) {
        cout << "Não há caminho entre o vértice de origem e o vértice de destino." << endl;
    } else {
        cout << "A distância mínima de " << origem << " para " << destino << " é " << distanciaDestino << endl;
    }
}

// ...
