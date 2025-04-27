#!/bin/bash

# Lo d Intel compilers and MPI
module load compilers/intel/2019u5
module load mpi/intel-mpi/2019u5/bin

# At run‐time SLURM_NTASKS will be set to what you passed via `-n`
numMPI=${SLURM_NTASKS:-1}

# Compile the MPI programme
mpiicc -std=c99 quadMPI.c -o quadMPI.exe

# Launch exactly that many ranks
mpirun -np $numMPI ./quadMPI.exe
