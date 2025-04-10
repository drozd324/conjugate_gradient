#include <math.h>

#define MAX_ITER 2000

double dot(int n, double* v, double* w){
	double sum = 0;
	for (int i=0; i<n; i++){
		sum += v[i]*w[i];	
	}
	return sum;
}

void vect_sum(int n, double* v, double alpha, double* w, double* out){
	for (int i=0; i<n; i++){
		out[i] = v[i] + alpha*w[i];	
	}
}

double norm(int n, double* v){
	return sqrt(dot(n, v, v));
} 

void mat_mul(double* A, double* B, double* C, int n, int m, int p){
	for (int i=0; i<n; i++){
		for (int j=0; j<p; i++){
			double sum = 0;
			for (int k=0; k<m; k++){
				sum += A[i*m + k] * B[k*p + j];
			}
		
			C[i*p + j] = sum;
		}	
	}
}


void conjugate_gradient(n, A, b, x_0){
	
	double alpha;
	double beta;

	double* x = malloc(n * sizeof(double)); 
	double* p = malloc(n * sizeof(double)); 
	double* Ap = malloc(n * sizeof(double)); 
	double* r = malloc(n * sizeof(double)); 
	double* Ar = malloc(n * sizeof(double)); 

	mat_mul(A, x_0, r, n, n, 1);
	memcpy(p, r, n*sizeof(double));
	
	for (int j=0; j<MAX_ITER; i++){
		mat_mul(A, r, Ar, n, n, 1);
		mat_mul(A, p, Ap, n, n, 1);
		alpha_j = dot(r, Ar) / dot(Ap, Ap);
	
		vect_sum(n, x,  alpha, p , x);
		double dot_Ar_prev = dot(r, Ar);	
		vect_sum(n, r, -alpha, Ap, r);

		if (fabs(norm(r)) < 1e-4) {
			printf("Converged at iter = %d\n", j);
			break;
		}
		
		beta = dot(r, Ar) / dot_Ar_prev;
		vect_sum(n, r, beta, p, p);
	}
}
