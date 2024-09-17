#include <thrust/device_vector.h>
#include <thrust/reduce.h>
#include <iostream>

int main() {
    // Criando um vetor na GPU com 5 elementos: {10, 20, 30, 40, 50}
    thrust::device_vector<int> vec_gpu(5);
    thrust::sequence(vec_gpu.begin(), vec_gpu.end(), 10, 10);

    // Calculando a soma dos elementos
    int soma = thrust::reduce(vec_gpu.begin(), vec_gpu.end(), 0, thrust::plus<int>());

    std::cout << "Soma dos elementos: " << soma << std::endl; // Saída: 150

    return 0;
}
