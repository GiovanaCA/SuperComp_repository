#!/bin/bash
#SBATCH --job-name=mpi                          # Nome do job
#SBATCH --output=mpi_%j.txt                     # Nome do arquivo de saída
#SBATCH --ntasks=4                              # Número de tarefas 
#SBATCH --mem=2048                               # Memória total alocada por nó
#SBATCH --time=00:20:00                         # Tempo máximo de execução
#SBATCH --partition=espec                      # fila do cluster a ser utilizada

mpirun ./MPI1
