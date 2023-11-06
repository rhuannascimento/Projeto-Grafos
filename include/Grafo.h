#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "No.h"
#include "Aresta.h"
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <climits>
#include <limits>
#include <cstdio>

using namespace std;

class No;
class Aresta;

class Grafo {
public:

    //--- Construtor e Destrutor ---
    Grafo();
    Grafo(bool digrafo, bool ponderado, int ordem);
    ~Grafo();

    //--- Seters ---


    //--- Getter ---
    bool isDIgrafo(){
        return this->digrafo;
    }

    //--- Funcoes do No ---

    No *insereNo(int idNo);
   

    //--- Funcoes de Aresta ---
  
    bool insereAresta(int noOrigem, int noDestino);
    bool insereAresta(int noOrigem, int noDestino, int peso);

    //--- Caracteristica do Grafo ---
    
    void imprimeGrafo();
    No *buscaNo(int no);
    string fechoTransitivoDireto(int idNo);
    string fechoTransitivoIndireto(int idNo);
    bool existeCaminho(No* origem, No* destino);
    bool buscaEmProfundidade(No* origem, No* destino, vector<bool>& visitados);

    //funcionalidades

    int dijkstra(int origem, int destino);
    string floyd(int origem, int destino);

    void primAGM(int ponderado); 
    bool isConexo();

    int calcularDiametro();
    int calcularRaio() ;
    vector<int> calcularCentro();
    vector<int> calcularPeriferia();

private:

    int ordem;
    int numAresta;
    bool digrafo;
    bool ponderado;

    No *noRaiz = nullptr;
    No *ultimoNo = nullptr;

};


#endif // GRAPH_H
