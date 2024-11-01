#include <iostream>
#include <cstring>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv){
    int rank, size, type = 99;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int iteracoes;

    if (rank == 0) { iteracoes = 20; }
    
    MPI_Bcast(&iteracoes, 1, MPI_INT, 0, MPI_COMM_WORLD);
    cout << "Processo " << rank << " recebeu iteracoes = " << iteracoes << endl;

    MPI_Finalize();

    return 0;
}