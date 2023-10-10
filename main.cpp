#include <iostream>
#include <fstream>
#include <string>
#include "include/Grafo.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << endl << "--------------------------------------------------------------------------------------------------" << endl << endl;

    Grafo * g = new Grafo(false);

    ifstream archive("./instancias_grafos_n_ponderados/ex1.txt");

    if (!archive.is_open()) {
        cerr << "Erro ao abrir o arquivo "<< endl;
        return 1;
    }

    int no_origem, no_destino;
    int n_nos;
    archive >> n_nos;

    while (archive >> no_origem >> no_destino) {
        g->insereAresta(no_origem, no_destino);
    }

    g->imprimeGrafo();


    archive.close();
    return 0;
}
