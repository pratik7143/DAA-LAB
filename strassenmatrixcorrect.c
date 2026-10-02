#include <stdio.h>
#include <time.h>
#define N 256 // Matrix size (256 is large enough to show Strassen winning)
// Traditional Method
void traditional(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
// performs the addition and subtraction required for strassen
void add(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) C[i][j] = A[i][j] + B[i][j];
}
void sub(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) C[i][j] = A[i][j] - B[i][j];
}
// Strassen Algo
void strassen(int n, int A[n][n], int B[n][n], int C[n][n]) {
    // HYBRID CUTOFF: This is mandatory if you aren't using pointers.
    // It stops the stack memory from overloading and crashing the speed.
    if (n <= 32) { 
        traditional(n, A, B, C);
        return;
    }   
    int h = n / 2;
    // C99 Variable Length Arrays allocated on the stack
    int A11[h][h], A12[h][h], A21[h][h], A22[h][h];
    int B11[h][h], B12[h][h], B21[h][h], B22[h][h];
    int P1[h][h], P2[h][h], P3[h][h], P4[h][h], P5[h][h], P6[h][h], P7[h][h];
    int tA[h][h], tB[h][h];
    // Split matrices
    for(int i=0; i<h; i++) {
        for(int j=0; j<h; j++) {
            A11[i][j] = A[i][j];       A12[i][j] = A[i][j+h];
            A21[i][j] = A[i+h][j];     A22[i][j] = A[i+h][j+h];
            B11[i][j] = B[i][j];       B12[i][j] = B[i][j+h];
            B21[i][j] = B[i+h][j];     B22[i][j] = B[i+h][j+h];
        }
    }
    // 7 Recursive Calls
    sub(h, B12, B22, tB);  strassen(h, A11, tB, P1);
    add(h, A11, A12, tA);  strassen(h, tA, B22, P2);
    add(h, A21, A22, tA);  strassen(h, tA, B11, P3);
    sub(h, B21, B11, tB);  strassen(h, A22, tB, P4);
    add(h, A11, A22, tA);  add(h, B11, B22, tB); strassen(h, tA, tB, P5);
    sub(h, A12, A22, tA);  add(h, B21, B22, tB); strassen(h, tA, tB, P6);
    sub(h, A11, A21, tA);  add(h, B11, B12, tB); strassen(h, tA, tB, P7);
    // Combine results
    for(int i=0; i<h; i++) {
        for(int j=0; j<h; j++) {
            C[i][j]     = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j]; 
            C[i][j+h]   = P1[i][j] + P2[i][j];                       
            C[i+h][j]   = P3[i][j] + P4[i][j];                       
            C[i+h][j+h] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j]; 
        }
    }
}
int main() {
    // Declared as 'static' so these massive arrays don't blow up the local stack
    static int A[N][N], B[N][N], C_trad[N][N], C_stras[N][N];
    clock_t start, end;   
    // We run it 5 times to get a stable, measurable average
    int iterations = 5; 
    // Initialize the matrices
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (i + j) % 5; 
            B[i][j] = (i - j) % 5;
        }
    }
    printf("Running benchmark for %dx%d matrix...\n", N, N);
    start = clock();
    for (int i = 0; i < iterations; i++) traditional(N, A, B, C_trad);
    end = clock();
    printf("Traditional Method Time : %f seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    start = clock();
    for (int i = 0; i < iterations; i++) strassen(N, A, B, C_stras);
    end = clock();
    printf("Strassen Method Time    : %f seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    return 0;
}