#!/bin/bash
#SBATCH --job-name=convolucao_alterar             # Nome do job
#SBATCH --output=alterar_%j.txt          # Nome do arquivo de saída
#SBATCH --ntasks=8                              # Número de tarefas 
#SBATCH --cpus-per-task=8                       # Número de threads por tarefa 
#SBATCH --mem=8000                               # Memória total alocada por nó (1024 MB = 1 GB)
#SBATCH --time=00:10:00                         # Tempo máximo de execução (10 minutos)
#SBATCH --partition=espec                      # fila do cluster a ser utilizada

# Exporta a variável de ambiente para configurar o número de threads OpenMP
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK


# Executa o programa usando MPI e OpenMP
mpirun ./convolucao