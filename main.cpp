#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "include/Grafo.h"

using namespace std;

void execFunc(Grafo *g, int opt, ofstream &output_file, bool digrafo, bool ponderado)
{

    int no;
    int destino;
    int option = 0;
    string result = "";
    vector<int> vetorAux = {};

    cout << "Executando a opção " << opt << ":" << endl;
    while (option != 1 && option != 2)
    {
        cout << "|1| Imprimir no console o resultado" << endl;
        cout << "|2| Salvar em um arquivo o resultado" << endl;
        cin >> option;
    }

    cout << "=========================================================================================================" << endl;

    switch (opt)
    {
    case 1:
        result = g->imprimeGrafo();
        break;

    case 2:

        if (digrafo)
        {

            cout << "Qual nó você deseja encontrar o fecho transitivo direto?" << endl;
            cin >> no;

            result = g->fechoTransitivoDireto(no);
        }
        else
        {
            cout << "O grafo não é direcionado!" << endl;
        }

        break;

    case 3:

        if (digrafo)
        {
            cout << "Qual nó você deseja encontrar o fecho transitivo indireto?" << endl;
            cin >> no;

            result = g->fechoTransitivoIndireto(no);
        }
        else
        {
            cout << "O grafo não é direcionado!" << endl;
        }

        break;

    case 4:
        cout << "De qual nó você deseja partir?" << endl;
        cin >> no;
        cout << "A qual nó você deseja chegar?" << endl;
        cin >> destino;

        result = "A menor distância (Dijkstra) entre o nó (" + to_string(no) + ") e o nó (" + to_string(destino) + ") é: " + to_string(g->dijkstra(no, destino)) + "\n";

        break;

    case 5:
        cout << "De qual nó você deseja partir?" << endl;
        cin >> no;
        cout << "A qual nó você deseja chegar?" << endl;
        cin >> destino;

        result = "A menor distância (Floyd) entre o nó (" + to_string(no) + ") e o nó (" + to_string(destino) + ") é: " + to_string(g->floyd(no, destino)) + "\n";

        break;

    case 6:

        result = g->primAGM();

        break;

    case 7:

        result = g->kruskalAGM();

        break;

    case 9:
        vetorAux = g->ordenacaoTopologica();

        if (vetorAux.size() == 0)
        {
            result = "O grafo é acíclico direcionado.\n";
            break;
        }

        result = "Odenação topologica do grafo: ";
        for (int i = 0; i < vetorAux.size(); i++)
        {
            result += vetorAux[i] + "  ";
        }
        result += "\n";

        break;

    case 10:
        if (ponderado)
        {
            result = "Raio do Grafo: " + to_string(g->calcularRaio()) + "\n";

            result += "Diâmetro do Grafo: " + to_string(g->calcularDiametro()) + "\n";

            result += "Centro do Grafo: " + g->calcularCentro() + "\n";

            result += "Periferia do Grafo: " + g->calcularPeriferia() + "\n";
        }
        else
        {
            cout << "O grafo não é ponderado!" << endl;
        }

        break;
    case 11:

        if (!digrafo)
        {

            result = "Conjunto de vértices de articulação: " + g->encontrarVerticesDeArticulacao();
        }
        else
        {
            cout << "O grafo é direcionado!" << endl;
        }

        break;

    default:
        return;
    }

    if (option == 1)
    {
        cout << result << endl;
    }
    else if (option == 2)
    {

        output_file << result << endl;
        cout << "arquivo salvo!!" << endl;
    }
    cout << "=========================================================================================================" << endl;
}

