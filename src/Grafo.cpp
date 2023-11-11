/**
 * @file Grafo.cpp
 * @brief Este arquivo contém a implementação das funções da classe Grafo.
 */

#include "../include/Grafo.h"
#include "../include/Aresta.h"

/**
 * @brief Construtor da classe Grafo.
 * @param digrafo Indica se o grafo é direcionado (true) ou não (false).
 * @param ponderado Indica se o grafo é ponderado (true) ou não (false).
 * @param ordem O número de nós no grafo.
 */
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

/**
 * @brief Destrutor da classe Grafo.
 */
Grafo::~Grafo()
{
    // Libere a memória alocada para nós e arestas
    No *proxNo = noRaiz;
    while (proxNo != nullptr)
    {
        No *temp = proxNo;
        proxNo = proxNo->getProxNo();
        delete temp;
    }
}

/**
 * @brief Insere um novo nó no grafo.
 * @param idNo O ID do nó a ser inserido.
 * @return Um ponteiro para o nó recém-inserido.
 */
No *Grafo::insereNo(int idNo)
{

    No *novoNo = new No(idNo);

    if (this->noRaiz == nullptr)
    {
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

/**
 * @brief Imprime o grafo, mostrando os nós e suas arestas.
 */
void Grafo::imprimeGrafo()
{

    if (this->noRaiz == nullptr)
    {
        return;
    }

    No *proxNo = this->noRaiz;
    Aresta *aresta = proxNo->getPrimeiraAresta();

    while (proxNo != nullptr)
    {

        cout << "|" << proxNo->getIdNo() << "| => ";

        aresta = proxNo->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            if (this->ponderado)
            {
                cout << aresta->getIdNoDestino() << " (p:" << aresta->getPesoAresta() << ") => ";
                aresta = aresta->getProxAresta();
            }
            else
            {
                cout << aresta->getIdNoDestino() << " => ";
                aresta = aresta->getProxAresta();
            }
        }

        cout << endl;

        proxNo = proxNo->getProxNo();
    }
}

/**
 * @brief Busca um nó pelo seu ID.
 * @param no O ID do nó a ser buscado.
 * @return Um ponteiro para o nó encontrado ou nullptr se não encontrado.
 */
No *Grafo::buscaNo(int no)
{

    if (this->noRaiz == nullptr)
    {
        insereNo(no);
    }

    if (this->noRaiz->getIdNo() == no)
    {
        return this->noRaiz;
    }

    No *noBusca = this->noRaiz->getProxNo();

    while (noBusca != nullptr && noBusca->getIdNo() != no)
    {
        noBusca = noBusca->getProxNo();
    }

    return noBusca;
}

/**
 * @brief Insere uma aresta no grafo entre dois nós.
 * @param noOrigem O ID do nó de origem.
 * @param noDestino O ID do nó de destino.
 * @param peso O peso da aresta (opcional, apenas se o grafo for ponderado).
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool Grafo::insereAresta(int noOrigem, int noDestino, int peso)
{

    No *origem = this->buscaNo(noOrigem);
    No *destino = this->buscaNo(noDestino);

    if (origem == nullptr)
    {
        origem = insereNo(noOrigem);
    }

    if (destino == nullptr)
    {
        destino = insereNo(noDestino);
    }

    if (this->isDIgrafo())
    {
        origem->insertAresta(noDestino, peso);
    }
    else
    {
        origem->insertAresta(noDestino, peso);
        destino->insertAresta(noOrigem, peso);
    }

    return true;
}

/**
 * @brief Sobrecarga da função para inserir uma aresta sem peso.
 * @param noOrigem O ID do nó de origem.
 * @param noDestino O ID do nó de destino.
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool Grafo::insereAresta(int noOrigem, int noDestino)
{

    No *origem = this->buscaNo(noOrigem);
    No *destino = this->buscaNo(noDestino);

    if (origem == nullptr)
    {
        origem = insereNo(noOrigem);
    }

    if (destino == nullptr)
    {
        destino = insereNo(noDestino);
    }

    if (this->isDIgrafo())
    {
        origem->insertAresta(noDestino);
    }
    else
    {
        origem->insertAresta(noDestino);
        destino->insertAresta(noOrigem);
    }

    return true;
}

/**
 * @brief Calcula o fecho transitivo direto de um nó.
 * @param idNo O ID do nó de origem.
 * @return Uma string que representa o fecho transitivo direto do nó.
 */
string Grafo::fechoTransitivoDireto(int idNo)
{
    No *noOrigem = buscaNo(idNo);
    string fechoDireto;

    if (noOrigem == nullptr)
    {
        fechoDireto += "Nó de origem (" + to_string(idNo) + ") não encontrado.\n";
        return fechoDireto;
    }

    stack<No *> pilha;
    pilha.push(noOrigem);

    vector<bool> visitados(ordem, false);

    fechoDireto = "Fecho Transitivo Direto do nó " + to_string(idNo) + ": ";

    while (!pilha.empty())
    {
        No *noAtual = pilha.top();
        pilha.pop();

        visitados[noAtual->getIdNo()] = true;

        fechoDireto += std::to_string(noAtual->getIdNo()) + ' ';

        Aresta *aresta = noAtual->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            No *noDestino = buscaNo(aresta->getIdNoDestino());

            if (!visitados[noDestino->getIdNo()])
            {
                pilha.push(noDestino);
            }

            aresta = aresta->getProxAresta();
        }
    }
    fechoDireto += "\n";
    return fechoDireto;
}

