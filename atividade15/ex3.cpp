#include <iostream>
#include <cstring>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv){
    char message[20];
    int i, rank, size, type = 99;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        strcpy(message, "Exercicio 3 feito");
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 1, type, MPI_COMM_WORLD);
    } else {
        MPI_Recv(message, 50, MPI_CHAR, rank - 1, type, MPI_COMM_WORLD, &status);
        if (rank == size - 1) { cout << "Processo " << rank << " recebeu: " << message << endl; }
        else { MPI_Send(message, strlen(message) + 1, MPI_CHAR, rank + 1, type, MPI_COMM_WORLD); }
    }
    
    MPI_Finalize();

    return 0;
}