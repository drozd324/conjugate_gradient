#include <math.h>

#define MAX_ITER 100000

double dot(int n, double* v, double* w);
void vect_sum(int n, double* v, double alpha, double* w, double* out);
double norm(int n, double* v);
void mat_mul(double* A, double* B, double* C, int n, int m, int p);
void conjugate_gradient(int n, double* A, double* b, double* x_0, double eps, double* x, int* num_iter);
void conjugate_gradient_saveres(int n, double* A, double* b, double* x_0, double eps, double* x, int* num_iter, double* residuals);
