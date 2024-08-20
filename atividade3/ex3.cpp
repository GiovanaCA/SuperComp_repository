// Escreva um programa que peça ao usuário para inserir um
// número e informe se ele é par ou ímpar

#include <iostream>
using namespace std;

int main(){

    // pedindo digito
    cout << "Insira um digito: ";
    int x;
    cin >> x;

    // analisando se possui, ou nao, resto 0 da divisao de 2
    if (x % 2 == 0){ cout << "É par" << endl; }
    else { cout << "É impar" << endl; }

    return 0;
}