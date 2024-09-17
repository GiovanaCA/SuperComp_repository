#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    thrust::device_vector<double> AAPL(3520, 0.0);
    thrust::device_vector<double> MSFT(3520, 0.0);
    thrust::device_vector<double> diff(3520);

    string line;
    double value1 = 0.0, value2 = 0.0;
    for (int i = 0; i < 3520; i++) {
        getline(cin, line);
        stringstream ss(line);
        string temp;
        getline(ss, temp, ',');
        value1 = stod(temp);
        getline(ss, temp, ',');
        value2 = stod(temp);
        AAPL[i] = value1;
        MSFT[i] = value2;
    }

    thrust::transform(AAPL.begin(), AAPL.end(), MSFT.begin(), diff.begin(), thrust::minus<double>());

    double soma = thrust::reduce(diff.begin(), diff.end(), 0.0, thrust::plus<double>());
    double media = soma / 3520;
    cout << "Média das diferenças: " << media << endl;

    return 0;
}
