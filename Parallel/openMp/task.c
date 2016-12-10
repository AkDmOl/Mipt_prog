#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <stdbool.h>

#define parts 1000
#define MAX_THREADS 3

double func(double x){
	return 1/(1+x*x);
}

int main(int argc, char* argv[]){
	FILE* file;
	file = fopen("res.txt", "w");

	bool reduction = false;
	if (argc == 2)
		if (strcmp(argv[1], "--reduction") == 0)
			reduction = true;

	double chunk = 1 / (double)parts;
	int i = 0;
	int j = 0;
	double begin, end, total;
	for (i = 1; i <= MAX_THREADS; ++i){
		double res = 0.0;
		begin = 0.0; end = 0.0; total = 0.0;
		omp_set_num_threads(i);
		if (reduction){
			begin = omp_get_wtime();
			#pragma omp parallel for reduction(+:res)
				for (j = 1; j < parts; ++j)
					res += func(j*chunk);
		}
		else{
			begin = omp_get_wtime();
			double aux_res;
			#pragma omp parallel private(aux_res) shared(res)
			{
				aux_res = 0.0;
				#pragma omp for
					for (j = 1; j < parts; ++j){
						aux_res += func(j*chunk);		
					}
					#pragma omp critical
					{
						res += aux_res;
					}
			}
		}
		res += (func(0) + func(1))/2;
		res *= 4*chunk;
		end = omp_get_wtime();
		total = end - begin;
		fprintf(file, "%.8f:%.4f:%d\n", total, res, i);
	}	
	return 0;
}
