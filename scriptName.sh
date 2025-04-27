#!/bin/bash
#
#SBATCH --job-name=helloMPI        # Job name
#SBATCH --ntasks=1                 # Default number of MPI ranks
#SBATCH --time=01:00:00            # Walltime (HH:MM:SS)
#SBATCH --partition=standard       # Partition/queue
#SBATCH --output=helloMPI_%j.out   # STDOUT: helloMPI_<jobID>.out
#SBATCH --error=helloMPI_%j.err    # STDERR: helloMPI_<jobID>.err

# Load Intel compilers and MPI
module load compilers/intel/2019u5
module load mpi/intel-mpi/2019u5/bin

# At run‐time SLURM_NTASKS will be set to what you passed via `-n`
numMPI=${SLURM NTASKS:-1}

# Compile the MPI programme
mpiicc helloMPI.c

# Launch exactly that many ranks
mpirun -np $numMPI ./helloMPI.exe
