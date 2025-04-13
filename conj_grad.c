#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <omp.h>
#include "conj_grad.h"

double dot(int n, double* v, double* w){
	double sum = 0;
	#pragma omp parallel for reduction(+:sum)
	for (int i=0; i<n; i++){
		sum += v[i]*w[i];	
	}
	return sum;
}

void vect_sum(int n, double* v, double alpha, double* w, double* out){
	#pragma omp parallel for
	for (int i=0; i<n; i++){
		out[i] = v[i] + alpha*w[i];	
	}
}

double norm(int n, double* v){
	return sqrt(dot(n, v, v));
} 

void mat_mul(double* A, double* B, double* C, int n, int m, int p){
	for (int i=0; i<n; i++){
		for (int j=0; j<p; j++){
			double sum = 0;
			
			#pragma omp parallel for reduction(+:sum)
			for (int k=0; k<m; k++){
				sum += A[i*m + k] * B[k*p + j];
			}
		
			C[i*p + j] = sum;
		}	
	}
}


/*
 * @brief A serial variant of the congugate gradient algrithm following algorithm
 * 			9.19 in Saad.
 * 
 * @param n[in] size of square matrix A 
 * @param A[in] pointer to double representing square matrix of size n x n.
 * @param b[in] pointer to double representing vector
 * @param x_0[in] pointer to double for initial guess of solution to linear system
 * @param eps[in] Precision to cut off convecgence with. 
 * @param x[out] pointer to double for soution vector
*/
void conjugate_gradient(int n, double* A, double* b, double* x_0, double eps, double* x, int* num_iter){
	double alpha;
	double beta;

	double* p  = malloc(n * sizeof(double)); 
	double* Ap = malloc(n * sizeof(double)); 
	double* r  = malloc(n * sizeof(double)); 
	double* Ar = malloc(n * sizeof(double)); 

	mat_mul(A, x_0, r, n, n, 1);
	vect_sum(n, b, -1, r, r);
	memcpy(p, r, n*sizeof(double));
	
	int j;
	for (j=0; j<MAX_ITER; j++){
		mat_mul(A, r, Ar, n, n, 1);
		mat_mul(A, p, Ap, n, n, 1);
		alpha = dot(n, r, Ar) / dot(n, Ap, Ap);
	
		vect_sum(n, x,  alpha, p , x);
		double dot_Ar_prev = dot(n, r, Ar);	
		vect_sum(n, r, -alpha, Ap, r);

		if (norm(n, r) < eps) {
			break;
		}
		
		beta = dot(n, r, Ar) / dot_Ar_prev;
		vect_sum(n, r, beta, p, p);
	}
	
	printf("Converged at iter = %d\n", j);
	*num_iter = j;

	free(p);
	free(Ap);
	free(r);
	free(Ar);
}



/*
 * @brief A serial variant of the congugate gradient algrithm following algorithm
 * 			9.19 in Saad. This one is meant for question 3.3 in which it computes 
 * 			and saves the residuals at each step.
 * 
 * @param n[in] size of square matrix A 
 * @param A[in] pointer to double representing square matrix of size n x n.
 * @param b[in] pointer to double representing vector
 * @param x_0[in] pointer to double for initial guess of solution to linear system
 * @param eps[in] Precision to cut off convecgence with. 
 * @param x[out] pointer to double for soution vector
 * @param residuals[out] pointer to pointers of size num_iter x n which stores all computer residuals
*/
void conjugate_gradient_saveres(int n, double* A, double* b, double* x_0, double eps, double* x, int* num_iter, double* residuals){
	double alpha;
	double beta;

	double* p  = malloc(n * sizeof(double)); 
	double* Ap = malloc(n * sizeof(double)); 
	double* r  =  malloc(n * sizeof(double)); 
	double* Ar = malloc(n * sizeof(double)); 

	mat_mul(A, x_0, r, n, n, 1);
	vect_sum(n, b, -1, r, r);
	memcpy(p, r, n*sizeof(double));
	
	int j;
	for (j=0; j<MAX_ITER; j++){
		printf("\rj = %d", j);
		mat_mul(A, r, Ar, n, n, 1);
		mat_mul(A, p, Ap, n, n, 1);
		alpha = dot(n, r, Ar) / dot(n, Ap, Ap);
	
		vect_sum(n, x,  alpha, p , x);
		double dot_Ar_prev = dot(n, r, Ar);	
		vect_sum(n, r, -alpha, Ap, r);
	
		// saves residual
		for (int i=0; i<n; i++){
			residuals[j*n + i] = r[i];
		}

		if (norm(n, r) < eps) {
			break;
		}
		
		beta = dot(n, r, Ar) / dot_Ar_prev;
		vect_sum(n, r, beta, p, p);
	}
	
	printf("\nConverged at iter = %d\n", j);
	*num_iter = j;

	free(p);
	free(Ap);
	free(r);
	free(Ar);
}
