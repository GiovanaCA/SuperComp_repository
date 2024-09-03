#!/bin/bash
#SBATCH --job-name=mochila2             # Nome do job
#SBATCH --output=mochila2_%j.txt          # Nome do arquivo de saída
#SBATCH --ntasks=1                              # Número de tarefas 
#SBATCH --cpus-per-task=1                       # Número de threads por tarefa 
#SBATCH --mem=1024                               # Memória total alocada por nó (1024 MB = 1 GB)
#SBATCH --time=03:00:00                         # Tempo máximo de execução (10 minutos)
#SBATCH --partition=espec                      # fila do cluster a ser utilizada

# Alterar arquivos de entrada
./mochila2 < "Entrada_3.txt"