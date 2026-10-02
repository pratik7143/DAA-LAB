#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void traditional(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            C[i][j] = 0;
            for(int k=0; k<n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void add(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int n, int A[n][n], int B[n][n], int C[n][n])
{
    if(n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int h = n/2;

    int A11[h][h], A12[h][h], A21[h][h], A22[h][h];
    int B11[h][h], B12[h][h], B21[h][h], B22[h][h];
    int P1[h][h], P2[h][h], P3[h][h], P4[h][h];
    int P5[h][h], P6[h][h], P7[h][h];
    int X[h][h], Y[h][h];

    for(int i=0; i<h; i++)
        for(int j=0; j<h; j++)
        {
            A11[i][j]=A[i][j];       A12[i][j]=A[i][j+h];
            A21[i][j]=A[i+h][j];     A22[i][j]=A[i+h][j+h];

            B11[i][j]=B[i][j];       B12[i][j]=B[i][j+h];
            B21[i][j]=B[i+h][j];     B22[i][j]=B[i+h][j+h];
        }

    sub(h,B12,B22,Y); strassen(h,A11,Y,P1);
    add(h,A11,A12,X); strassen(h,X,B22,P2);
    add(h,A21,A22,X); strassen(h,X,B11,P3);
    sub(h,B21,B11,Y); strassen(h,A22,Y,P4);

    add(h,A11,A22,X); add(h,B11,B22,Y);
    strassen(h,X,Y,P5);

    sub(h,A12,A22,X); add(h,B21,B22,Y);
    strassen(h,X,Y,P6);

    sub(h,A11,A21,X); add(h,B11,B12,Y);
    strassen(h,X,Y,P7);

    for(int i=0; i<h; i++)
        for(int j=0; j<h; j++)
        {
            C[i][j]     = P5[i][j]+P4[i][j]-P2[i][j]+P6[i][j];
            C[i][j+h]   = P1[i][j]+P2[i][j];
            C[i+h][j]   = P3[i][j]+P4[i][j];
            C[i+h][j+h] = P5[i][j]+P1[i][j]-P3[i][j]-P7[i][j];
        }
}
int main()
{
    int sizes[] = {8,16,32,64,128,256};
    clock_t start, end;
    srand(time(NULL));
    for(int s=0; s<6; s++)
    {
        int n = sizes[s];
        int A[n][n], B[n][n];
        int C1[n][n], C2[n][n];
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
            {
                A[i][j] = rand()%10;
                B[i][j] = rand()%10;
            }
        start = clock();
        traditional(n,A,B,C1);
        end = clock();
        double t1 = (double)(end-start)/CLOCKS_PER_SEC;
        start = clock();
        strassen(n,A,B,C2);
        end = clock();
        double t2 = (double)(end-start)/CLOCKS_PER_SEC;
        printf("%d x %d\n",n,n);
        printf("Traditional = %f sec\n",t1);
        printf("Strassen    = %f sec\n\n",t2);
    }
    return 0;
}