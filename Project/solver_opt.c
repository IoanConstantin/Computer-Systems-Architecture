/*
 * Tema 2 ASC
 * 2019 Spring
 * Catalin Olaru / Vlad Spoiala
 */
#include "utils.h"
#define bs 40
#define min(a, b) (((a) < (b) ? (a) : (b)))

/*
 * Add your optimized implementation here
 */

double* my_solver(int N, double *A, double* B) {
	int i, j, k, i2, j2, k2;
	double *C = malloc(N * N * sizeof(double));
	double *D = malloc(N * N * sizeof(double));
	double *E = malloc(N * N * sizeof(double));
	double F[N * N], Atr[N * N], Btr[N * N];

	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			Atr[j * N + i] = A[i * N + j];
		}
	}

	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			Btr[j * N + i] = B[i * N + j];
		}
	}

	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			F[i * N + j] = 0;
		}
	}

	/* Facem inmultirile de matrici folosind blocked matrix multiplication
	 * cu bs = 40 pentru ca N % 40 == 0 */
	for (i = 0; i < N; i += bs) {
		for (j = 0; j < N; j += bs) {
			for (k = 0; k < N; k += bs) {
				for (i2 = i; i2 < min(i + bs, N); ++i2) {
					for (j2 = j; j2 < min(j + bs, N); ++j2) {
						for (k2 = k; k2 < min(k + bs, N); ++k2) {
							D[i2 * N + j2] = D[i2 * N + j2] + Atr[i2 * N + k2] * B[k2 * N + j2];
							E[i2 * N + j2] = E[i2 * N + j2] + Btr[i2 * N + k2] * A[k2 * N + j2];
						}
						if(i2 <= j2)
								F[i2 * N + j2] = D[i2 * N + j2] + E[i2 * N + j2];
					}
				}
			}
		}
	}


	for (i = 0; i < N; i += bs) {
		for (j = 0; j < N; j += bs) {
			for (k = 0; k < N; k += bs) {
				for (i2 = i; i2 < min(i + bs, N); ++i2) {
					for (j2 = j; j2 < min(j + bs, N); ++j2) {
						for (k2 = k; k2 < min(k + bs, N); ++k2) {
							C[i2 * N + j2] = C[i2 * N + j2] + F[i2 * N + k2] * F[k2 * N + j2];
						}
					}
				}
			}
		}
	}

	return C;
}
