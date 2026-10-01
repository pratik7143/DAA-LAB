#include <stdio.h>
#include <limits.h>
#include <time.h>
int main()
{
    int arr[100], n, i;
    int l1 = INT_MIN, l2 = INT_MIN; // initialized the minimum integer value possible so that it's easy for comparison and replacing
    int s1 = INT_MAX, s2 = INT_MAX;// initialized the maximum integer value possible so that it's easy for comparison and replacing
    clock_t start, end;
    double cpu_time_used;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    if (n < 2)
    { // boundary condition
        printf("Please enter at least 2 elements.\n");
        return 1;
    }
    printf("Enter the elements:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    start = clock();
    for (i = 0; i < n; i++)
    {
        if(arr[i] > l1)
        {
            l2 = l1;
            l1 = arr[i];
        }
        else if(arr[i] > l2 && arr[i] != l1)
        {
            l2 = arr[i];
        }
        if(arr[i] < s1)
        {
            s2 = s1;
            s1 = arr[i];
        }
        else if(arr[i] < s2 && arr[i] != s1)
        {
            s2 = arr[i];
        }
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    if (l2 == INT_MIN || s2 == INT_MAX)
    { // did this because there could be the numbers which are the same.
        printf("Second largest or second smallest element does not exist.\n");
    }
    else
    {
        printf("Second largest element: %d\n", l2);
        printf("Second smallest element: %d\n", s2);
    }
    printf("CPU time taken: %.9f seconds\n", cpu_time_used);
    return 0;
}