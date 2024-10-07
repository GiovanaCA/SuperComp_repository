#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/transform_reduce.h>
#include <thrust/iterator/constant_iterator.h>
#include <thrust/extrema.h>
#include <thrust/transform.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <thrust/count.h>
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {
    int n = 3112;
    double value = 0.0;
    thrust::host_vector<double> host(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> value;
        host[i] = value;
    }
    thrust::device_vector<double> dev(host);


    // CALCULO DA VARIANCIA USANDO ITERADORES DINAMICOS

    auto inicio_leitura = chrono::steady_clock::now();
    double total_sum = thrust::reduce(dev.begin(), dev.end(), 0.0, thrust::plus<double>());
    double mean_price = total_sum / n;
    thrust::constant_iterator<double> mean_iter(mean_price);
    auto variance_functor = [mean_price] __host__ __device__ (double x) { return (x-mean_price) * (x-mean_price); };
    double variance = thrust::transform_reduce( dev.begin(), dev.end(), variance_functor, 0.0, thrust::plus<double>() ) / n;
    cout << "Variância dos preços das ações nos últimos 10 anos: " << variance << endl;
    auto fim_leitura = chrono::steady_clock::now();
    duration<double> diff = fim_leitura - inicio_leitura;
    cout << "Tempo do cálculo da variância (em segundos):  " << diff.count() << endl << endl;

    // ANALISE DA VARIACAO DIARIA DOS PRECOS DAS ACOES

    inicio_leitura = chrono::steady_clock::now();
    thrust::device_vector<double> ganho_diario(n-1);
    auto difference_functor = [] __host__ __device__ (double x1, double x2) { return x1 - x2; };
    thrust::transform(dev.begin(), dev.end()-1, dev.begin()+1, ganho_diario.begin(), difference_functor);
    cout << "Mostrando o ganho diário dos primeiros 20 dias:" << endl;
    for (int i = 0; i < 20; i++) { cout << "Ganho diário: " << ganho_diario[i] << endl; }
    fim_leitura = chrono::steady_clock::now();
    diff = fim_leitura - inicio_leitura;
    cout << "Tempo da análise da variação diária dos preços (em segundos):  " << diff.count() << endl << endl;

    // CONTAGEM DE DIAS COM AUMENTO NO PRECO DAS ACOES

    inicio_leitura = chrono::steady_clock::now();
    int dias_ganho = thrust::count_if(ganho_diario.begin(), ganho_diario.end(), [] __host__ __device__ (double x) { return x > 0; });
    cout << "Contagem de dias com ganho: " << dias_ganho << endl;
    fim_leitura = chrono::steady_clock::now();
    diff = fim_leitura - inicio_leitura;
    cout << "Tempo do cálculo da contagem de dias com aumento no preço (em segundos):  " << diff.count() << endl << endl;

    // CALCULO DO AUMENTO MEDIO NOS DIAS EM QUE O PRECO SUBIU

    inicio_leitura = chrono::steady_clock::now();
    thrust::replace_if(ganho_diario.begin(), ganho_diario.end(), [] __host__ __device__ (double x) { return x < 0; }, 0);
    double ganho_total = thrust::reduce(ganho_diario.begin(), ganho_diario.end(), 0.0, thrust::plus<double>());
    double aumento_medio = ganho_total / dias_ganho;
    cout << "Aumento médio nos dias que o preço subiu: " << aumento_medio << endl;
    fim_leitura = chrono::steady_clock::now();
    diff = fim_leitura - inicio_leitura;
    cout << "Tempo do cálculo do aumento médio nos dias que o preço subiu (em segundos):  " << diff.count() << endl;

    return 0;
}