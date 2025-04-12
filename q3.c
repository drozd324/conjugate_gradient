#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <float.h>
#include "conj_grad.h"

#define GRID_PTS 4

int main(){
	
	int num = 1;
	int N;	

	for (int k=0; k<GRID_PTS; k++){
		printf("iter k=%d\n", k);
		num *= 10;
		N = num;
	
		int size = N;
		printf("size thing = %d\n", size*size);
		double* A = calloc(size * size, sizeof(double));
		double* u = calloc(size, sizeof(double));
		double* b = calloc(size, sizeof(double));
		double* r = calloc(size, sizeof(double));
	
		for (int i=0; i<N; i++){
			for (int j=0; j<N; j++){
				A[i*size + j] = (N - fabs((double)(i - j))) / N;
			}
		}

		for (int j=0; j<size; j++){
			b[j] = 1;
		}
		
		// computes initial residual	
		mat_mul(A, u, r, size, size, 1);
		vect_sum(size, b, -1, r, r);
	
		double reltol = sqrt(DBL_EPSILON);
		double abstol = 0;
		double stop_crit = fmax(reltol * norm(size, r), abstol);
 		int num_iter;
		double** residuals = malloc(MAX_ITER * sizeof(double*));
		for (int i=0; i<MAX_ITER; i++){
			residuals[i] = malloc(size * sizeof(double));
		}

		conjugate_gradient_saveres(size, A, b, u, stop_crit, u, &num_iter, residuals);
		
		char filename[50];
		sprintf(filename, "writeup/q3out%d.txt", num);	
		FILE *fp = fopen(filename, "w");
		// saves residual to file
        for (int j=0; j<num_iter; j++){
        	for (int i=0; i<size; i++){
            	fprintf(fp, "%lf ", residuals[j][i]);
			}
            fprintf(fp, "\n");
        }
		fclose(fp);
		
		for (int i=0; i<MAX_ITER; i++){
			free(residuals[i]);
		}

		free(A);
		free(u);
		free(b);
		free(r);
		free(residuals);
	}
}

