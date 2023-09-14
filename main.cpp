#include <iostream>
#include <fstream>
#include <string>
#include "src/Grafo.cpp"

using namespace std;

int main(int argc, char* argv[]) {

    Grafo g = new Grafo(false);
    
    cout<<g.getPedro();

    // Nome do arquivo que você deseja ler
    string nomeArquivo = argv[1];

    // Abrir o arquivo
    ifstream arquivo("./instancias_grafos_n_ponderados/" + nomeArquivo);

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return 1;
    }

    string linha;
    string value;

    // Loop para ler todas as linhas do arquivo
    while (getline(arquivo, linha)) {
        // Processar a linha aqui, você pode imprimir ou fazer qualquer outra coisa
        cout<< linha << endl;
        break;
    }

    // Fechar o arquivo
    arquivo.close();

    return 0;
}
