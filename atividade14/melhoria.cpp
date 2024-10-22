#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <omp.h>
using namespace std;
using namespace std::chrono;


int main() {
    const int N = 100000;
    int sum = 0;

    auto inicio = high_resolution_clock::now();

    #pragma omp parallel reduction(+:sum)
    {
        mt19937 generator(chrono::system_clock::now().time_since_epoch().count() + omp_get_thread_num());
        uniform_real_distribution<double> distribution(0.0, 1.0);

        #pragma omp for
        for (int i = 0; i < N; ++i) {
            double x = distribution(generator);
            double y = distribution(generator);
            if (x * x + y * y <= 1.0) { sum++; }
        }
    }

    auto fim = high_resolution_clock::now();
    double pi = 4.0 * static_cast<double>(sum) / N;

    duration<double> duracao = fim - inicio;
    double exec_time = duracao.count();

    cout << "Estimativa de Pi = " << pi << endl;
    cout << "Tempo de execução = " << exec_time << " segundos" << endl;

    return 0;
}