#include <stdio.h>
#include <time.h>
int partition(int a[], int low, int high)
{
    int v = a[low];     
    int p = low + 1;     
    int q = high;        
    int temp;
    while (p <= q)
    {
        // p moves from left to right
        while (p <= high && a[p] <= v)
        {
            p++;
        }
        // q moves from right to left
        while (q >= low && a[q] > v)
        {
            q--;
        }
        // pointers have not crossed each other
        if (p < q)
        {
            temp = a[p];
            a[p] = a[q];
            a[q] = temp;
        }
    }
    // Pointers have crossed
    temp = a[low];
    a[low] = a[q];
    a[q] = temp;
    return q;
}
void qs(int a[], int low, int high)
{
    if (low < high)
    {
        int q = partition(a, low, high);
        qs(a, low, q - 1);
        qs(a, q + 1, high);
    }
}
int main()
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int a[n];
    printf("Enter the array elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    clock_t start = clock();
    qs(a, 0, n - 1);
    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\nCPU Time taken: %f seconds\n", cpu_time_used);
    return 0;
}