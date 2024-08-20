// Escreva um programa que leia um arquivo de texto e calcule as seguintes estatísticas:
// número total de palavras, número total de linhas, número médio de palavras por linha e a
// palavra mais frequente. Em seguida, grave essas estatísticas em um novo arquivo de texto.

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main(){

    // abrindo arquivos de entrada e saida
    ifstream arquivo("arquivo.txt");
    ofstream estatisticas("estatisticas.txt");
    string line;
    
    // criando variaveis de estatistica
    int num_linhas = 0, num_palavras = 0, max_freq = 0;
    float num_med_palavra_linha = 0;
    vector<string> palavras_freqs;

    // criando dicionario para contar frequencia que as palavras aparecem
    map<string, size_t> contagem;

    // obtendo linhas
    while (getline(arquivo, line)){
        num_linhas++; // adicionando numero de linhas
        istringstream ss(line);
        string palavra;
        while(ss >> palavra) { // enquanto estiver obtendo strings
            num_palavras++; // adicionando numero de palavras
            transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower); // transformando em lowercase
            contagem[palavra]++; // adicionando ao dicionario e acrescentando frequencia
        }
    }
    
    // calculando numero medio de palavras por linha
    if (num_palavras > 0 && num_linhas > 0){ num_med_palavra_linha = (float) num_palavras / (float) num_linhas; }

    // obtendo maxima frequencia
    for(auto mapa = contagem.begin(); mapa != contagem.end(); ++mapa) {
        if (mapa->second > max_freq) { max_freq = mapa->second; }
    }

    // adicionando palavras mais frequentes (com a mesma maxima frequencia)
    for(auto mapa = contagem.begin(); mapa != contagem.end(); ++mapa) {
        if (mapa->second == max_freq) { palavras_freqs.push_back(mapa->first); }
    }

    // adicionando estatisticas ao arquivo de saida
    estatisticas << "Numero total de palavras: " << num_palavras << endl;
    estatisticas << "Numero total de linhas: " << num_linhas << endl;
    estatisticas << "Numero medio de palavras por linha: " << num_med_palavra_linha << endl;
    estatisticas << "Palavras mais frequentes: ";
    
    // adicionando palavras mais frequentes
    for (size_t i = 0; i < palavras_freqs.size(); i++){ estatisticas << palavras_freqs[i] << " "; }
    
    // fechando arquivos de entrada e saida
    arquivo.close();
    estatisticas.close();

    return 0;
}