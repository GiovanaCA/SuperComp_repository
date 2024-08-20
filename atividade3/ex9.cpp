// Escreva um programa que verifique se uma string inserida pelo usuário é um
// palíndromo (lê-se da mesma forma de trás para frente).

#include <iostream>
#include <vector>
using namespace std;

int main(){
    
    // pedindo para inserir uma string
    cout << "Insira uma string: ";
    string c;
    vector<char> vec;
    
    // recebendo a string
    cin >> c;

    // percorrendo a string e acrescentando char ao vetor
    for (int i = 0; c[i] != '\0'; i++) {  vec.push_back(c[i]); }

    // percorre vetor, compara i e vec.size()-1-i
    for (size_t i = 0; i <= (vec.size())/2; i++){
        if (vec[i] != vec[(vec.size())-1-i]){
            cout << "Nao é palindromo" << endl;
            break;
        }
        if (i == (vec.size())/2){ cout << "É palindromo" << endl; }
    }
    return 0;
}