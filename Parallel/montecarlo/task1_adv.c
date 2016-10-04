#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREADS 12
#define NUM_DOTS 1000000
#define PI 3.14159265

void* count_points(void* _iters){
	int i;
	int* iters = (int*)_iters;
	double* res = (double*)malloc(sizeof(double));
	unsigned int seed = time(NULL);
	for (i = 0; i < *iters; ++i){
		double x = (double)(rand_r(&seed) % 314) / 100;
		double y = (double)(rand_r(&seed) % 100) / 100;
		if (y <= sin(x))
			*res += x*y;
	}
	pthread_exit((void*)res);
}

int main(int argc, char* argv[]){
	int i;
	double num_points = 0;
	pthread_t pthrs[NUM_THREADS];
	int iters = NUM_DOTS/NUM_THREADS;
	for (i = 0; i < NUM_THREADS; ++i){
		pthread_create(&pthrs[i], NULL, count_points, (void*)&iters);
	}
	for (i = 0; i < NUM_THREADS; ++i){
		void* tmp;
		pthread_join(pthrs[i], &tmp);
		num_points += *((double*)tmp);
		free(tmp);
	}
	double res = (PI/NUM_DOTS)*num_points;
        printf("%f \n", res);
        printf("%f, \n", PI*PI/8);

	return 0;
}
