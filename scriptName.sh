#!/bin/bash
#
#SBATCH --job-name=helloMPI       # Job name
#SBATCH --ntasks=${SLURM_NTASKS:-1}  # Number of MPI ranks (overridable by sbatch -n)
#SBATCH --time=01:00:00           # Walltime (HH:MM:SS)
#SBATCH --partition=standard      # Queue/partition name
#SBATCH --output=helloMPI_%j.out  # STDOUT output file (%j expands to jobID)
#SBATCH --error=helloMPI_%j.err   # STDERR output file

# Load Intel compilers and MPI
module load compilers/intel/2019u5
module load mpi/intel-mpi/2019u5/bin

# Determine number of MPI tasks
numMPI=${SLURM_NTASKS:-1}

# Compile the MPI programme
mpiicc helloMPI.c -o helloMPI.exe

# Run with the requested number of processes
mpirun -np ${numMPI} ./helloMPI.exe
