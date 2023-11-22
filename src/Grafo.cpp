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
Grafo::Grafo(bool digrafo, bool ponderado, int ordem, bool noPonderado)
{
    this->digrafo = digrafo;
    this->ponderado = ponderado;
    this->ordem = ordem;
    this->noPonderado = noPonderado;
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
    noRaiz = ultimoNo = nullptr;
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
 * @brief Insere um novo nó no grafo.
 * @param idNo O ID do nó a ser inserido.
 * @param peso O peso do nó a ser inserido.
 * @return Um ponteiro para o nó recém-inserido.
 */
No *Grafo::insereNo(int idNo, int peso)
{

    No *novoNo = new No(idNo, peso);

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
 * @return String contendo o grafo.
 */
string Grafo::imprimeGrafo()
{
    string result;

    if (this->noRaiz == nullptr)
    {
        return "Grafo Vazio";
    }

    No *proxNo = this->noRaiz;
    Aresta *aresta = proxNo->getPrimeiraAresta();

    while (proxNo != nullptr)
    {

        result += "|" + to_string(proxNo->getIdNo()) + "| => ";
        // cout << "|" << proxNo->getIdNo() << "| => ";

        aresta = proxNo->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            if (this->ponderado)
            {
                result += to_string(aresta->getIdNoDestino()) + " (p:" + to_string(aresta->getPesoAresta()) + ") => ";
                // cout << aresta->getIdNoDestino() << " (p:" << aresta->getPesoAresta() << ") => ";
                aresta = aresta->getProxAresta();
            }
            else if (this->noPonderado)
            {
                No *noImpresso = buscaNo(aresta->getIdNoDestino());
                result += to_string(aresta->getIdNoDestino()) + " (p do nó:" + to_string(noImpresso->getPesoNo()) + ") => ";
                // cout << aresta->getIdNoDestino() << " (p:" << aresta->getPesoAresta() << ") => ";
                aresta = aresta->getProxAresta();
            }
            else
            {
                result += to_string(aresta->getIdNoDestino()) + " => ";
                // cout << aresta->getIdNoDestino() << " => ";
                aresta = aresta->getProxAresta();
            }
        }

        result += "\n";
        // cout << endl;

        proxNo = proxNo->getProxNo();
    }
    return result;
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
        if (this->noPonderado)
        {
            origem = insereNo(noOrigem, peso);
        }
        else
        {
            origem = insereNo(noOrigem);
        }
    }

    if (destino == nullptr)
    {
        if (this->noPonderado)
        {
            destino = insereNo(noDestino, peso);
        }
        else
        {
            destino = insereNo(noDestino);
        }
    }

    if (this->isDIgrafo())
    {
        if (this->noPonderado)
        {
            origem->insertAresta(noDestino);
        }
        else
        {
            origem->insertAresta(noDestino, peso);
        }
    }
    else
    {
        if (this->noPonderado)
        {
            origem->insertAresta(noDestino);
            destino->insertAresta(noOrigem);
        }
        else
        {
            origem->insertAresta(noDestino, peso);
            destino->insertAresta(noOrigem, peso);
        }
    }

    return true;
}

/**
 * @brief Insere uma aresta no grafo entre dois nós.
 * @param noOrigem O ID do nó de origem.
 * @param noDestino O ID do nó de destino.
 * @param peso O peso da aresta (opcional, apenas se o grafo for ponderado).
 * @param peso2 O peso do no (opcional, apenas se o grafo for NoPonderado).
 * @return true se a operação foi bem-sucedida, false caso contrário.
 */
