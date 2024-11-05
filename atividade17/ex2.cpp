#include <iostream>
#include <mpi.h>
#include <omp.h>
using namespace std;

int main(int argc, char *argv[]) {
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 24;
    int data[N][N];

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) { data[i][j] = i + j; }
        }
    }

    int chunk_size = N / size;
    int local_data[chunk_size][N];
    MPI_Scatter(data, chunk_size * N, MPI_INT, local_data, chunk_size * N, MPI_INT, 0, MPI_COMM_WORLD);

    #pragma omp parallel for colapse(2)
    for (int i = 0; i < chunk_size; i++) {
        for (int j = 0; j < N; j++) { local_data[i][j] *= local_data[i][j]; }
    }

    cout << "Processo " << rank << " - Dados local_data após a computação:" << endl;
    cout << "Valor inicial: " << local_data[0][0] << endl;
    cout << "Valor final: " << local_data[chunk_size-1][N-1] << endl;

    MPI_Gather(local_data, chunk_size * N, MPI_INT, data, chunk_size * N, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) { cout << data[i][j] << " "; }
            cout << endl;
        }
        cout << "Tasks: 5" << endl;
        cout << "Nodes: 2" << endl; 
        cout << "Tasks per node: 3" << endl; 
    }

    

    MPI_Finalize();

    return 0;
}