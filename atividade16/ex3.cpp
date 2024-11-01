#include <iostream>
#include <algorithm>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv){
    int rank, size, type = 99;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double array[100];
    double valor_maximo;
    int chunk_size = 100 / size;
    double recv_array[chunk_size];
    double norm_array[100];

    if (rank == 0) {
        for (int i = 0; i < 100; i++) { array[i] = rand() % 20; }
        valor_maximo = *max_element(array, array + 100);
        cout << "O valor máximo é: " << valor_maximo << endl;
    }
    
    MPI_Bcast(&valor_maximo, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(array, chunk_size, MPI_DOUBLE, recv_array, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    double normalized_chunk[chunk_size];
    for (int j = 0; j < chunk_size; j++) { normalized_chunk[j] = recv_array[j] / valor_maximo; }
    MPI_Gather(normalized_chunk, chunk_size, MPI_DOUBLE, norm_array, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Array normalizado:" << endl;
        for (int k = 0; k < 100; k++) {
            cout << norm_array[k] << " ";
            if ((k + 1) % 10 == 0) cout << endl;
        }
    }

    MPI_Finalize();

    return 0;
}