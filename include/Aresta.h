#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "No.h"

using namespace std;

class No;

class Aresta {
public:
    Aresta(int idNoDestino);
    Aresta(int idNoDestino, int pesoAresta);

    int getPesoAresta();

    void setProxAresta(Aresta *aresta);
    
    Aresta *getProxAresta(){
        return proxAresta;
    };

    int getidNoDestino(){return idNoDestino;}
    
private:
    int pesoAresta;
    int idNoDestino;
    Aresta *proxAresta;
};

#endif // ARESTA_H