bool Grafo::insereAresta(int noOrigem, int noDestino, int peso, int peso2)
{

    No *origem = this->buscaNo(noOrigem);
    No *destino = this->buscaNo(noDestino);

    if (origem == nullptr)
    {
        origem = insereNo(noOrigem, peso2);
    }

    if (destino == nullptr)
    {
        destino = insereNo(noDestino, peso2);
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
int Grafo::dijkstra(int origem, int destino) {
   
    No *noOrigem = buscaNo(origem);
    No *noDestino = buscaNo(destino);

    if (noOrigem == nullptr || noDestino == nullptr) {
        cout << "Nós de origem ou destino não encontrados no grafo." << endl;
        return -1; 
    }
    if (noOrigem == noDestino)
    {
        return 0;
    }

 
    vector<int> distancia(ordem + 1, INT_MAX);
    distancia[origem] = 0;

    set<int> visitados;

  
    while (visitados.size() < ordem) {
       
        int verticeAtual = -1;
        int distanciaMinima = INT_MAX;

        for (int i = 1; i <= ordem; ++i) {
            if (visitados.find(i) == visitados.end() && distancia[i] < distanciaMinima) {
                verticeAtual = i;
                distanciaMinima = distancia[i];
            }
        }

        if (verticeAtual == -1) {
            break;
        }

        visitados.insert(verticeAtual);

        No *noAtual = buscaNo(verticeAtual);

        Aresta *aresta = noAtual->getPrimeiraAresta();

        while(aresta != nullptr){
            No *vizinho =  buscaNo(aresta->getIdNoDestino()); 
            int custo = aresta->getPesoAresta();
            distancia[vizinho->getIdNo()] = min(distancia[vizinho->getIdNo()], distancia[verticeAtual] + custo);
            aresta = aresta->getProxAresta();
        }
    }

    if (distancia[destino] == INT_MAX)
    {
        return -1;
    }

   
    return distancia[destino];
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

    No *noOrigem = buscaNo(origem);
    No *noDestino = buscaNo(destino);

    if (noOrigem == nullptr || noDestino == nullptr)
    {
         cout << "Nós de origem ou destino não encontrados no grafo." << endl;
        return -1;
    }

    if (noOrigem == noDestino)
    {
        return 0;
    }

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
string Grafo::primAGM()
{

    if (this->digrafo)
    {
        return "Não é possível AGM em digrafos!";
    }

    vector<bool> inAGM(ordem, false);
    vector<int> chave(ordem, INT_MAX);
    vector<int> pai(ordem, -1);

    int raiz = noRaiz->getIdNo();
    chave[raiz - 1] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaPrioridade;
    filaPrioridade.push(make_pair(0, raiz));

    while (!filaPrioridade.empty())
    {
        int u = filaPrioridade.top().second;
        filaPrioridade.pop();

        if (inAGM[u - 1])
            continue;

        inAGM[u - 1] = true;

        Aresta *aresta = buscaNo(u)->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            int v = aresta->getIdNoDestino();
            int peso = aresta->getPesoAresta();

            if (!inAGM[v - 1] && peso < chave[v - 1])
            {
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
    for (int i = 0; i < ordem; i++)
    {
        if (pai[i] != -1)
        {
            int u = pai[i];
            int v = i + 1;
            int peso = chave[i];

            result += to_string(u) + " " + to_string(v) + " " + to_string(peso) + "\n";

            pesoTotal += peso;
        }
    }

    result += "Peso total da Árvore Geradora Mínima: " + to_string(pesoTotal) + "\n";

    return result;
}

/**
 * @brief Aplica o algoritmo de Kruskal para encontrar uma Árvore Geradora Mínima (AGM) no grafo.
 */
string Grafo::kruskalAGM()
{

    if (this->digrafo)
    {
        return "Não é possível AGM em digrafos!";
    }

    vector<pair<int, pair<int, int>>> arestasOrdenadas;

    for (No *noAtual = noRaiz; noAtual != nullptr; noAtual = noAtual->getProxNo())
    {
        Aresta *aresta = noAtual->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            int noOrigem = noAtual->getIdNo();
            int noDestino = aresta->getIdNoDestino();
            int peso = aresta->getPesoAresta();
            arestasOrdenadas.push_back({peso, {noOrigem, noDestino}});
            aresta = aresta->getProxAresta();
        }
    }

    sort(arestasOrdenadas.begin(), arestasOrdenadas.end());

    vector<int> conjunto(ordem + 1);

    for (int i = 1; i <= ordem; ++i)
    {
        conjunto[i] = i;
    }

    vector<pair<int, pair<int, int>>> arvoreGeradoraMinima;

    for (int i = 0; i < arestasOrdenadas.size(); ++i)
    {
        int origem = arestasOrdenadas[i].second.first;
        int destino = arestasOrdenadas[i].second.second;

        if (conjunto[origem] != conjunto[destino])
        {
            arvoreGeradoraMinima.push_back(arestasOrdenadas[i]);

            int conjuntoOrigem = conjunto[origem];
            int conjuntoDestino = conjunto[destino];
            for (int j = 1; j <= ordem; ++j)
            {
                if (conjunto[j] == conjuntoDestino)
                {
                    conjunto[j] = conjuntoOrigem;
                }
            }
        }
    }

    string result = "";
   
    result +=  "Arestas da Árvore Geradora Mínima (kruskal): \n";
    int pesoTotal = 0;
    for (auto &aresta : arvoreGeradoraMinima)
    {
        int origem = aresta.second.first;
        int destino = aresta.second.second;
        int peso = aresta.first;
        pesoTotal += peso;
        result += to_string(origem) + " " + to_string(destino) + " " + to_string(peso) + "\n";
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

/**
 * @brief Calcula o centro do grafo.
 * @return Um vetor de inteiros com os centros do grafo.
 */
string Grafo::calcularCentro() {
    int menorExcentricidade = INT_MAX;

    int contador = 0;
    string centro;

    for (No *noAtual = noRaiz; noAtual != nullptr; noAtual = noAtual->getProxNo())
    {
        int excentricidadeAtual = 0;

        for (No *outroNo = noRaiz; outroNo != nullptr; outroNo = outroNo->getProxNo())
        {
            int distancia = floyd(noAtual->getIdNo(), outroNo->getIdNo());
            excentricidadeAtual = max(excentricidadeAtual, distancia);
        }

        if (excentricidadeAtual < menorExcentricidade)
        {
            menorExcentricidade = excentricidadeAtual;
            
            centro += to_string(noAtual->getIdNo()) + " " ;
            contador = 1;
        }
    }

    if(contador == 0){
        return "Grafo nao possui centro";
    }

    return centro;
}

/**
 * @brief Calcula a periferia do grafo.
 * @return Um vetor de inteiros com as perifeiras do grafo.
 */
string Grafo::calcularPeriferia() {
    int maiorExcentricidade = INT_MIN;
    string periferia;
    int contador = 0;

    for (No *noAtual = noRaiz; noAtual != nullptr; noAtual = noAtual->getProxNo()) {
        int excentricidadeAtual = 0;

        for (No *outroNo = noRaiz; outroNo != nullptr; outroNo = outroNo->getProxNo())
        {
            int distancia = floyd(noAtual->getIdNo(), outroNo->getIdNo());
            excentricidadeAtual = max(excentricidadeAtual, distancia);
        }

        maiorExcentricidade = max(maiorExcentricidade, excentricidadeAtual);
    }


    for (No *noAtual = noRaiz; noAtual != nullptr; noAtual = noAtual->getProxNo())
    {

        int excentricidadeAtual = 0;

        for (No *outroNo = noRaiz; outroNo != nullptr; outroNo = outroNo->getProxNo())
        {
            int distancia = floyd(noAtual->getIdNo(), outroNo->getIdNo());
            excentricidadeAtual = max(excentricidadeAtual, distancia);
        }

        if (excentricidadeAtual == maiorExcentricidade) {
            periferia += to_string(noAtual->getIdNo()) + " " ;
            contador = 1;
        }
    }

    if(contador == 0 ){
        return "Grafo nao possui periferia";
    }

    return periferia;
}

/**
 * @brief Calcula a Ordenação Topológica do grafo.
 * @return Um vetor com a Ordenação Topológica ou um vetor vazio se o grafo não for acíclico direcionado.
 */
vector<int> Grafo::ordenacaoTopologica()
{
    vector<int> resultado;             // Vetor para armazenar a ordenação topológica
    vector<int> grauEntrada(ordem, 0); // Vetor para armazenar o grau de entrada de cada nó
    queue<No *> fila;                  // Fila para realizar a ordenação topológica

    // Calcula o grau de entrada de cada nó
    for (No *noAtual = noRaiz; noAtual != nullptr; noAtual = noAtual->getProxNo())
    {
        Aresta *aresta = noAtual->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            grauEntrada[aresta->getIdNoDestino()]++;
            aresta = aresta->getProxAresta();
        }
    }

    // Adiciona nós com grau de entrada zero à fila
    for (No *noAtual = noRaiz; noAtual != nullptr; noAtual = noAtual->getProxNo())
    {
        if (grauEntrada[noAtual->getIdNo()] == 0)
        {
            fila.push(noAtual);
        }
    }

    // Realiza a ordenação topológica
    while (!fila.empty())
    {
        No *noAtual = fila.front();
        fila.pop();

        resultado.push_back(noAtual->getIdNo());

        Aresta *aresta = noAtual->getPrimeiraAresta();
        while (aresta != nullptr)
        {
            grauEntrada[aresta->getIdNoDestino()]--;

            if (grauEntrada[aresta->getIdNoDestino()] == 0)
            {
                fila.push(buscaNo(aresta->getIdNoDestino()));
            }

            aresta = aresta->getProxAresta();
        }
    }

    // Verifica se o grafo é acíclico direcionado
    for (int grau : grauEntrada)
    {
        if (grau > 0)
        {
            // Se algum nó ainda tem grau de entrada maior que zero, o grafo possui ciclo
            return vector<int>(); // Retorna um vetor vazio indicando que o grafo não é acíclico direcionado
        }
    }

    return resultado;
}

/**
 * Auxiliar da função que encontra os vértices de articulação no grafo.
 */
void Grafo::encontrarArticulacaoDFS(No* u, No* pai, int& tempo, vector<int>& descoberta, vector<int>& baixo, vector<bool>& visitado, set<int>& verticesDeArticulacao) {
    int filhos = 0;

    descoberta[u->getIdNo()] = baixo[u->getIdNo()] = ++tempo;
    visitado[u->getIdNo()] = true;

    Aresta* aresta = u->getPrimeiraAresta();

    while (aresta != nullptr) {
        No* v = buscaNo(aresta->getIdNoDestino());

        if (!visitado[v->getIdNo()]) {
            filhos++;
            encontrarArticulacaoDFS(v, u, tempo, descoberta, baixo, visitado, verticesDeArticulacao);

            baixo[u->getIdNo()] = min(baixo[u->getIdNo()], baixo[v->getIdNo()]);

            // Verifica se u é vértice de articulação
            if (baixo[v->getIdNo()] >= descoberta[u->getIdNo()] && pai != nullptr) {
                verticesDeArticulacao.insert(u->getIdNo());
            }
        } else if (v != pai) {
            baixo[u->getIdNo()] = min(baixo[u->getIdNo()], descoberta[v->getIdNo()]);
        }

        aresta = aresta->getProxAresta();
    }

    // Verifica se u é vértice de articulação (caso especial para a raiz da árvore DFS)
    if (pai == nullptr && filhos > 1) {
        verticesDeArticulacao.insert(u->getIdNo());
    }
}

/**
 * Encontra os vértices de articulação no grafo.
 * @return Uma string contendo os vértices de articulação.
 */
string Grafo::encontrarVerticesDeArticulacao() {
    vector<int> descoberta(ordem, -1);
    vector<int> baixo(ordem, -1);
    vector<bool> visitado(ordem, false);
    set<int> verticesDeArticulacao;

    int tempo = 0;

    // Inicia a DFS para encontrar os vértices de articulação
    for (No* noAtual = noRaiz; noAtual != nullptr; noAtual = noAtual->getProxNo()) {
        if (!visitado[noAtual->getIdNo()]) {
            encontrarArticulacaoDFS(noAtual, nullptr, tempo, descoberta, baixo, visitado, verticesDeArticulacao);
        }
    }

    // Formata os resultados em uma string
    string resultado = "Vértices de Articulação: ";
    for (int vertice : verticesDeArticulacao) {
        resultado += to_string(vertice) + " ";
    }

    return resultado + "\n";
}





