#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include <omp.h>
#include <mutex>

using namespace std;

vector<vector<int> > LerGrafo(const string& nomeArquivo, int& numVertices) {
    ifstream arquivo(nomeArquivo);
    int numArestas;
    arquivo >> numVertices >> numArestas;
    vector<vector<int> > grafo(numVertices, vector<int>(numVertices, 0));
    for (int i = 0; i < numArestas; ++i) {
        int u, v;
        arquivo >> u >> v;
        grafo[u - 1][v - 1] = 1;
        grafo[v - 1][u - 1] = 1;
    }
    arquivo.close();
    return grafo;
}

bool VerificaClique(const vector<vector<int> >& grafo, const vector<int>& clique) {
    for (int i = 0; i < clique.size(); i++) {
        for (int j = i + 1; j < clique.size(); j++) {
            if (grafo[clique[i]][clique[j]] == 0) { return false; }
        }
    }
    return true;
}

void EncontrarCliqueMaxima(const vector<vector<int> >& grafo, int numVertices, vector<int>& cliqueMaxima) {
    vector<int> cliqueGlobal;
    mutex mtx;  // Protege o acesso ao clique máximo global

    #pragma omp parallel
    {
        vector<int> cliqueLocal;  // Clique máximo de cada thread
        vector<int> atualClique;

        // Função recursiva para construir cliques
        auto backtrack = [&](int v, auto& backtrack_ref) -> void {
            if (atualClique.size() > cliqueLocal.size()) { cliqueLocal = atualClique; }

            for (int i = v; i < numVertices; i++) {
                atualClique.push_back(i);
                if (VerificaClique(grafo, atualClique)) { backtrack_ref(i + 1, backtrack_ref); }
                atualClique.pop_back();
            }
        };

        #pragma omp for schedule(dynamic)
        for (int i = 0; i < numVertices; i++) {
            atualClique.clear();
            atualClique.push_back(i);
            backtrack(i + 1, backtrack);
        }

        // Atualiza o clique máximo global
        mtx.lock();
        if (cliqueLocal.size() > cliqueGlobal.size()) { cliqueGlobal = cliqueLocal; }
        mtx.unlock();
    }
    cliqueMaxima = cliqueGlobal;
}

int main() {
    int numVertices = 136;
    vector<vector<int> > grafo = LerGrafo("grafo.txt", numVertices);
    vector<int> cliqueMaxima;
    double start = omp_get_wtime();
    EncontrarCliqueMaxima(grafo, numVertices, cliqueMaxima);
    double end = omp_get_wtime();

    cout << "Clique máxima arquivo saída: ";
    for (int i = 0; i < cliqueMaxima.size(); i++) { cout << cliqueMaxima[i] + 1 << " "; }
    cout << endl;

    cout << "Tempo de execução: " << (end - start) << " segundos" << endl;
    return 0;
}
