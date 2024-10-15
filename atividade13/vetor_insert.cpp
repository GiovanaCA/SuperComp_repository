#include <vector>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <omp.h>
using namespace std;

double conta_complexa(int i) {
    return 2 * i;
}

int main() {
    int N = 10000; 
    vector<double> vec;

    double init_time, final_time;

    init_time = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        // Lidando com efeitos colaterais
        #pragma omp critical
        {
            vec.push_back(conta_complexa(i));
        }
    }
    final_time = omp_get_wtime() - init_time;
    cout << "Final time (omp critical) " << final_time << " secs\n";

    for (int i = 0; i < N; i++) {
        cout << vec[i] << " ";
    }

    cout << endl << endl;

    // Pré-alocação de memória
    vec.resize(N);
    init_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        vec[i] = conta_complexa(i);
    }
    final_time = omp_get_wtime() - init_time;
    cout << "Final time (omp parallel for) " << final_time << " secs\n";

    for (int i = 0; i < N; i++) {
        cout << vec[i] << " ";
    }

    return 0;
}