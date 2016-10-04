#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <string.h>

#define PI 3.14159265
#define NUM_THREADS 12
#define NUM_DOTS 10000000

sem_t sem;
double num_points = 0.0;

void *count_points(void *_iters){
	int i;
	int* iters = (int*)_iters;
	double res = 0.0;
	unsigned int seed = time(NULL);
	for(i = 0; i < *iters; i++){	
		double x = (double)(rand_r(&seed) % 314) / 100;		//x in [0...PI]
		double y = (double)(rand_r(&seed) % 100) / 100;		//y in [0...1]
		if (y <= sin(x))
			res += x*y;
	}	

	sem_wait(&sem);
	num_points += res;
	sem_post(&sem);
	return NULL;
}

void reset(){
	num_points = 0.0;
}

int main(int argc, char* argv[])
{
	int i;
	char* filename = NULL;
	for (i = 1; i < argc; ++i)
		if(strcmp(argv[1], "-o") == 0 && argc > 2)
			filename = argv[2];
	
	if (!filename){
		printf("You should provide the name of the output file");
		return -1;
	}
	FILE* fd = fopen(filename, "w");
	if (!fd){
		printf("ERROR: Can't open file!");
		return -1;
	}


	sem_init(&sem, 0, 1);
	int j, rc;
	for (j = 1; j <= NUM_THREADS; ++j){
		//double start_time = clock();
		struct timespec begin, end;
		double elapsed;

		pthread_t pthrs[j];
		int iters = NUM_DOTS/j;

		clock_gettime(CLOCK_REALTIME, &begin);
		for  (i = 0; i < j; i++){
			rc = pthread_create(&pthrs[i], NULL, count_points, (void*)&iters);
			if (rc) printf("ERROR; return  code from pthread_create() is %d \n", rc);
		}
	
		for(i = 0; i < j; i++){
			rc = pthread_join(pthrs[i], NULL);
			if (rc) printf("ERROR; return code from pthread_join() is %d \n", rc);
		}
		if (j < NUM_THREADS)
			reset();

		clock_gettime(CLOCK_REALTIME, &end);
		elapsed = end.tv_sec - begin.tv_sec;
		elapsed += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
		//double end_time = clock() - start_time;
		fprintf(fd, "%d:%f \n", j, elapsed);
	}
	double res = (PI/NUM_DOTS)*num_points;
	printf("%f \n", res);
	printf("%f, \n", PI*PI/8);
	fclose(fd);
	sem_destroy(&sem);
	return 0;
}