/**
 * @brief Verifica se existe um caminho entre dois nós.
 * @param origem Um ponteiro para o nó de origem.
 * @param destino Um ponteiro para o nó de destino.
 * @return true se existe um caminho entre os nós, false caso contrário.
 */
bool Grafo::existeCaminho(No *origem, No *destino)
{

    vector<bool> visitados(ordem, false);

    return buscaEmProfundidade(origem, destino, visitados);
}

/**
 * @brief Realiza uma busca em profundidade (DFS) a partir de um nó de origem para verificar a existência de um caminho até um nó de destino.
 * @param origem Um ponteiro para o nó de origem.
 * @param destino Um ponteiro para o nó de destino que estamos tentando alcançar.
 * @param visitados Um vetor que rastreia os nós visitados durante a busca.
 * @return true se existe um caminho de 'origem' para 'destino', false caso contrário.
 */
bool Grafo::buscaEmProfundidade(No *origem, No *destino, vector<bool> &visitados)
{

    visitados[origem->getIdNo()] = true;

    if (origem == destino)
    {
        return true;
    }

    Aresta *aresta = origem->getPrimeiraAresta();
    while (aresta != nullptr)
    {
        No *proximoNo = buscaNo(aresta->getIdNoDestino());

        if (!visitados[proximoNo->getIdNo()] && buscaEmProfundidade(proximoNo, destino, visitados))
        {
            return true;
        }

        aresta = aresta->getProxAresta();
    }

    return false;
}

/**
 * @brief Calcula o fecho transitivo indireto de um nó.
 * @param idNo O ID do nó de origem.
 * @return Uma string que representa o fecho transitivo indireto do nó.
 */
string Grafo::fechoTransitivoIndireto(int idNo)
{
    string fechoDireto;

    fechoDireto += "Fecho Transitivo Indireto do nó " + to_string(idNo) + ": ";

    No *noOrigem = buscaNo(idNo);

    if (noOrigem == nullptr)
    {
        fechoDireto += "Nó de origem não encontrado.\n";
        return fechoDireto;
    }

    No *proxNo = this->noRaiz;

    while (proxNo != nullptr)
    {
        if (proxNo->getIdNo() != noOrigem->getIdNo() && existeCaminho(noOrigem, proxNo))
        {
            fechoDireto += to_string(proxNo->getIdNo()) + " ";
        }
        proxNo = proxNo->getProxNo();
    }
    fechoDireto += "\n";

    return fechoDireto;
}

/**
 * @brief Calcula a distância mínima entre dois nós usando o algoritmo de Dijkstra.
 * @param origem O ID do nó de origem.
 * @param destino O ID do nó de destino.
 * @return A distância mínima entre os nós, ou -1 se não houver caminho.
 */
int Grafo::dijkstra(int origem, int destino)
{

    No *noOrigem = buscaNo(origem);
    No *noDestino = buscaNo(destino);
    string fechoDireto;

    if (noOrigem == nullptr || noDestino == nullptr)
    {
        return -1;
    }

    vector<int> distanciaMinima(ordem, numeric_limits<int>::max());

    distanciaMinima[origem] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaPrioridade;
    filaPrioridade.push(make_pair(0, origem));

    while (!filaPrioridade.empty())
    {
        int u = filaPrioridade.top().second;
        filaPrioridade.pop();

        Aresta *aresta = buscaNo(u)->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            int v = aresta->getIdNoDestino();
            int peso = aresta->getPesoAresta();

            if (distanciaMinima[u] + peso < distanciaMinima[v])
            {
                distanciaMinima[v] = distanciaMinima[u] + peso;
                filaPrioridade.push(make_pair(distanciaMinima[v], v));
            }

            aresta = aresta->getProxAresta();
        }
    }

    int distanciaDestino = distanciaMinima[destino];


    if (distanciaDestino == numeric_limits<int>::max())
    {
        return -1;
    }

    return distanciaDestino;
}

