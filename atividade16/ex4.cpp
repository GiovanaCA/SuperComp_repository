#include <iostream>
#include <cmath>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv){
    int rank, size, type = 99;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int array[100];
    int chunk_size = 100 / size;
    int recv_array[chunk_size];
    double media_local = 0.0, variacao_local = 0.0, media_global = 0.0, variacao_global = 0.0;


    if (rank == 0) {
        int soma = 0;
        for (int i = 0; i < 100; i++) { array[i] = rand() % 20; }
    }

    MPI_Scatter(array, chunk_size, MPI_INT, recv_array, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < chunk_size; i++) { media_local += recv_array[i]; }
    media_local /= chunk_size;
    for (int i = 0; i < chunk_size; i++) { variacao_local += pow(recv_array[i] - media_local, 2); }
    variacao_local /= chunk_size;

    double medias[size], variacoes[size];
    MPI_Gather(&media_local, 1, MPI_DOUBLE, medias, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Gather(&variacao_local, 1, MPI_DOUBLE, variacoes, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < size; i++) { media_global += medias[i]; }
        media_global /= size;
        for (int i = 0; i < size; i++) { variacao_global += variacoes[i] + pow(medias[i] - media_global, 2); }
        variacao_global /= size;
        double desvio_padrao_global = sqrt(variacao_global);
        cout << "Média global: " << media_global << endl;
        cout << "Desvio padrão global: " << desvio_padrao_global << endl;
    }

    MPI_Finalize();

    return 0;
}