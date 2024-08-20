// Escreva um programa que peça ao usuário para inserir
// uma string e exiba o número de caracteres na string.

#include <iostream>
#include <string>
using namespace std;

int main() {

    // pedindo para inserir uma string
    cout << "Insira uma string: ";
    string c;
    int contagem = 0;
    
    // recebendo a string
    cin >> c;

    // percorrendo a string e contando numero de caracteres
    for (int i = 0; c[i] != '\0'; i++) { contagem++; }

    // retornando resultado
    cout << contagem << endl;
    return 0;
}