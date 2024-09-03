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

void tarefa1(vector<item> itens, int W, vector<int>& melhor, vector<int>& tarefa_1) {
    random_device rd;
    mt19937 g(rd());
    shuffle(itens.begin(), itens.end(), g);
    
    int pesoTotal = 0, valorTotal = 0;
    for (auto& it : itens) {
        if (pesoTotal + it.peso <= W) {
            pesoTotal += it.peso;
            valorTotal += it.valor;
            melhor.push_back(it.id);
        }
    }
    tarefa_1.push_back(valorTotal);
    tarefa_1.push_back(pesoTotal);
}

void tarefa2(vector<item>& itens, int W, vector<int>& melhor, vector<int>& tarefa_2, double limiar = 0.5) {
    random_device rd;
    mt19937 g(rd());
    uniform_real_distribution<> dist(0.0, 1.0);
    
    int pesoTotal = 0, valorTotal = 0;
    for (auto& it : itens) {
        double prob = dist(g);
        if (prob > limiar && (pesoTotal + it.peso <= W)) {
            pesoTotal += it.peso;
            valorTotal += it.valor;
            melhor.push_back(it.id);
        }
    }
    tarefa_2.push_back(valorTotal);
    tarefa_2.push_back(pesoTotal);
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
  
    vector<int> melhorH1;
    vector<int> tarefa_1;
    auto inicio = high_resolution_clock::now();
    tarefa1(itens, W, melhorH1, tarefa_1);
    auto fim = high_resolution_clock::now();
    duration<double> duracaoH1 = fim - inicio;
    double exec_time_h1 = duracaoH1.count();

    vector<int> melhorH2;
    vector<int> tarefa_2;
    inicio = high_resolution_clock::now();
    tarefa2(itens, W, melhorH2, tarefa_2);
    fim = high_resolution_clock::now();
    duration<double> duracaoH2 = fim - inicio;
    double exec_time_h2 = duracaoH2.count();
    
    cout << "Heurística 1 - Tempo: " << exec_time_h1 << " s, Valor: " << tarefa_1[0] << ", Peso: " << tarefa_1[1] << endl;
    cout << "Itens: ";
    for (int id : melhorH1) { cout << id << " "; }
    cout << endl;
    
    cout << "Heurística 2 - Tempo: " << exec_time_h2 << " s, Valor: " << tarefa_2[0] << ", Peso: " << tarefa_2[1] << endl;
    cout << "Itens: ";
    for (int id : melhorH2) { cout << id << " "; }
    cout << endl;

    return 0;
}