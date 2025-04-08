#define MAX_ITER 2000

double dot(int n, double* v, double* w){
	double sum = 0;
	for (int i=0; i<n; i++){
		sum += v[i]*w[i];	
	}
	return sum;
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

void conjugate_gradient(A, b, x, ){
	
	double alpha_j;

	for (int j=0; j<MAX_ITER; i++){
		alpha_j = mat_mul( 
	}
	

}
