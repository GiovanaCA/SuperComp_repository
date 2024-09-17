#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <iostream>

int main() {
    // Criando vetores de preços na GPU
    thrust::device_vector<double> AAPL(5, 150.0);  // Exemplo com preço fixo
    thrust::device_vector<double> MSFT(5, 140.0);  // Exemplo com preço fixo
    thrust::device_vector<double> diff(5);         // Para armazenar as diferenças

    // Calculando a diferença ponto a ponto entre os preços
    thrust::transform(AAPL.begin(), AAPL.end(), MSFT.begin(), diff.begin(), thrust::minus<double>());

    // Exibindo as diferenças
    for (int i = 0; i < diff.size(); i++) {
        std::cout << "Diferença " << i << ": " << diff[i] << std::endl;
    }

    return 0;
}
