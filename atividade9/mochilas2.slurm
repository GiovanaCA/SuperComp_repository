#!/bin/bash
#SBATCH --job-name=mochilas2             # Nome do job
#SBATCH --output=mochilas2_%j.txt          # Nome do arquivo de saída
#SBATCH --ntasks=1                              # Número de tarefas 
#SBATCH --cpus-per-task=1                       # Número de threads por tarefa 
#SBATCH --mem=1024                               # Memória total alocada por nó (1024 MB = 1 GB)
#SBATCH --time=00:20:00                         # Tempo máximo de execução (10 minutos)
#SBATCH --partition=espec                      # fila do cluster a ser utilizada

# Alterar arquivos de entrada
./mochilas2 < "Entrada_caro_melhor.txt"