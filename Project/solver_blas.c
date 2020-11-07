/*
 * Tema 2 ASC
 * 2019 Spring
 * Catalin Olaru / Vlad Spoiala
 */
#include "utils.h"
#include <cblas.h>

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	int i, j;
	double *C = malloc(N * N * sizeof(double));
	double *D = malloc(N * N * sizeof(double));
	double *E = malloc(N * N * sizeof(double));
	double *F = malloc(N * N * sizeof(double));

	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			F[j * N + i] = 0.0;

	double alfa = 1.0, beta = 0.0;

	/* D = A transpus * B */
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N, N, alfa, A, N, B, N, beta, D, N);
	
	/* E = B transpus * A */
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N, N, alfa, B, N, A, N, beta, E, N);
	
	/* F = zerotr(D + E) */
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
				if (i <= j) {
					F[i * N + j] = D[i * N + j] + E[i * N + j];
				}
		}
	}

	/* C = F * F */
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, alfa, F, N, F, N, beta, C, N);

	return C;
}
