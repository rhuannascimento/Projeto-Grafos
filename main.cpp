#include <iostream>
#include <fstream>
#include <string>
#include "include/Grafo.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout <<endl << "--------------------------------------------------------------------------------------------------" << endl<< endl;

    Grafo * g = new Grafo();

    string archive_name = argv[1];
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
    archive.close();

    return 0;
}
