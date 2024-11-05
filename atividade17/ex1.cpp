#include <iostream>
#include <mpi.h>
#include <omp.h>
using namespace std;

int main(int argc, char *argv[]) {
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 500;
    int data[N][N];

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) { data[i][j] = i + j; }
        }
    }

    int chunk_size = N / size;
    int local_data[chunk_size][N];

    double start_time = MPI_Wtime();

    double scatter_start = MPI_Wtime();
    MPI_Scatter(data, chunk_size * N, MPI_INT, local_data, chunk_size * N, MPI_INT, 0, MPI_COMM_WORLD);
    double scatter_end = MPI_Wtime();

    double compute_start = MPI_Wtime();

    for (int i = 0; i < chunk_size; i++) {
        for (int j = 0; j < N; j++) { local_data[i][j] *= local_data[i][j]; }
    }
    double compute_end = MPI_Wtime();

    double gather_start = MPI_Wtime();
    MPI_Gather(local_data, chunk_size * N, MPI_INT, data, chunk_size * N, MPI_INT, 0, MPI_COMM_WORLD);
    double gather_end = MPI_Wtime();

    double end_time = MPI_Wtime();

    if (rank == 0) {
        cout << "Matriz resultante:" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) { cout << data[i][j] << " "; }
            cout << endl;
        }
        cout << "\nN tamanho: " << N << endl;
        cout << "Tempo total: " << end_time - start_time << " segundos" << endl;
        cout << "Tempo MPI_Scatter: " << scatter_end - scatter_start << " segundos" << endl;
        cout << "Tempo computação sequencial: " << compute_end - compute_start << " segundos" << endl;
        cout << "Tempo MPI_Gather: " << gather_end - gather_start << " segundos" << endl;
    }

    MPI_Finalize();

    return 0;
}