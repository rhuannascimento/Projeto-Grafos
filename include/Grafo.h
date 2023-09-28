#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "No.h"
#include "Aresta.h"


using namespace std;

class No;
class Aresta;

class Grafo {
public:

    //--- Construtor e Destrutor ---
    Grafo();
    ~Grafo();

    //--- Seters ---


    //--- Funcoes do No ---

    No *insereNo(int idNo);
   

    //--- Funcoes de Aresta ---
  
    Aresta * insereAresta(int noOrigem, int noDestino);
    Aresta * insereArestaPonderada(int noOrigem, int noDestino, int peso);

    //--- Caracteristica do Grafo ---
    
    void imprimeGrafo();
    No *buscaNo(int no);


private:

    int ordem;
    int numAresta;
    bool digrafo;
    bool weigthNo;
    bool weightArc;

    No *noRaiz;
    No *ultimoNo;

};


#endif // GRAPH_H
