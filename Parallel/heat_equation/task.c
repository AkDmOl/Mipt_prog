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
const double u_r = 80.0;
const double u_l = 30.0;
const double tau = 0.1;
double aux_width = 50; //0.5:0.01 = 50
double aux_height = 50;

int num_process = 0;
int rank = 0;
MPI_Status status;

size_t chunk = 0;
size_t i, j, t;

void calc_V(double** U, double** V){
	double* boundary = (double*)malloc(aux_height * sizeof(double));

	for(i = 1; i < chunk - 1; ++i){
		for(j = 0; j < aux_height; ++j){
			V[i][j] = U[i][j] + k*tau*(U[i+1][j] - 2*U[i][j] + U[i-1][j]);
		}
	}
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
		MPI_Sendrecv(U[0], aux_height, MPI_DOUBLE, rank - 1, 2,
				boundary, aux_height, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, &status);
		for (j = 0; j < aux_height; ++j)
			V[0][j] = U[0][j] + k*tau*(U[1][j] - 2*U[0][j] + boundary[j]);

		if (rank != num_process - 1){
			size_t ids = chunk - 1;
			MPI_Sendrecv(U[ids], aux_height, MPI_DOUBLE, rank + 1, 1,
					boundary, aux_height, MPI_DOUBLE, rank + 1, 2, MPI_COMM_WORLD, &status);
			for (j = 0; j < aux_height; ++j)
				V[ids][j] = U[ids][j] + k*tau*(boundary[j] - 2*U[ids][j] + U[ids - 1][j]);
		}
	}	
	free(boundary);
}


void update(double** U){
	double** V;
	size_t i,j;
	V = (double**)malloc(chunk * sizeof(double*));
	for(i = 0; i < chunk; ++i)
		V[i] = (double*)malloc(aux_height * sizeof(double));
	calc_V(U, V);

	if (rank == 0)
		for (i = 0; i < aux_height; ++i)		
			U[0][i] = u_l;
	if (rank == num_process - 1)
		for (i = 0; i < aux_height; ++i)
			U[chunk - 1][i] = u_r;

	for (i = 1; i < chunk - 1; ++i)
		for (j = 0; j < aux_height; ++j){
				double tmp_up = ((j == aux_height - 1) ? 0.0 : V[i][j+1]);
				double tmp_down = ((j == 0) ? 0.0 : V[i][j-1]);
				U[i][j] = V[i][j] + k*tau*(tmp_down - 2*V[i][j] + tmp_up); 
		}
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
	//proc 0 init Py-values, because he create graph
	if (rank == 0)
		if (argc >= 3){
			Py_Initialize();
			PyRun_SimpleString("import sys"); 
			PyRun_SimpleString("sys.path.append('....')");
			pName = PyString_FromString(argv[1]);
			pModule = PyImport_Import(pName);
			pDict = PyModule_GetDict(pModule);
			pFunc = PyDict_GetItemString(pDict, argv[2]);	
		}
	//Results temperature
	double *Res = (double*)malloc(aux_width * sizeof(double*));
	for (i = 0; i < aux_width; ++i)
		Res[i] = 0.0;
	//distribute work-size for everyone process
	if (rank != num_process - 1) chunk = aux_width / num_process;
	else chunk = aux_width / num_process + aux_width - (aux_width / num_process) * num_process;
	//temperature table
	double **U = (double**)malloc(chunk * sizeof(double*));
	for (i = 0; i < chunk; ++i)
		U[i] = (double*)malloc(aux_height * sizeof(double));
	//init values
	for (i = 0; i < chunk; ++i)
		for (j = 0; j < aux_height; ++j)
			U[i][j] = u_0;	
	//t - time of distrib temperature
	double t = 0.0;
	while(t < 60.0){
		update(U);	
		t += tau;
	}
	//proc 0 gets final temperature values from other process
	if (rank != 0)
		for (i = 0; i < chunk; ++i)
			MPI_Send(&U[i][25], 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
	if (rank == 0){
		for (i = 0; i < chunk; ++i)
			Res[i] = U[i][25];
		for (j = 1; j < num_process; ++j)
			for (i = 0; i < chunk; ++i)
				MPI_Recv(&Res[chunk*j+i], 1, MPI_DOUBLE, j, 1, MPI_COMM_WORLD, &status);
		//write values to file
		file = fopen("res.txt", "w");
		for (i = 1; i <= aux_width; ++i)		
			fprintf(file, "%.3f:%.1f\n", i*h - h/2, Res[i-1]);
		fclose(file);
		//call graphic() from graph.py
		if (PyCallable_Check(pFunc)){
			PyObject_CallObject(pFunc, NULL);
		}
	}
	//free memory
	for (i = 0; i < chunk; ++i)
		free(U[i]);
	free(U);
	Py_DECREF(pModule);
	Py_DECREF(pName);
	Py_Finalize();
	MPI_Finalize();
	return 0;
}
