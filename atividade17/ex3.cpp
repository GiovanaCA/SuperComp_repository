#include <iostream>
#include <vector>
#include <mpi.h>
#include <omp.h>
using namespace std;

int main(int argc, char *argv[]) {
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 100;
    vector<int> data(N);
 
    if (rank == 0) {
        for (int i = 0; i < N; i++) { data[i] = i + 1; }
    }

    int chunk_size = N / size;
    vector<int> local_data(chunk_size);

    MPI_Scatter(data.data(), chunk_size, MPI_INT, local_data.data(), chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    int local_sum = 0;
    #pragma omp parallel for reduction(+:local_sum)
    for (int i = 0; i < chunk_size; i++) { local_sum += local_data[i]; }

    vector<int> sums(size);  
    MPI_Gather(&local_sum, 1, MPI_INT, sums.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        int global_sum = 0;
        cout << "Vetor:" << endl;
        for (int j = 0; j < N; j++) { cout << data[j] << " "; }
        for (int i = 0; i < size; i++) { global_sum += sums[i]; }
        double media = static_cast<double> (global_sum) / N;
        cout << "\nMédia do array: " << media << endl;
    }

    MPI_Finalize();

    return 0;
}