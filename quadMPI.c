#include<stdio.h>
#include<math.h>
#include<mpi.h>

double func(double);
double approximateArea();

int main(void){
	const int REPEAT = 25;
	
	MPI_Init(NULL, NULL);

	//TASK: Get the comm size and the rank number for each process.

	double tStart;
	double tEnd;
	
	int count = 0;

	double result;

	for(count; count < REPEAT; count++){
		
	
		tStart = MPI_Wtime();
		result = approximateArea();
    		//result = integrationPTP(commSz, myRank);
		tEnd = MPI_Wtime();

		//if (rank == 0){
			printf("Result = %f\n", result);
			printf("COUNT = %d\n", count);
			printf("Time taken = %f milliseconds\n", 1000.0*(tEnd - tStart));	//print wallTimeTaken
		//}
	}
	MPI_Finalize();
}

/*TASK: create a function integrationPTP here which calls approximateArea for each rank.
In intergrationPTP, after returning the local sum from approximateArea,...
...every rank, except 0, should send their data to rank 0...
...and rank 0 should add them all up together and return the result*/


double approximateArea(/*int commSz, int myRank*/){
	const double a=0.0, b=200.0;
	const int  quads = 50000000;
	double const width = (b-a) / (double) quads;
	
	//TASK: Include quadsPerRank, the number of quads to be for each rank
	//int quadsPerRank;

	//This is to be used for the final rank, if the number of quads is not divisible by the number of ranks
	//if(myRank == commSz - 1){	
	//	quadsPerRank = quads - (quadsPerRank*myRank);
	//}
	
	//TASK: Modify startIter and endIter to change based on the rank and quadsPerRank.
	int startIter = 0;
	int endIter = quads;
	
	double x, y;
    
	double sum;
	int i;

	for(i = startIter; i <= endIter; i++){
		x = a + i * width;
		y = x + width;
		sum += 0.5*width*(func(x) + func(y));
	}
	return sum;
}

double func(double x){
	return pow(x,1.5)/3.1 - x/log(3.0);
}

