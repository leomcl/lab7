#include <stdio.h>
#include <math.h>
#include <mpi.h>

/* prototype declarations */
double func(double x);
double approximateArea(int commSz, int myRank);
double integrationPTP(int commSz, int myRank);

int main(void) {
    const int REPEAT = 25;

    MPI_Init(NULL, NULL);

    /* TASK: Get the comm size and the rank number for each process. */
    int commSz, myRank;
    MPI_Comm_size(MPI_COMM_WORLD, &commSz);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    double tStart, tEnd;
    double result;

    for (int count = 0; count < REPEAT; count++) {
        tStart = MPI_Wtime();
        result = integrationPTP(commSz, myRank);
        tEnd = MPI_Wtime();

        /* only rank 0 prints the global result */
        if (myRank == 0) {
            printf("Result = %f\n", result);
            printf("COUNT = %d\n", count);
            printf("Time taken = %f milliseconds\n\n",
                   1000.0 * (tEnd - tStart));
        }
    }

    MPI_Finalize();
    return 0;
}

/*
 * TASK: create a function integrationPTP here which calls approximateArea
 *       for each rank.  In integrationPTP, after computing the local sum,
 *       every rank except 0 sends it to rank 0, and rank 0 receives them
 *       all, adds them up and returns the global integral.
 */
double integrationPTP(int commSz, int myRank) {
    double localSum = approximateArea(commSz, myRank);

    if (myRank == 0) {
        double totalSum = localSum;
        for (int src = 1; src < commSz; src++) {
            double tmp;
            MPI_Recv(&tmp, 1, MPI_DOUBLE, src, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            totalSum += tmp;
        }
        return totalSum;
    } else {
        MPI_Send(&localSum, 1, MPI_DOUBLE, 0, 0,
                 MPI_COMM_WORLD);
        return localSum;  /* value for non-zero ranks (not printed) */
    }
}

/*
 * TASK: modify this so each rank integrates only its slice of the interval
 */
double approximateArea(int commSz, int myRank) {
    const double a      = 0.0;
    const double b      = 200.0;
    const int    quads  = 50000000;
    double       width  = (b - a) / (double)quads;

    /* number of trapezoids per rank */
    int quadsPerRank = quads / commSz;

    /* start/end indices for this rank */
    int startIter = myRank * quadsPerRank;
    int endIter   = startIter + quadsPerRank - 1;

    /* last rank takes any leftover */
    if (myRank == commSz - 1) {
        endIter = quads - 1;
    }

    double sum = 0.0;
    for (int i = startIter; i <= endIter; i++) {
        double x = a + i * width;
        double y = x + width;
        sum += 0.5 * width * (func(x) + func(y));
    }
    return sum;
}

double func(double x) {
    return pow(x, 1.5) / 3.1 - x / log(3.0);
}
