#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <cstdlib>
#include <iostream>
using namespace std;


struct square
{
    __host__ __device__
    float operator()(const float& x) const {
        return x * x;
    }
};


int main(){
    const int N = 1000;
    thrust::host_vector<float> h_v(N);
    for (int i = 0; i < N; ++i) {
        h_v[i] = rand() % 10;
    }

    thrust::device_vector<float> d_v = h_v;
    thrust::transform(d_v.begin(), d_v.end(), d_v.begin(), square());
    thrust::host_vector<float> h_result = d_v;
    
    for (int i = 0; i < 10; ++i) {
        cout << "Resultado [" << i << "]: " << h_result[i] << endl;
    }
    return 0;
}
