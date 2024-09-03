#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

struct item {
    int id;
    int peso;
    int valor;
};

void combinacoes(vector<item>& itens, int W, int i, int peso, int valor, int &max, vector<int>& melhor, vector<int>& atual) {
    if (peso > W) { return; }
    if (i == itens.size()) {
        if (valor > max) {
            max = valor;
            melhor = atual;
        }
        return;
    }
    combinacoes(itens, W, i+1, peso, valor, max, melhor, atual);
    atual.push_back(itens[i].id);
    combinacoes(itens, W, i+1, peso+itens[i].peso, valor+itens[i].valor, max, melhor, atual);
    atual.pop_back();
}

int main() {
    string line;
    int N, W, num1, num2, id = 0, max = 0;
    vector<item> itens;

    auto inicio = high_resolution_clock::now();

    getline(cin, line);
    istringstream ss(line);
    ss >> N >> W;
    cout << "max. peso: " << W << endl;

    while (getline(cin, line)) {
        istringstream ss(line);
        ss >> num1 >> num2;
        item newItem;
        cout << id << ": peso-" << num1 << " valor-" << num2 << endl;
        newItem.id = id++;
        newItem.peso = num1;
        newItem.valor = num2;
        itens.push_back(newItem);
    }
    
    vector<int> melhor;
    vector<int> atual;
    combinacoes(itens, W, 0, 0, 0, max, melhor, atual);
    
    auto fim = high_resolution_clock::now();
    duration<double> duracao = fim - inicio;
    double exec_time = duracao.count();
    cout << "Tempo: " << exec_time << " s" << endl;

    cout << "Valor máximo: " << max << endl;
    cout << "Itens: ";
    for (int id : melhor) { cout << id << " "; }
    cout << endl;
    return 0;
}