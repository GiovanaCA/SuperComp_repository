#include <iostream>
#include <cstring>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv){
    char message[50];
    int i, rank, size, type = 99;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        for (int i = 1; i < size; i++){
            sprintf(message, "Aqui é o processo %d falando com o processo %d", rank, i);
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, i, type, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(message, 50, MPI_CHAR, 0, type, MPI_COMM_WORLD, &status);
        cout << "Processo " << rank << " recebeu: " << message << endl;
    }

    MPI_Finalize();

    return 0;
}