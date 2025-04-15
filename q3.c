#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <float.h>
#include "conj_grad.h"

#define MAT_ITER 3

int main(){
	int N = 1;	

	for (int k=0; k<MAT_ITER; k++){
		N *= 10;
	
		long long int size = N;
		printf("size*size = %lld\n", size*size);
		double* A = calloc(size*size, sizeof(double));
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
		//double stop_crit = fmax(reltol * norm(size, r), abstol);
		double stop_crit = 1e-2;
		printf("Stopping criterion = %.17lf\n", stop_crit);
 		int num_iter;

		double* residuals = malloc(MAX_ITER*size * sizeof(double));
		conjugate_gradient_saveres(size, A, b, u, stop_crit, u, &num_iter, residuals);
	
		char filename[100];
		sprintf(filename, "writeup/q3out%d.txt", N);	
		FILE *fp = fopen(filename, "w");
        for (int j=0; j<num_iter; j++){
        	for (int i=0; i<size; i++){
            	fprintf(fp, "%.17lf ", residuals[j*size + i]);
			}
 	    	fprintf(fp, "\n");
		}
		fclose(fp);

		free(A);
		free(u);
		free(b);
		free(r);
		free(residuals);
	}
}

