#ifndef NO_H
#define NO_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Aresta.h"

using namespace std;
class Aresta;

class No {
public:
    No(int idNo);
    ~No();

    int getIdNo ();
    No * getProxNo();
    Aresta * getPrimeiraAresta(){return primeiraAresta;}

    void setProxNo(No *no);
    Aresta * insertAresta(int destino);
    Aresta * insertArestaPonderada(int destino, int peso);


private:
    int idNo = -1;
    int pesoNo;
    int grauEntrada;
    int grauSaida;
    No *proxNo;
    Aresta *primeiraAresta = nullptr;
    Aresta *ultimaAresta;
};

#endif // NO_H
