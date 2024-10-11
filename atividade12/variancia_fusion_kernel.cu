#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/transform_reduce.h>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;

struct variance_op
{
    float mean;
    variance_op(float mean_) : mean(mean_) {}

    __host__ __device__
    float operator()(const float& x) const {
        float diff = x - mean;
        return diff * diff;
    }
};

struct variance_fusion_op
{
    __host__ __device__
    thrust::pair<float, float> operator()(const float& x) const {
        return thrust::make_pair(x, x * x);  // Retorna (x, x^2)
    }
};

float calculate_mean(const thrust::device_vector<float>& d_vec) { return thrust::reduce(d_vec.begin(), d_vec.end(), 0.0f, thrust::plus<float>()) / d_vec.size(); }

float calculate_variance(const thrust::device_vector<float>& d_vec, float mean) {
    return thrust::transform_reduce(d_vec.begin(), d_vec.end(), variance_op(mean), 0.0f, thrust::plus<float>()) / d_vec.size();
}

float calculate_variance_fusion(const thrust::device_vector<float>& d_vec) {
    thrust::pair<float, float> result = thrust::transform_reduce(d_vec.begin(), d_vec.end(), variance_fusion_op(), thrust::make_pair(0.0f, 0.0f),
          [] __host__ __device__ (const thrust::pair<float, float>& a, const thrust::pair<float, float>& b) {
        return thrust::make_pair(a.first + b.first, a.second + b.second);  // Soma de (x, x^2)
    });

    float mean = result.first / d_vec.size();
    float mean_of_squares = result.second / d_vec.size();
    return mean_of_squares - mean * mean;
}

int main(){
    const int N = 1000000;
    thrust::host_vector<float> h_v(N);

    for (int i = 0; i < N; ++i) { h_v[i] = rand() % 10; }

    thrust::device_vector<float> d_v = h_v;

    auto start = chrono::high_resolution_clock::now();
    float mean = calculate_mean(d_v);
    float variance_traditional = calculate_variance(d_v, mean);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration_traditional = end - start;

    start = chrono::high_resolution_clock::now();
    float variance_fusion = calculate_variance_fusion(d_v);
    end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration_fusion = end - start;

    cout << "Variância tradicional: " << variance_traditional << endl;
    cout << "Tempo variância tradicional: " << duration_traditional.count() << " segundos" << endl;

    cout << "Variância com Fusion Kernel: " << variance_fusion << endl;
    cout << "Tempo variância Fusion Kernel: " << duration_fusion.count() << " segundos" << endl;

    return 0;
}
