/*
 * Tema 2 ASC
 * 2019 Spring
 * Catalin Olaru / Vlad Spoiala
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double *B) {
	int i, j, k;
	double *C = malloc(N * N * sizeof(double));
	double D[N * N], E[N * N], F[N * N], Atr[N * N], Btr[N * N];

	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			Atr[j * N + i] = A[i * N + j];

	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			Btr[j * N + i] = B[i * N + j];
	
	/* D = A transpus * B; E = B transpus * A; F = zerotr(D + E) */
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			D[i * N + j] = 0.0;
			E[i * N + j] = 0.0;
			F[i * N + j] = 0.0;
			for (k = 0; k < N; ++k) {
				if (i <= j) {
					D[i * N + j] = D[i * N + j] + Atr[i * N + k] * B[k * N + j];
					E[i * N + j] = E[i * N + j] + Btr[i * N + k] * A[k * N + j];
					F[i * N + j] = D[i * N + j] + E[i * N + j];
				}
			}
		}
	}

	/* C = F * F */
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			C[i * N + j] = 0.0;
			for (k = 0; k < N; ++k) {
				C[i * N + j] = C[i * N + j] + F[i * N + k] * F[k * N + j];
			}
		}
	}

	return C;
}