/**
 * @brief Calcula a distância mínima entre dois nós usando o algoritmo de Floyd-Warshall.
 * @param origem O ID do nó de origem.
 * @param destino O ID do nó de destino.
 * @return A distância mínima entre os nós, ou -1 não houver caminho.
 */
int Grafo::floyd(int origem, int destino)
{
    string result;
    vector<vector<int>> distancia(ordem + 1, vector<int>(ordem + 1, INT_MAX));

    for (int i = 1; i <= ordem; i++)
    {
        distancia[i][i] = 0;
        Aresta *aresta = buscaNo(i)->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            distancia[i][aresta->getIdNoDestino()] = aresta->getPesoAresta();
            aresta = aresta->getProxAresta();
        }
    }

    for (int k = 1; k <= ordem; k++)
    {
        for (int i = 1; i <= ordem; i++)
        {
            for (int j = 1; j <= ordem; j++)
            {
                if (distancia[i][k] != INT_MAX && distancia[k][j] != INT_MAX &&
                    distancia[i][k] + distancia[k][j] < distancia[i][j])
                {
                    distancia[i][j] = distancia[i][k] + distancia[k][j];
                }
            }
        }
    }

    if (distancia[origem][destino] == INT_MAX)
    {
        return -1;
    }

 
    return distancia[origem][destino];
}


/**
 * @brief Aplica o algoritmo de Prim para encontrar uma Árvore Geradora Mínima (AGM) no grafo.
 */
string Grafo::primAGM() {


    if(this->digrafo){
        return "Não é possível AGM em digrafos!";
    }
  
    vector<bool> inAGM(ordem, false); 
    vector<int> chave(ordem, INT_MAX);  
    vector<int> pai(ordem, -1);  

    
    int raiz = noRaiz->getIdNo();
    chave[raiz - 1] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaPrioridade;
    filaPrioridade.push(make_pair(0, raiz));

    while (!filaPrioridade.empty()) {
        int u = filaPrioridade.top().second;
        filaPrioridade.pop();

        if (inAGM[u - 1]) continue;  

        inAGM[u - 1] = true;

        Aresta* aresta = buscaNo(u)->getPrimeiraAresta();
        while (aresta != nullptr) {
            int v = aresta->getIdNoDestino();
            int peso = aresta->getPesoAresta();

            if (!inAGM[v - 1] && peso < chave[v - 1]) {
                chave[v - 1] = peso;
                pai[v - 1] = u;

                filaPrioridade.push(make_pair(peso, v));
            }

            aresta = aresta->getProxAresta();
        }
    }


    string result = "";


    int pesoTotal = 0;
    result += "Arestas da Árvore Geradora Mínima (Prim): \n";
    for (int i = 0; i < ordem; i++) {
        if (pai[i] != -1) {
            int u = pai[i];
            int v = i + 1;
            int peso = chave[i];

            result +=  to_string(u) + " " + to_string(v) + " " + to_string(peso)  + "\n";

            pesoTotal += peso;
        }
    }

    result += "Peso total da Árvore Geradora Mínima: " + to_string(pesoTotal) + "\n";

    return result;
}


/**
 * @brief Calcula o diâmetro do grafo.
 * @return O diâmetro do grafo.
 */
int Grafo::calcularDiametro()
{
    int diametro = -1;

    for (No *noAtual = this->noRaiz; noAtual != nullptr; noAtual = noAtual->getProxNo())
    {
        int distanciaMaxima = 0;

        for (No *outroNo = this->noRaiz; outroNo != nullptr; outroNo = outroNo->getProxNo())
        {
            if (noAtual != outroNo)
            {
                int distancia = floyd(noAtual->getIdNo(), outroNo->getIdNo());
                distanciaMaxima = max(distanciaMaxima, distancia);
            }
        }

        diametro = max(diametro, distanciaMaxima);
    }

    return diametro;
}

/**
 * @brief Calcula o raio do grafo.
 * @return O raio do grafo.
 */
int Grafo::calcularRaio()
{
    int raio = INT_MAX;

    for (No *noAtual = this->noRaiz; noAtual != nullptr; noAtual = noAtual->getProxNo())
    {
        int distanciaMaxima = 0;

        for (No *outroNo = this->noRaiz; outroNo != nullptr; outroNo = outroNo->getProxNo())
        {
            if (noAtual != outroNo)
            {
                int distancia = floyd(noAtual->getIdNo(), outroNo->getIdNo());
                distanciaMaxima = max(distanciaMaxima, distancia);
            }
        }

        raio = min(raio, distanciaMaxima);
    }

    return raio;
}

