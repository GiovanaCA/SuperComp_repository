#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/transform_reduce.h>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;

struct square
{
    __host__ __device__
    double operator()(const double& x) const {
        return x * x;
    }
};

double magnitude_gpu(thrust::device_vector<double>& v) {
    double sum_of_squares = thrust::transform_reduce(v.begin(), v.end(), square(), 0.0f, thrust::plus<double>());
    return std::sqrt(sum_of_squares);
}

double magnitude_cpu(const std::vector<double>& v) {
    double sum_of_squares = 0.0f;
    for (size_t i = 0; i < v.size(); ++i) {
        sum_of_squares += v[i] * v[i];
    }
    return std::sqrt(sum_of_squares);
}

int main() {
    const int N = 1000000;  // Tamanho do vetor
    thrust::host_vector<double> h_v(N);

    for (int i = 0; i < N; ++i) { h_v[i] = static_cast<double>(rand() % 10); }

    thrust::device_vector<double> d_v = h_v;

    // Conversão para std::vector para a implementação na CPU
    std::vector<double> v_cpu(h_v.begin(), h_v.end());

    auto start_gpu = chrono::high_resolution_clock::now();
    double result_gpu = magnitude_gpu(d_v);
    auto end_gpu = chrono::high_resolution_clock::now();
    chrono::duration<double> duration_gpu = end_gpu - start_gpu;

    auto start_cpu = chrono::high_resolution_clock::now();
    double result_cpu = magnitude_cpu(v_cpu);
    auto end_cpu = chrono::high_resolution_clock::now();
    chrono::duration<double> duration_cpu = end_cpu - start_cpu;

    cout << "Magnitude GPU: " << result_gpu << endl;
    cout << "Tempo GPU: " << duration_gpu.count() << " segundos" << endl;

    cout << "Magnitude CPU: " << result_cpu << endl;
    cout << "Tempo CPU: " << duration_cpu.count() << " segundos" << endl;

    return 0;
}
