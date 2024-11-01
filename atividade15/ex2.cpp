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

    if (size > 2) {
        if (rank == 0) {
            sprintf(message, "Aqui é o processo %d falando com o processo %d", rank, rank + 1);
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, rank + 1, type, MPI_COMM_WORLD);
            MPI_Recv(message, 50, MPI_CHAR, size - 1, type, MPI_COMM_WORLD, &status);
            cout << "Processo 0 recebeu: " << message << endl;
        } else {
            
            MPI_Recv(message, 50, MPI_CHAR, rank - 1, type, MPI_COMM_WORLD, &status);
            cout << "Processo " << rank << " recebeu: " << message << endl;
            
            if (rank < size - 1){
                sprintf(message, "Aqui é o processo %d falando com o processo %d", rank, rank + 1);
                MPI_Send(message, strlen(message) + 1, MPI_CHAR, rank + 1, type, MPI_COMM_WORLD);
            }
            if (rank == size-1) {
                sprintf(message, "Aqui é o processo %d falando com o processo 0", rank);
                MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, type, MPI_COMM_WORLD);
            }

        }
    } else { cout << "Número de processos deve ser maior que 2" << endl; }
    
    MPI_Finalize();

    return 0;
}