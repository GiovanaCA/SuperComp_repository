#!/bin/bash
#SBATCH --job-name=openmp             # Nome do job
#SBATCH --output=openmp_%j.txt          # Nome do arquivo de saída
#SBATCH --ntasks=4                              # Número de tarefas 
#SBATCH --cpus-per-task=2                       # Número de threads por tarefa 
#SBATCH --mem=1024                               # Memória total alocada por nó
#SBATCH --time=00:20:00                         # Tempo máximo de execução
#SBATCH --partition=espec                      # fila do cluster a ser utilizada

./threads_openmp1
