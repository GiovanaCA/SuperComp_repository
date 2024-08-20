// Implemente o algoritmo de ordenação Bubble Sort
// para organizar um vetor de números em ordem crescente.

#include <iostream>
#include <vector>
using namespace std;

int main(){

    // pedindo digitos
    cout << "Insira numeros para o vetor, quando desejar parar de inserir numeros, digite uma letra (ex: 1 9 4 3 6 7 j): ";
    int num, mudar;
    bool trocado;
    vector<int> vec;

    // inserindo digitos no vetor
    while(true){
        cin >> num;
        if (cin.fail()) { break; }
        vec.push_back(num);
    }

    // percorrendo vetor
    for (int i = 0; i < vec.size()-1; i++) {
        trocado = false;
        // comparando valores do vetor com os adjacentes
        for (int j = 0; j < vec.size()-i-1; j++) {
            if (vec[j] > vec[j+1]) { // caso maior, realizar a troca
                mudar = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = mudar;
                trocado = true;
            }
        }
        if (!trocado) { break; } // se nenhum foi trocado, vetor esta em ordem crescente
    }

    // retornando resultado
    for (size_t k = 0; k < vec.size(); k++){ cout << vec[k]; }
    cout << endl;

    return 0;
}