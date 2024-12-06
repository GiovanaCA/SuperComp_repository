#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <mpi.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<vector<int>> LerGrafo(const string &nomeArquivo, int &numVertices) {
    ifstream arquivo(nomeArquivo);
    int numArestas;
    arquivo >> numVertices >> numArestas;
    vector<vector<int>> grafo(numVertices, vector<int>(numVertices, 0));
    for (int i = 0; i < numArestas; ++i) {
        int u, v;
        arquivo >> u >> v;
        grafo[u - 1][v - 1] = 1;
        grafo[v - 1][u - 1] = 1;
    }
    arquivo.close();
    return grafo;
}

bool VerificaClique(const vector<vector<int>> &grafo, const vector<int> &clique) {
    for (int i = 0; i < clique.size(); i++) {
        for (int j = i + 1; j < clique.size(); j++) {
            if (grafo[clique[i]][clique[j]] == 0) { return false; }
        }
    }
    return true;
}

void EncontrarCliquesLocais(const vector<vector<int>>& grafo, const vector<int>& vertices_Iniciais, vector<vector<int>>& cliques_Locais) {
    vector<int> atualClique;

    auto backtrack = [&](int v, auto& backtrack_ref) -> void {
        // Salva o clique atual como uma solução válida
        if (!atualClique.empty()) { cliques_Locais.push_back(atualClique); }
        for (int i = v; i < grafo.size(); i++) {
            // Verifica se o vértice pode ser adicionado ao clique atual
            bool adiciona = true;
            for (int u : atualClique) {
                if (grafo[u][i] == 0) { // Não é clique
                    adiciona = false;
                    break;
                }
            }
            if (adiciona) {
                atualClique.push_back(i);
                backtrack_ref(i + 1, backtrack_ref);
                atualClique.pop_back();
            }
        }
    };
    // Pra cada vértice inicial, inicia a busca de cliques
    for (int vInicial : vertices_Iniciais) {
        atualClique.clear();
        atualClique.push_back(vInicial);
        backtrack(vInicial + 1, backtrack);
    }
}

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    high_resolution_clock::time_point inicio, fim;

    int numVertices = 0;
    vector<vector<int>> grafo;

    if (rank == 0) {
        grafo = LerGrafo("grafo1.txt", numVertices);
        
        inicio = high_resolution_clock::now();
        
        // Enviando numVertices para os processos
        for (int i = 1; i < size; i++) { MPI_Send(&numVertices, 1, MPI_INT, i, 0, MPI_COMM_WORLD); }

        // Enviado o grafo para os processos
        for (int i = 1; i < size; i++) {
            for (int j = 0; j < numVertices; j++) { MPI_Send(grafo[j].data(), numVertices, MPI_INT, i, 0, MPI_COMM_WORLD); }
        }
    } else {
        // Receber o numVertices do processo raiz
        MPI_Recv(&numVertices, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        grafo.resize(numVertices, vector<int>(numVertices));
        // Receber o grafo do processo raiz
        for (int j = 0; j < numVertices; j++) { MPI_Recv(grafo[j].data(), numVertices, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); }
    }

    // Dividir
    vector<int> verticesIniciais;
    for (int i = rank; i < numVertices; i += size) { verticesIniciais.push_back(i); }

    // Cada processo executa a busca de cliques
    vector<vector<int>> Locais;
    EncontrarCliquesLocais(grafo, verticesIniciais, Locais);

    if (rank == 0) {
        vector<vector<int>> Cliques;
        Cliques.insert(Cliques.end(), Locais.begin(), Locais.end());

        for (int i = 1; i < size; i++) {
            int tam;
            MPI_Recv(&tam, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            vector<int> recebidos(tam);
            MPI_Recv(recebidos.data(), tam, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (int k = 0; k < tam; k) {
                int tamClique = recebidos[k++];
                vector<int> clique;
                for (int j = 0; j < tamClique; j++) { clique.push_back(recebidos[k++]); }
                Cliques.push_back(clique);
            }
        }
        
        size_t maior = 0;
        for (const auto& clique : Cliques) {
            if (clique.size() > maior) { maior = clique.size(); }  // Maior tamanho de clique
        }
        
        vector<int> cliquesMax;
        for (const auto& clique : Cliques) { // Primeira clique de maior tamanho encontrada
            if (clique.size() == maior) { cliquesMax = clique; }
        }

        fim = high_resolution_clock::now();
        duration<double> duracao = duration_cast<duration<double>>(fim - inicio);

        cout << "Clique máxima arquivo saída: ";
        for (int m = 0; m < cliquesMax.size(); m++) { cout << cliquesMax[m]+1 << " "; }
        cout << endl;
        cout << "Tempo de execução: " << duracao.count() << " segundos" << endl;
    }
    else {
        vector<int> enviar;
        for (const auto& clique : Locais) {
            enviar.push_back(clique.size());
            enviar.insert(enviar.end(), clique.begin(), clique.end());
        }

        // Enviar o tamanho e os dados
        int tam = enviar.size();
        MPI_Send(&tam, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(enviar.data(), tam, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