//<arquivo_entrada> <arquivo_saida> <Opc_Direc> <Opc_Peso_Aresta> <Opc_Peso_Nos>,
int main(int argc, char *argv[])
{
    cout << endl
         << "--------------------------------------------------------------------------------------------------" << endl
         << endl;

    string arquivo_entrada = argv[1];
    ifstream input_file(arquivo_entrada);
    if (!input_file.is_open())
    {
        std::cerr << "Não foi possível abrir o arquivo de entrada: " << arquivo_entrada << std::endl;
        return 1;
    }

    std::ofstream output_file;
    output_file.open(argv[2], std::ios::out | std::ios::app);

    bool digrafo = false;
    bool ponderado = false;
    bool pesoNo = false;

    switch (argc)
    {
    case 4:
        digrafo = (*argv[3] == '1') ? true : false;
        break;
    case 5:
        digrafo = (*argv[3] == '1') ? true : false;
        ponderado = (*argv[4] == '1') ? true : false;
        break;
    case 6:
        digrafo = (*argv[3] == '1') ? true : false;
        ponderado = (*argv[4] == '1') ? true : false;
        pesoNo = (*argv[5] == '1') ? true : false;
        break;
    default:
        break;
    }

    int no_origem, no_destino;
    int ordem;
    int peso;
    int peso2;
    input_file >> ordem;

    Grafo *g = new Grafo(digrafo, ponderado, ordem, pesoNo);

    while (!ponderado && input_file >> no_origem >> no_destino)
    {
        g->insereAresta(no_origem, no_destino, 1);
    }
    while (ponderado && !pesoNo && input_file >> no_origem >> no_destino >> peso)
    {
        g->insereAresta(no_origem, no_destino, peso);
    }
    while (pesoNo && !ponderado && input_file >> no_origem >> no_destino >> peso)
    {
        g->insereAresta(no_origem, no_destino, peso);
    }
    while (pesoNo && ponderado && input_file >> no_origem >> no_destino >> peso >> peso2)
    {
        g->insereAresta(no_origem, no_destino, peso, peso2);
    }

    //================================================================================================================
    // FUNCIONALIDADES
    //================================================================================================================

    bool quit = false;

    /*
    2[x] Fecho transitivo direto de um vértice.
    3[x] Fecho transitivo indireto de um vértice.
    4[x] Caminho mínimo entre dois vértices usando algoritmo de Dijkstra.
    5[x] Caminho mínimo entre dois vértices usando algoritmo de Floyd.
    6[x] Árvore Geradora Mínima usando o algoritmo de Prim.
    7[x] Árvore Geradora Mínima usando o algoritmo de Kruskal.
    8 Árvore de caminhamento em profundidade a partir de um nó, destacando as arestas de retorno.
    9[x] Ordenação topológica ou indicação de que o grafo não é acíclico direcionado.
    10[x]Raio, diâmetro, centro e periferia do grafo ponderado nas arestas.
    11[x] Conjunto de vértices de articulação.
    [x]Cada saída deve ser apresentada na tela e o usuário poderá optar por salvar a saída em arquivo.
    */
    while (!quit)
    {
        int option;
        cout << endl
             << "Funcionalidades:" << endl;
        cout << "|1| Imprimir Grafo." << endl;
        cout << "|2| Fecho transitivo direto." << endl;
        cout << "|3| Fecho transitivo indireto." << endl;
        cout << "|4| Caminho minimo por Dijkstra." << endl;
        cout << "|5| Caminho minimo por Floyd." << endl;
        cout << "|6| Arvore Geradora por Prim" << endl;
        cout << "|7| Arvore Geradora por Kruskal." << endl;
        cout << "|| Arvore de caminhamento em profundidade destacando aresta de retorno." << endl;
        cout << "|9| Possui ordenação topologica ou e é acíclico direcionado?" << endl;
        cout << "|10| Raio, diâmetro, centro e periferia do grafo." << endl;
        cout << "|11| Conjunto de vértices de articulação." << endl;
        cout << "|0| Sair das funcionalidades." << endl;
        cout << "Insira a opcao: ";
        cin >> option;
        cout << endl
             << endl;

        switch (option)
        {
        case 0:
            quit = true;
            break;
        default:
            execFunc(g, option, output_file, digrafo, ponderado);
            break;
        }
    }

    g->~Grafo();
    input_file.close();
    output_file.close();

    return 0;
}
