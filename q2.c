#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "conj_grad.h"

double f(double x1, double x2){
	return 2 * M_PI * M_PI * sin(M_PI * x1) * sin(M_PI * x2);  
}
	
void print_mat(int n, double* A){
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			printf("%lf, ", A[i*n + j]);
		}
		printf("\n");
	}
}

/**
 * @brief Function to measure time
 *
 * @param[out] Actual time in seconds
 */
double walltime(){
    struct timeval t;
    gettimeofday(&t, NULL);
    double wtime = (double) (t.tv_sec + t.tv_usec*1e-6);
    return wtime;
}


#define GRID_PTS 2
#define EPS 1e-8

int main(){
	
	int N[GRID_PTS];
	int num = 4;
	
	FILE *fp = fopen("q2_out.csv", "w");
	fprintf(fp, "N,time,num_iter\n");
	
	for (int k=0; k<GRID_PTS; k++){
		num *= 2;
		N[k] = num;

		int size = N[k]*N[k];
		double* A = calloc(size * size, sizeof(double));
		double* u = calloc(size, sizeof(double));
		double* b = calloc(size, sizeof(double));

		for (int i=0; i<size; ++i){
			A[i*size + i] =  4.0;
		}
		for (int i=0; i<size-1; ++i){
			if ((i % N[k]) != N[k]-1){
				A[(i+1)*size + i+0] = 1.0;
				A[(i+0)*size + i+1] = 1.0;	
				//printf("%d\n", i);
			}
		}
		for (int i=0; i<size-N[k]; ++i){
			A[(i+N[k])*size + i+0] = 1.0;
			A[(i+0)*size    + i+N[k]] = 1.0;
		}
		
		for (int i=0; i<N[k]; i++){
			for (int j=0; j<N[k]; j++){
				b[i*N[k] + j] = f((double)i/N[k], (double)j/N[k]);
			}
		}
		
		//print_mat(size, A);	
	
		int num_iter;
		double t1 = walltime();
		conjugate_gradient(size, A, b, u, EPS, u, &num_iter);
		double time = walltime() - t1;
		
		free(A);
		free(u);
		free(b);

		fprintf(fp, "%d,%lf,%d\n", N[k], time, num_iter);
	}
	fclose(fp);
}

