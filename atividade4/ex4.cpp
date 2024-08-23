#include <iostream>
#include <vector>
using namespace std;

class Vector {
public:
    Vector(int tamanho);
    ~Vector();
    void inicializa(int valor);
    int get(int index) const;
    void set(int index, int valor);
    void inserir(int index, int valor);
    void remover(int index);
    void imprime() const;
    void multiplicar(int escalar);

private:
    int* dados;
    int tam;
    int capacidade;
    void redimensiona(int novaCapacidade);
};

// Implementação das funções...

Vector::Vector(int tamanho) : tam(tamanho), capacidade(tamanho), dados(new int[tamanho]) {}
Vector::~Vector() { delete[] dados; }
void Vector::inicializa(int valor) {
    for (int i = 0; i < tam; ++i) { dados[i] = valor; }
}
inline int Vector::get(int index) const {
    if (index >= 0 && index < tam) { return dados[index]; }
    else { 
        cerr << "nao tem esse index" << endl;
        return -1;
    }
}
inline void Vector::set(int index, int valor) {
    if (index >= 0 && index < tam) { dados[index] = valor; }
    else {
        cerr << "nao tem esse index" << endl;
    }
}
void Vector::inserir(int index, int valor) {
    if (index < 0 || index > tam) { cerr << "nao tem esse index" << endl; }
    else {
        if (tam >= capacidade) { redimensiona(capacidade*2); }
        for (int i = tam; i > index; i--) { dados[i] = dados[i-1]; }
        dados[index] = valor;
        tam++;
    }
}
void Vector::remover(int index) {
    if (index >= 0 && index < tam) {
        for (int i = index; i < tam; i++) { dados[i] = dados[i+1]; }
        tam--;
    }
    else { cerr << "nao tem esse index" << endl; }
}
void Vector::imprime() const {
    for (size_t i = 0; i < tam; i++) { cout << dados[i] << " "; }
    cout << endl;
}
void Vector::redimensiona(int novaCapacidade) {
    int* novo = new int[novaCapacidade];
    for (int i = 0; i < tam; i++) { novo[i] = dados[i]; }
    delete[] dados;
    dados = novo;
    capacidade = novaCapacidade;
}

void Vector::multiplicar(int escalar) {
    for (int i = 0; i < tam; i++) { dados[i] = dados[i] * escalar; }
}

int main() {
    Vector vec(5);
    vec.inicializa(0);
    vec.imprime();

    vec.set(2, 10);
    vec.imprime();

    vec.inserir(2, 20);
    vec.imprime();

    vec.remover(1);
    vec.imprime();

    vec.multiplicar(2);
    vec.imprime();

    return 0;
}