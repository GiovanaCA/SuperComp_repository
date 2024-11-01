#include <iostream>
#include <cstring>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv){
    int i, rank, size, type = 99;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int soma = 0;

    if (rank == 0) {
        MPI_Send(&soma, 1, MPI_INT, 1, type, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&soma, 1, MPI_INT, rank-1, type, MPI_COMM_WORLD, &status);
        soma += rank;
        if (rank == size - 1) { cout << "Soma: " << soma << endl; }
        else { MPI_Send(&soma, 1, MPI_INT, rank+1, type, MPI_COMM_WORLD); }
    }
    
    MPI_Finalize();

    return 0;
}