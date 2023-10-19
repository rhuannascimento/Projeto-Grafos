#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 
#include "include/Grafo.h"

using namespace std;

void execFunc(Grafo *g, int opt){

    int no;
    int destino;

    cout<<"Executando a opção " << opt << ":" << endl;

    switch (opt)
    {
    case 1:    
        g->imprimeGrafo();
    break;
    
    case 2:
        cout << "Qual nó você deseja encontrar o fecho transitivo direto?" << endl;
        cin >> no;
        g->fechoTransitivoDireto(no);
    break;
        
    case 3:
        cout << "Qual nó você deseja encontrar o fecho transitivo indireto?" << endl;
        cin >> no;
        g->fechoTransitivoIndireto(no);
    break;

    case 4:
        cout << "De qual nó você deseja partir?" << endl;
        cin >> no;
        cout << "A qual nó você deseja chegar?" << endl;
        cin >> destino;
        g->dijkstra(no, destino);
    break;

    case 5:
        cout << "De qual nó você deseja partir?" << endl;
        cin >> no;
        cout << "A qual nó você deseja chegar?" << endl;
        cin >> destino;
        g->floyd(no, destino);
    break;

    default:
        return;
    }

}

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
    archive.open("instancias_grafo_ponderados/ex1.txt");


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
    
    //================================================================================================================
    // FUNCIONALIDADES
    //================================================================================================================

    bool quit = false;


    while(!quit){
        int option;
        cout << endl << "Funcionalidades:" << endl;
        cout << "|1| Imprimir Grafo." << endl;
        cout << "|2| Fecho transitivo direto." << endl;
        cout << "|3| Fecho transitivo indireto." << endl;
        cout << "|4| Caminho minimo por Dijkstra." << endl;
        cout << "|5| Caminho minimo por floyd." << endl;
        cout << "|0| Sair das funcionalidades." << endl;
        cout << "Insira a opção: ";
        cin >> option;
        cout<<endl;

        switch (option)
        {
        case 0:
            quit = true;
            break;
        default:
            execFunc(g, option);
            break;
        }
    }

    archive.close();
    return 0;
}
