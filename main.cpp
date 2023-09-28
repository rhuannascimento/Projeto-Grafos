#include <iostream>
#include <fstream>
#include <string>
#include "include/Grafo.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << endl << "--------------------------------------------------------------------------------------------------" << endl << endl;

    Grafo *g = new Grafo();
   
    ifstream arquivo; // Abre o arquivo para leitura

    bool ponderado = (*argv[1] == '1') ? true : false;

    if(ponderado){
        arquivo.open("instancias_grafo_ponderados/ex1.txt");
    }else{
        arquivo.open("instancias_grafos_n_ponderados/ex1.txt");
    }
    

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

    int a, b, c;
    while (!ponderado && arquivo >> a >> b)
    {
        g->insereAresta(a, b);
        g->insereAresta(b, a);
        break;
    }

    while (arquivo >> a >> b >> c && ponderado)
    {

        g->insereArestaPonderada(a, b, c);
        g->insereArestaPonderada(b, a, c);
        break;
    }


    g->imprimeGrafo();

    arquivo.close(); // Fecha o arquivo

    return 0;
}
