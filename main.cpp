#include <iostream>
#include <fstream>
#include <string>
#include "include/Grafo.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout <<endl << "--------------------------------------------------------------------------------------------------" << endl<< endl;

    Grafo * g = new Grafo();



    g->insereNo(2);
    g->insereNo(4);
    g->insereNo(5);
    g->insereNo(6);
    g->insereNo(7);

    g->insereAresta(4, 2);
    g->insereAresta(4, 5);
    g->insereAresta(2, 4);

    g->imprimeGrafo();


    /*string archive_name = argv[1];
    ifstream archive("../instancias_grafos_n_ponderados/" + archive_name);
    if (!archive.is_open()) {
        cerr << "Erro ao abrir o arquivo " << archive_name << endl;
        return 1;
    }
    string line;    
    while (getline(archive, line)) {
        cout<< line << endl;
        break;
    }
    archive.close();*/

    return 0;
}
