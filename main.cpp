#include <iostream>
#include <fstream>
#include <string>
#include "include/Grafo.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << endl << "--------------------------------------------------------------------------------------------------" << endl << endl;

    Grafo *g = new Grafo();

   
    ifstream arquivo("instancias_grafos_n_ponderados/ex1.txt"); // Abre o arquivo para leitura
    

    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    int nodeNumbers;

    if (arquivo >> nodeNumbers)
    {
        for (int i = 1; i < nodeNumbers; i++)
        {
            g->insereNo(i);
        }
    }

    

    int a, b;
    while (arquivo >> a >> b)
    {
        g->insereAresta(a, b);
        g->insereAresta(b, a);
        break;
    }
    g->imprimeGrafo();

    arquivo.close(); // Fecha o arquivo

    return 0;
}
