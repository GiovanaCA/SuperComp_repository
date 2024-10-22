#include <iostream>
#include <random>
#include <cmath>
#include <chrono>
using namespace std;
using namespace std::chrono;


int main() {
    const int N = 100000;
    int sum = 0;
    double x, y;

    mt19937 generator(chrono::system_clock::now().time_since_epoch().count()); 
    uniform_real_distribution<double> distribution(0.0, 1.0);

    auto inicio = high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        x = distribution(generator);
        y = distribution(generator);
        if (x * x + y * y <= 1.0) { sum++; }
    }

    auto fim = high_resolution_clock::now();
    double pi = 4.0 * static_cast<double>(sum) / N;

    duration<double> duracao = fim - inicio;
    double exec_time = duracao.count();

    cout << "Estimativa de Pi = " << pi << endl;
    cout << "Tempo de execução = " << exec_time << " segundos" << endl;

    return 0;
}