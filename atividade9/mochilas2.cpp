#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;
using namespace std::chrono;

struct item {
    int id;
    int peso;
    int valor;
};

void mais_caro(vector<item> itens, int W, vector<int>& melhor, vector<int>& tarefa1) {
    sort(itens.begin(), itens.end(), [](const item& a, const item& b) { return a.valor > b.valor; });
    int pesoTotal = 0, valorTotal = 0;
    for (auto& it : itens) {
        if (pesoTotal + it.peso <= W) {
            pesoTotal += it.peso;
            valorTotal += it.valor;
            melhor.push_back(it.id);
        }
    }
    tarefa1.push_back(valorTotal);
    tarefa1.push_back(pesoTotal);
}

void mais_leve(vector<item> itens, int W, vector<int>& melhor, vector<int>& tarefa2) {
    sort(itens.begin(), itens.end(), [](const item& a, const item& b) { return a.peso < b.peso; });
    int pesoTotal = 0, valorTotal = 0;
    for (auto& it : itens) {
        if (pesoTotal + it.peso <= W) {
            pesoTotal += it.peso;
            valorTotal += it.valor;
            melhor.push_back(it.id);
        }
    }
    tarefa2.push_back(valorTotal);
    tarefa2.push_back(pesoTotal);
}

int main() {
    string line;
    int N, W, num1, num2, id = 0, max = 0, peso = 0;
    vector<item> itens;

    getline(cin, line);
    istringstream ss(line);
    ss >> N >> W;
    cout << "max. peso: " << W << endl;

    while (getline(cin, line)) {
        istringstream ss(line);
        ss >> num1 >> num2;
        item newItem;
        newItem.id = id++;
        newItem.peso = num1;
        newItem.valor = num2;
        itens.push_back(newItem);
    }
  
    vector<int> melhor;
    vector<int> tarefa;
    auto inicio = high_resolution_clock::now();
    mais_caro(itens, W, melhor, tarefa);
    auto fim = high_resolution_clock::now();
    duration<double> duracao = fim - inicio;
    double exec_time = duracao.count();

    vector<int> melhorP;
    vector<int> tarefaP;
    inicio = high_resolution_clock::now();
    mais_leve(itens, W, melhorP, tarefaP);
    fim = high_resolution_clock::now();
    duration<double> duracaoP = fim - inicio;
    double exec_timeP = duracaoP.count();

    cout << "Mais caro - Tempo: " << exec_time << " s, Valor: " << tarefa[0] << ", Peso: " << tarefa[1] << endl;
    cout << "Itens: ";
    for (int id : melhor) { cout << id << " "; }
    cout << endl;

    cout << "Mais leve - Tempo: " << exec_timeP << " s, Valor: " << tarefaP[0] << ", Peso: " << tarefaP[1] << endl;
    cout << "Itens: ";
    for (int id : melhorP) { cout << id << " "; }
    cout << endl;

    return 0;
}