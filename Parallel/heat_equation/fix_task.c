#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <python2.7/Python.h>

//initial values
const double k = 1.177749;
const double h = 0.01;
const double u_0 = 5.0;
const double height = 0.5;
const double width = 0.5;
const double u_r = 30.0;
const double u_l = 80.0;
const double tau = 0.1;
double aux_width = 50; //size_plate:h
double aux_height = 50;//height_plate:h

int num_process = 0;
int rank = 0;
MPI_Status status;

size_t chunk = 0;
size_t i, j, t;

//calculation auxiliary plate V
void calc_V(double** U, double** V){
	double* boundary = (double*)malloc(aux_height * sizeof(double));
	//general recurrence
	for(i = 1; i < chunk - 1; ++i){
		for(j = 0; j < aux_height; ++j){
			V[i][j] = U[i][j] + k*tau*(U[i+1][j] - 2*U[i][j] + U[i-1][j]);
		}
	}
	//interprocess communication
	if (rank % 2 == 0){
		if (rank != 0) {
			MPI_Sendrecv(U[0], aux_height, MPI_DOUBLE, rank - 1, 2,
				       	boundary, aux_height, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, &status);
			for (j = 0; j < aux_height; ++j)
				V[0][j] = U[0][j] + k*tau*(U[1][j] - 2*U[0][j] + boundary[j]);
		}
		if (rank != num_process - 1){ 
			size_t ids = chunk - 1;			
			MPI_Sendrecv(U[ids], aux_height, MPI_DOUBLE, rank + 1, 1,
					boundary, aux_height, MPI_DOUBLE, rank + 1, 2, MPI_COMM_WORLD, &status);
			for (j = 0; j < aux_height; ++j)
				V[ids][j] = U[ids][j] + k*tau*(boundary[j] - 2*U[ids][j] + U[ids - 1][j]);
		}
	}
	else{
		if (rank != num_process - 1){
			size_t ids = chunk - 1;
			MPI_Sendrecv(U[ids], aux_height, MPI_DOUBLE, rank + 1, 1,
					boundary, aux_height, MPI_DOUBLE, rank + 1, 2, MPI_COMM_WORLD, &status);
			for (j = 0; j < aux_height; ++j)
				V[ids][j] = U[ids][j] + k*tau*(boundary[j] - 2*U[ids][j] + U[ids - 1][j]);
		}

		MPI_Sendrecv(U[0], aux_height, MPI_DOUBLE, rank - 1, 2,
				boundary, aux_height, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, &status);
		for (j = 0; j < aux_height; ++j)
			V[0][j] = U[0][j] + k*tau*(U[1][j] - 2*U[0][j] + boundary[j]);
	}	
	free(boundary);
}

//update distribution temperature
void update(double** U){
	double** V;
	size_t i,j;
	V = (double**)malloc(chunk * sizeof(double*));
	for(i = 0; i < chunk; ++i)
		V[i] = (double*)malloc(aux_height * sizeof(double));
	calc_V(U, V);
	//general recurrence
	for (i = 0; i < chunk; ++i)
		for (j = 0; j < aux_height; ++j){
				double tmp_up = ((j == aux_height - 1) ? 0.0 : V[i][j+1]);
				double tmp_down = ((j == 0) ? 0.0 : V[i][j-1]);
				U[i][j] = V[i][j] + k*tau*(tmp_down - 2*V[i][j] + tmp_up); 
		}
	//init boundary values
	if (rank == 0)
		for (i = 0; i < aux_height; ++i)		
			U[0][i] = u_l;
	if (rank == num_process - 1)
		for (i = 0; i < aux_height; ++i)
			U[chunk - 1][i] = u_r;

	for(i = 0; i < chunk; ++i)
		free(V[i]);
	free(V);
}


int main(int argc, char* argv[]){
	FILE *file;
	//init value for MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &num_process);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//init value for python graph
	PyObject *pName, *pModule, *pDict, *pFunc, *pValue;
	if (rank == 0)
		if (argc >= 3){
			Py_Initialize();
			PyRun_SimpleString("import sys"); 
			PyRun_SimpleString("sys.path.append('/home/akdmol/Mipt_prog/Parallel/heat_equation/')");
			pName = PyString_FromString(argv[1]);
			pModule = PyImport_Import(pName);
			pDict = PyModule_GetDict(pModule);
			pFunc = PyDict_GetItemString(pDict, argv[2]);	
		}
	//resulting distribution temperature
	double *Res = (double*)malloc(aux_width * sizeof(double*));
	for (i = 0; i < aux_width; ++i)
		Res[i] = 0.0;
	//distrib work space
	size_t aux_chunk = aux_width / num_process;
	if (rank != num_process - 1) chunk = aux_chunk;
	else chunk = aux_chunk + (aux_width - aux_chunk*num_process);
	//pieces of distribution temperature
	double **U = (double**)malloc(chunk * sizeof(double*));
	for (i = 0; i < chunk; ++i)
		U[i] = (double*)malloc(aux_height * sizeof(double));
	//init values
	for (i = 0; i < chunk; ++i)
		for (j = 0; j < aux_height; ++j)
			U[i][j] = u_0;	
	//time 
	double t = 0.0;
	while(t < 60.0){
		update(U);	
		t += tau;
	}
	//proc 0 gets finish values of temperature from other processes
	if (rank != 0)
		for (i = 0; i < chunk; ++i)
			MPI_Send(&U[i][25], 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
	if (rank == 0){
		for (i = 0; i < chunk; ++i)
			Res[i] = U[i][25];
		for (j = 1; j < num_process; ++j)
			for (i = 0; i < chunk; ++i)
				MPI_Recv(&Res[chunk*j+i], 1, MPI_DOUBLE, j, 1, MPI_COMM_WORLD, &status);
		//recv from last proc
		size_t last_piece = (num_process - 1)*chunk + chunk;
		for (i = last_piece; i < aux_width; ++i)
			MPI_Recv(&Res[i], 1, MPI_DOUBLE, num_process - 1, 1, MPI_COMM_WORLD, &status);
		//write results to file
		file = fopen("res.txt", "w");
		for (i = 1; i <= aux_width; ++i)		
			fprintf(file, "%.3f:%.1f\n", i*h - h/2, Res[i-1]);
		fclose(file);
		//make graph of temperature
		if (PyCallable_Check(pFunc)){
			PyObject_CallObject(pFunc, NULL);
			//free resources
			Py_DECREF(pModule);
			Py_DECREF(pName);
		}
	}
	for (i = 0; i < chunk; ++i)
		free(U[i]);
	free(U);
	//final Py&MPI
	Py_Finalize();
	MPI_Finalize();
	return 0;
}
