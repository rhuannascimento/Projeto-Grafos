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

string Grafo::fechoTransitivoDireto(int idNo) {
    No* noOrigem = buscaNo(idNo);
    string fechoDireto;

    if (noOrigem == nullptr) {
        //cout << "Nó de origem não encontrado." << endl;
        fechoDireto += "Nó de origem (" + to_string(idNo) + ") não encontrado.\n";
        return fechoDireto;
    }

    // Usando uma pilha para a busca em profundidade
    stack<No*> pilha;
    pilha.push(noOrigem);

    // Vetor para marcar nós visitados
    vector<bool> visitados(ordem, false);

    //cout << "Fecho Transitivo Direto do nó " << idNo << ": ";
    fechoDireto = "Fecho Transitivo Direto do nó " + to_string(idNo) + ": ";

    
    while (!pilha.empty()) {
        No* noAtual = pilha.top();
        pilha.pop();

        // Marcar o nó como visitado
        visitados[noAtual->getIdNo()] = true;

        //cout << noAtual->getIdNo() << " ";
        fechoDireto += std::to_string(noAtual->getIdNo()) + ' ';

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
    fechoDireto += "\n";
    return fechoDireto;
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

string Grafo::fechoTransitivoIndireto(int idNo) {
    string fechoDireto;


    fechoDireto += "Fecho Transitivo Indireto do nó " + to_string(idNo) + ": ";

    No* noOrigem = buscaNo(idNo);

    if (noOrigem == nullptr) {
        fechoDireto += "Nó de origem não encontrado.\n";
        return fechoDireto;
    }

    No* proxNo = this->noRaiz;

    while (proxNo != nullptr) {
        if (proxNo->getIdNo() != noOrigem->getIdNo() && existeCaminho(noOrigem, proxNo)) {
            fechoDireto += to_string(proxNo->getIdNo()) + " ";
        }
        proxNo = proxNo->getProxNo();
    }
    fechoDireto += "\n";
    
    return fechoDireto;
}

int Grafo::dijkstra(int origem, int destino) {
    // Verifique se os vértices de origem e destino existem no grafo
    No* noOrigem = buscaNo(origem);
    No* noDestino = buscaNo(destino);
    string fechoDireto;


    if (noOrigem == nullptr || noDestino == nullptr) {
        return -1; 
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
    /*if (distanciaDestino == numeric_limits<int>::max()) {
        fechoDireto +="Não há caminho entre o vértice " + to_string(origem) + " e o vértice " + to_string(destino)+ ".\n";
    } else {
        fechoDireto += "A distância mínima de " + to_string(origem) + " para " + to_string(destino) + " é " + to_string(distanciaDestino) + " \n";
    }*/

    if (distanciaDestino == numeric_limits<int>::max()) {
       return -1; 
    }

    return distanciaDestino;
}

string Grafo::floyd(int origem, int destino) {
    string result;
    vector<vector<int>> distancia(ordem + 1, vector<int>(ordem + 1, INT_MAX));

    for (int i = 1; i <= ordem; i++) {
        distancia[i][i] = 0;
        Aresta* aresta = buscaNo(i)->getPrimeiraAresta();
        while (aresta != nullptr) {
            distancia[i][aresta->getIdNoDestino()] = aresta->getPesoAresta();
            aresta = aresta->getProxAresta();
        }
    }

    for (int k = 1; k <= ordem; k++) {
        for (int i = 1; i <= ordem; i++) {
            for (int j = 1; j <= ordem; j++) {
                if (distancia[i][k] != INT_MAX && distancia[k][j] != INT_MAX &&
                    distancia[i][k] + distancia[k][j] < distancia[i][j]) {
                    distancia[i][j] = distancia[i][k] + distancia[k][j];
                }
            }
        }
    }

    if(!(distancia[origem][destino] == INT_MAX)){
        result += "Distância mínima entre " + to_string(origem) + " e " + to_string(destino) + ": " + to_string(distancia[origem][destino]) + " \n";
    }else{
        result +=  "Esse cmainho não existe\n";
    }
    return result;
}

void Grafo::primAGM(int ponderado) {
    return;
}


int Grafo::calcularDiametro() {
    int diametro = -1; // Inicializa o diâmetro com um valor impossível

    // Itera sobre todos os pares de nós no grafo
    No* noAtual = this->noRaiz;
    while (noAtual != nullptr) {
        No* outroNo = this->noRaiz;
        while (outroNo != nullptr) {
            if (noAtual != outroNo) {
                // Calcula a distância mínima entre os dois nós usando o algoritmo de Dijkstra
                int distancia = this->dijkstra(noAtual->getIdNo(), outroNo->getIdNo());

                // Atualiza o diâmetro se a distância for maior
                if (distancia > diametro) {
                    diametro = distancia;
                }
            }
            outroNo = outroNo->getProxNo();
        }
        noAtual = noAtual->getProxNo();
    }

    return diametro;
}

















