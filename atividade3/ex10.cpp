// Crie um programa que simule um sistema de controle de estoque para uma loja.
// O programa deve permitir ao usuário adicionar itens, remover itens, e visualizar
// o estoque atual. Os dados devem ser armazenados em vetores.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(){

    // pedindo para o usuario escolher acao
    cout << "Bem vindo ao estoque da loja, qual acao voce deseja? Insira sua escolha" << endl;
    string opcao, item;
    vector<string> estoque = {"biquini", "havaianas", "canga", "boné"};

    // Enquanto estiver no sistema
    while (true) {

        // pede para inserir opcao
        cout << "adicionar, remover ou visualizar, sair: ";
        cin >> opcao;
        
        // executa as possiveis opcoes
        if (opcao == "adicionar"){ // se adicionar, adiciona ao vetor
            cin >> item;
            estoque.push_back(item);
        }
        else if (opcao == "remover"){ // se remover, remove do estoque
            cin >> item;
            estoque.erase(remove(estoque.begin(), estoque.end(), item), estoque.end()); 
        }
        else if (opcao == "visualizar"){ // se visualizar, mostrar itens do estoque
            for (size_t i = 0; i < estoque.size(); i++){ cout << estoque[i] << endl; }
        }
        else if (opcao == "sair"){ // se desejar sair do sistema, loop termina
            break;
        }
        
    }
    return 0;
}