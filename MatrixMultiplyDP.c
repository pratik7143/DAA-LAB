#include<stdio.h>
#include<limits.h>
#include<time.h>
int main(){
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d",&n);
    int a[n+1];
    printf("Enter the dimensions of the matrices: ");
    for(int i = 0;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int m[n][n];
    int s[n][n];
    clock_t start = clock();
    for(int i = 0;i<n;i++){
        m[i][i] = 0;
    }
    for(int l = 2; l<=n;l++){
        for(int i = 0;i<=n-l;i++){
            int j = i+l-1;
            m[i][j] = INT_MAX;
            for(int k = i;k<j;k++){
                int cost = m[i][k] + m[k+1][j]+a[i]*a[k+1]*a[j+1];
                if(cost<m[i][j]){
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
    clock_t end = clock();
    double time = (double)(end-start) / CLOCKS_PER_SEC;
    printf("Minimum number of multiplication = %d\n",m[0][n-1]);
    printf("Execution time = %.7f seconds\n",time);
    return 0;
}