#!/bin/bash
#SBATCH --job-name=vetor_insert_test
#SBATCH --output=vetor_insert_%j.txt
#SBATCH --ntasks=1
#SBATCH --mem=1024
#SBATCH --cpus-per-task=4
#SBATCH --time=00:05:00


./vetor_insert