#include <stdio.h>
#include <time.h>
int main()
{
    int n;
    clock_t start, end;
    double cpu_time_used;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int a[n];
    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("Element %d: ", i + 1);
        scanf("%d", &a[i]);
    }
    start = clock();
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nCPU time taken: %.9f seconds\n", cpu_time_used);
    return 0;
}