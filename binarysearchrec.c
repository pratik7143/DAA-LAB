#include <stdio.h>
#include <time.h>
int BS(int arr[], int st, int end, int tar)
{
    int mid;
    if (st > end)
    { //base condition 
        return -1;
    }
    mid = st + (end - st) / 2;
    if (tar > arr[mid])
    {
        return BS(arr, mid + 1, end, tar);
    }
    else if (tar < arr[mid])
    {
        return BS(arr, st, mid - 1, tar);
    }
    else
    {
        return mid;
    }
}
int main()
{
    int arr[100];
    int n, tar, result, i;
    clock_t start, end;
    double cpu_time_used;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter %d elements in sorted order:\n", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("Enter the element to search: ");
    scanf("%d", &tar);
    start = clock();
    result = BS(arr, 0, n - 1, tar);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    if (result == -1)
    {
        printf("Element not found\n");
    }
    else
    {
        printf("Element found at index %d\n", result);
    }
    printf("CPU time taken: %.9f seconds\n", cpu_time_used);
    return 0;
}