// Crie um programa que solicite ao usuário para inserir 5 números
// em um vetor e depois exiba a soma desses números

#include <iostream>
#include <vector>
using namespace std;

int main(){

    // pedindo 5 digitos
    cout << "insira 5 numeros: ";
    int num, resultado = 0;
    vector<int> vec;
    
    // inserindo digitos no vetor
    for (int i = 0; i < 5; i++){
        cin >> num;
        vec.push_back(num);
    }

    // somando valores do vetor
    for (size_t j = 0; j < vec.size(); j++){ resultado += vec[j]; }

    // retornando resultado
    cout << resultado << endl;
    return 0;
}