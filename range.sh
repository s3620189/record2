#!/usr/bin/env bash

#SBATCH -N 1
#SBATCH --time=01:00:00
#SBATCH --mem=100MB

echo "sum,matrix_size,num_threads,timer"

for (( i=0; i<32; i=i+1 ))
do
    ./diagonal 1000 $i
done
