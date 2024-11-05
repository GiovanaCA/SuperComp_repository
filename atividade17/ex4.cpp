#include <iostream>
#include <vector>
#include <mpi.h>
#include <omp.h>

using namespace std;

int main(int argc, char *argv[]) {
    int rank, size;
    const int N = 100;
    const int target = 3;
    vector<int> data(N);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (int i = 0; i < N; i++) { data[i] = i % 5; }
    }

    int chunk_size = N / size;
    vector<int> local_data(chunk_size);
    MPI_Scatter(data.data(), chunk_size, MPI_INT, local_data.data(), chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    
    vector<int> local_positions;
    #pragma omp parallel for
    for (int i = 0; i < chunk_size; i++) {
        if (local_data[i] == target) {
            #pragma omp critical
            local_positions.push_back(i+rank*chunk_size);
        }
    }

    int local_count = local_positions.size();
    vector<int> counts(size);
    MPI_Gather(&local_count, 1, MPI_INT, counts.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

    vector<int> displs(size, 0);
    int total_positions = 0;
    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            displs[i] = total_positions;
            total_positions += counts[i];
        }
    }

    vector<int> all_positions(total_positions);
    MPI_Gatherv(local_positions.data(), local_count, MPI_INT, all_positions.data(), counts.data(), displs.data(), MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Vetor:" << endl;
        for (int j = 0; j < N; j++) { cout << data[j] << " "; }
        cout << "\nPosições do valor " << target << " encontradas: ";
        for (int k = 0; k < total_positions; k++) { cout << all_positions[k] << " "; }
        cout << endl;
    }

    MPI_Finalize();

    return 0;
}