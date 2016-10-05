#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int sum(int* array, int size){
	return ((*array + *(array + size - 1))*size) / 2;
}


int main(int argc, char* argv[]){
	int i; int N = 0;
	int rank = 0; int num_proc = 0;
	int *array;
	MPI_Status status;

	N = atoi(argv[1]);

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	int results[num_proc - 1];
	int busket = N/(num_proc - 1);
	if (rank == 0){
		array = (int*)malloc(N * sizeof(int));
		for(i = 0; i < N; ++i)
			array[i] = i;
		for(i = 0; i < num_proc - 2; ++i)
			MPI_Send(array + i*busket, busket, MPI_INT, i+1, 1, MPI_COMM_WORLD);

		MPI_Send(array + (num_proc - 2)*busket, N - (num_proc - 2)*busket, MPI_INT, num_proc - 1, 1, MPI_COMM_WORLD);

		for (i = 0; i < num_proc - 1; ++i)
			MPI_Recv(&results[i], 1, MPI_INT, i+1, 1, MPI_COMM_WORLD, &status);
		for(i = 1; i < num_proc - 1; ++i){
			results[0] += results[i];
		//	printf("Sum by process %d : %d\n", i, results[i]);
		}
		printf("\n");
		int check_sum = sum(array, N);
		printf("Sum by processes %d\n Check sum %d\n", results[0], check_sum);	
		free(array);
	}
	if (rank != 0){
		int size = 0;
		if (rank != num_proc - 1)
			size = busket;
		else
			size = N - (num_proc - 2)*busket;
		array = (int*)malloc(size*sizeof(int));
		MPI_Recv(array, size, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		int res = sum(array, size);
	

		printf("Sum by process %d %d\n", rank, res);


		MPI_Send(&res, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		free(array);
	}

	MPI_Finalize();	
	return 0;
}
