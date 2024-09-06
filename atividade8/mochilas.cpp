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

void mochila_cheia(vector<item> itens, int W, vector<int>& melhor, vector<int>& tarefa) {
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
    tarefa.push_back(valorTotal);
    tarefa.push_back(pesoTotal);
}

void substituicao(vector<item>& itens, int W, vector<int>& melhor, vector<int>& tarefa) {
    mochila_cheia(itens, W, melhor, tarefa);
    bool melhorou = true;
    while (melhorou) {
        melhorou = false;
        int valorAtual = tarefa[0];
        int pesoAtual = tarefa[1];
        for (auto& it : itens) {
            if (find(melhor.begin(), melhor.end(), it.id) == melhor.end()) {
                for (int i = 0; i < melhor.size(); ++i) {
                    int idSubstituido = melhor[i];
                    int novoPeso = pesoAtual - itens[idSubstituido].peso + it.peso;
                    int novoValor = valorAtual - itens[idSubstituido].valor + it.valor;
                    if (novoPeso <= W && novoValor > valorAtual) {
                        melhor[i] = it.id;
                        tarefa[0] = novoValor;
                        tarefa[1] = novoPeso;
                        melhorou = true;
                        break;
                    }
                }
                if (melhorou) { break; }
            }
        }
    }
}

void hill_climbing(vector<item>& itens, int W, vector<int>& melhor, vector<int>& tarefa) {
    vector<int> solucaoAtual(itens.size(), 0);
    int pesoAtual = 0, valorAtual = 0;

    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<> dist(0, 1);
    for (int i = 0; i < itens.size(); ++i) {
        solucaoAtual[i] = dist(g);
        if (solucaoAtual[i] == 1) {
            if (pesoAtual + itens[i].peso <= W) {
                pesoAtual += itens[i].peso;
                valorAtual += itens[i].valor;
                melhor.push_back(itens[i].id);
            } else {
                solucaoAtual[i] = 0;
            }
        }
    }
    tarefa.push_back(valorAtual);
    tarefa.push_back(pesoAtual);

    bool melhorou = true;

    while (melhorou) {
        melhorou = false;
        vector<int> melhorVizinho = solucaoAtual;
        int melhorValor = valorAtual, melhorPeso = pesoAtual;
        for (int i = 0; i < itens.size(); ++i) {
            vector<int> vizinho = solucaoAtual;
            vizinho[i] = 1 - vizinho[i];
            int peso = 0, valor = 0;
            for (int i = 0; i < itens.size(); ++i) {
                if (vizinho[i] == 1) {
                    peso += itens[i].peso;
                    valor += itens[i].valor;
                }
            }
            auto [valorVizinho, pesoVizinho] = make_pair(valor, peso);
            if (pesoVizinho <= W && valorVizinho > melhorValor) {
                melhorVizinho = vizinho;
                melhorValor = valorVizinho;
                melhorPeso = pesoVizinho;
                melhorou = true;
            }
        }

        if (melhorou) {
            solucaoAtual = melhorVizinho;
            valorAtual = melhorValor;
            pesoAtual = melhorPeso;
            tarefa[0] = melhorValor;
            tarefa[1] = melhorPeso;
            melhor.clear();
            for (int i = 0; i < itens.size(); ++i) {
                if (solucaoAtual[i] == 1) { melhor.push_back(itens[i].id); }
            }
        }
    }
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
    substituicao(itens, W, melhor, tarefa);
    auto fim = high_resolution_clock::now();
    duration<double> duracao = fim - inicio;
    double exec_time = duracao.count();
    
    vector<int> melhorHC;
    vector<int> tarefaHC;
    inicio = high_resolution_clock::now();
    hill_climbing(itens, W, melhorHC, tarefaHC);
    fim = high_resolution_clock::now();
    duration<double> duracaoHC = fim - inicio;
    double exec_timeHC = duracaoHC.count();

    cout << "Substituicao - Tempo: " << exec_time << " s, Valor: " << tarefa[0] << ", Peso: " << tarefa[1] << endl;
    cout << "Itens: ";
    for (int id : melhor) { cout << id << " "; }
    cout << endl;

    cout << "Hill Climbing - Tempo: " << exec_timeHC << " s, Valor: " << tarefaHC[0] << ", Peso: " << tarefaHC[1] << endl;
    cout << "Itens: ";
    for (int id : melhorHC) { cout << id << " "; }
    cout << endl;

    return 0;
}