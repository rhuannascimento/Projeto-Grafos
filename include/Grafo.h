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
  
    

    //--- Caracteristica do Grafo ---
    
    void imprimeGrafo(){

        if(this->noRaiz == nullptr){
            return;
        }
        
        cout<<"No raiz: "<< this->noRaiz->getIdNo() <<endl;
        No * proxNo = this->noRaiz->getProxNo();

        while(proxNo != nullptr){
            cout<<proxNo->getIdNo()<<endl;
            proxNo = proxNo->getProxNo();
        }

    }


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
