// Crie um programa que peça ao usuário para inserir uma matriz 3x3
// e depois exiba a soma dos elementos na diagonal principal.

#include <iostream>
#include <vector>
using namespace std;

int main() {
    
    // pedindo 9 digitos
    cout << "Insira 9 numeros: ";
    int num;
    vector<vector<int>> matrix(3,vector<int>(3));
    
    // adicionando digitos na matrix 3x3
    for (size_t j = 0; j < 3; j++){
        for (size_t k = 0; k < 3; k++){
            cin >> num;
            matrix[j][k] = num;
        }
    }

    // realizando a soma dos elementos da diagonal principal
    int soma = 0;
    for (size_t i = 0; i < matrix.size(); ++i) { soma += matrix[i][i]; }
    
    // retornando resultado
    cout << soma << endl;
    return 0;
}
