#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 
#include "include/Grafo.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << endl << "--------------------------------------------------------------------------------------------------" << endl << endl;

    bool digrafo = false;
    bool ponderado = false;
    string archive_name = "ex1.txt";
    string diretory = "./instancias_grafos_ponderados/";
    diretory.append(archive_name);

    

    switch (argc)
    {
    case 2:
        digrafo = (*argv[1] == '1') ? true : false;
        break;
    case 3:
        digrafo = (*argv[1] == '1') ? true : false;
        ponderado = (*argv[2] == '1') ? true : false;
        break;

    case 4:
        digrafo = (*argv[1] == '1') ? true : false;
        ponderado = (*argv[2] == '1') ? true : false;
        archive_name = *argv[3];
        break;
    
    default:
        break;
    }

    ifstream archive;
    archive.open("instancias_grafos_n_ponderados/ex1.txt");


    if (!archive.is_open()) {
        cout << "Erro ao abrir o arquivo "<< endl;
        return 1;
    }

    int no_origem, no_destino;
    int ordem;
    int peso;
    archive >> ordem;

    Grafo * g = new Grafo(digrafo, ponderado, ordem);

    while (!ponderado && archive >> no_origem >> no_destino) {
        g->insereAresta(no_origem, no_destino);
    }
    while (ponderado && archive >> no_origem >> no_destino >> peso) {
        g->insereAresta(no_origem, no_destino, peso);
    }

    g->imprimeGrafo();

    g->fechoTransitivoDireto(7);

    archive.close();
    return 0;
}
