// Crie um programa que peça ao usuário para inserir dois números e uma operação
// (adição, subtração, multiplicação ou divisão). O programa deve exibir o resultado
// da operação

#include <iostream>
using namespace std;

int main(){
    
    // pedindo os digitos e operacao
    cout << "Insira um digito, uma operacao (+, -, *, /) e mais um dígito: ";
    int x, y;
    string z;
    cin >> x >> z >> y;
    float result = x;

    // realizando as operacoes com dados inseridos
    if (z == "+"){ result += y; }
    else if (z == "-") { result -= y; }
    else if (z == "/"){ result /= y; }
    else if (z == "*") { result *= y; }
    
    // retornando o resultado
    cout << result << endl;
    
    return 0;
}