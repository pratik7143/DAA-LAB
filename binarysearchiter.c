#include <stdio.h>
#include <time.h>
int BS(int arr[], int n, int tar)
{
    int st = 0;
    int end = n - 1;
    while (st <= end)
    {
        int mid = (st + end) / 2;
        if (tar > arr[mid])
            st = mid + 1;
        else if (tar < arr[mid])
            end = mid - 1;
        else
            return mid;
    }
    return -1;
}
int main()
{
    int arr[100], n, tar, result, i;
    clock_t start, end;
    double cpu_time_used;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter the elements in sorted order:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("Enter the element to search: ");
    scanf("%d", &tar);
    start = clock();
    result = BS(arr, n, tar);
    end = clock();
    if (result == -1)
    {
        printf("The element you entered is not present in the array.\n");
    }
    else
    {
        printf("The element was found at index %d.\n", result);
    }
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for search: %f seconds\n", cpu_time_used);

    return 0;
}