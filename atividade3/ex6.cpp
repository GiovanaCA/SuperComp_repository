// Escreva um programa que peça ao usuário para inserir 10
// números em um vetor e determine qual é o maior número

#include <iostream>
#include <vector>
using namespace std;

int main(){

    // pedindo 10 digitos
    cout << "Insira 10 numeros: ";
    int num, maior;
    vector<int> vec;

    // inserindo digitos no vetor
    for (int i = 0; i < 10; i++){
        cin >> num;
        vec.push_back(num);
    }

    // comparando valores do vetor para obter o maior numero
    maior = vec[0];
    for (size_t j = 0; j < vec.size(); j++){ if (vec[j] > maior){ maior = vec[j]; } }

    // retornando resultado
    cout << maior << endl;
    return 0;
}