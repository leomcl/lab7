#!/bin/bash

# Lo d Intel compilers and MPI
module load compilers/intel/2019u5
module load mpi/intel-mpi/2019u5/bin

# At run‐time SLURM_NTASKS will be set to what you passed via `-n`
numMPI=${SLURM NTASKS:-1}

# Compile the MPI programme
mpiicc helloMPI.c

# Launch exactly that many ranks
mpirun -np $numMPI ./helloMPI.exe
