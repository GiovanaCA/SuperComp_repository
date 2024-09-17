#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/extrema.h>
#include <iostream>
#include <chrono>
using namespace std;

int main() {
    std::chrono::duration<double> diff;

    // Leitura
    auto leitura_i = std::chrono::steady_clock::now();
    thrust::host_vector<double> host(3112, 0);
    for (int i = 0; i < 3112; i++) {
        cin >> host[i];
    }
    auto leitura_f = std::chrono::steady_clock::now();
    diff = leitura_f - leitura_i;
    cout << "Tempo de LEITURA (em segundos)  " << diff.count() << endl;

    // Copia
    auto copia_i = std::chrono::steady_clock::now();
    thrust::device_vector<double> dev(host);
    auto copia_f = std::chrono::steady_clock::now();
    diff = copia_f - copia_i;
    cout << "Tempo de CÓPIA (em segundos)  " << diff.count() << endl;


    // Calculando o preço médio dos últimos 10 anos
    double soma = thrust::reduce(dev.begin(), dev.end(), 0.0, thrust::plus<double>());
    double preco_medio = soma / 3112;
    cout << "Preço médio 10 anos: " << preco_medio << endl;

    // Calculando o preço médio dos últimos 365 dias
    thrust::device_vector<double> dev_ano(dev.end() - 365, dev.end());
    double ano_soma = thrust::reduce(dev_ano.begin(), dev_ano.end(), 0.0, thrust::plus<double>());
    double ano_media = ano_soma / 365;
    cout << "Preço médio 365 dias: " << ano_media << endl;

    // Encontrando o maior e o menor preço no período total de 10 anos
    auto min_max_total = thrust::minmax_element(dev.begin(), dev.end());
    cout << "Menor preço 10 anos: " << *min_max_total.first << endl;
    cout << "Maior preço 10 anos: " << *min_max_total.second << endl;

    // Encontrando o maior e o menor preço nos últimos 365 dias
    auto min_max_ano = thrust::minmax_element(dev_ano.begin(), dev_ano.end());
    cout << "Menor preço 365 dias: " << *min_max_ano.first << endl;
    cout << "Maior preço 365 dias: " << *min_max_ano.second << endl;

    return 0;
}
