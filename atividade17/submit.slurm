#!/bin/bash
#SBATCH --job-name=ex
#SBATCH --output=ex1_%j.txt
#SBATCH --ntasks=4
#SBATCH --mem=1024
#SBATCH --cpus-per-task=1
#SBATCH --time=00:05:00


mpirun ./ex1