#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>  // Adicionada para std::function

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
    vector<int> atualClique;

    // Função recursiva para construir cliques
    auto backtrack = [&](int v, auto& backtrack_ref) -> void {
        // Atualiza se encontrar um clique maior
        if (atualClique.size() > cliqueMaxima.size()) { cliqueMaxima = atualClique; }

        for (int i = v; i < numVertices; i++) {
            atualClique.push_back(i);
            if (VerificaClique(grafo, atualClique)) { backtrack_ref(i + 1, backtrack_ref); }
            atualClique.pop_back();
        }
    };

    backtrack(0, backtrack);  // Inicia com o primeiro vértice
}

int main() {
    int numVertices = 100;
    vector<vector<int> > grafo = LerGrafo("grafo_teste.txt", numVertices);
    vector<int> cliqueMaxima;
    EncontrarCliqueMaxima(grafo, numVertices, cliqueMaxima);
    cout << "Clique máxima arquivo saída: ";
    for(int i = 0; i < cliqueMaxima.size(); i++){ cout << cliqueMaxima[i] + 1 << " "; }
    cout << endl;
    return 0;
}