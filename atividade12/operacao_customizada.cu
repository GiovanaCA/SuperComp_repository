#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <cstdlib> // Para rand()
#include <iostream>
using namespace std;

struct saxpy
{
    int a;    
    saxpy(int a_) : a(a_) {}  // Inicializa a constante a

    __host__ __device__
    double operator()(const int& x, const int& y) const {
        return a * x + y;  // Aplica a fórmula a * x + y
    }
};

int main() {
    const int N = 1000;

    thrust::host_vector<int> h_a(N);
    thrust::host_vector<int> h_b(N);
    
    for (int i = 0; i < N; ++i) {
        h_a[i] = rand() % 100;
        h_b[i] = rand() % 100;
    }

    thrust::device_vector<int> d_a = h_a;
    thrust::device_vector<int> d_b = h_b;
    thrust::device_vector<double> d_c(N);

    int a = 5;

    thrust::transform(d_a.begin(), d_a.end(), d_b.begin(), d_c.begin(), saxpy(a));

    thrust::host_vector<double> h_c = d_c;

    for (int i = 0; i < 10; ++i) { cout << "Resultado [" << i << "]: " << h_c[i] << endl;
    }

    return 0;
}
