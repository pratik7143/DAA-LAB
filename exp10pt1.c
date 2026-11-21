#include <stdio.h>
#include <time.h>
int a[20], selected[20];
int n, target;
void subset(int index, int sum)
{
    // If target sum is found
    if (sum == target)
    {
        printf("Subset: ");
        for (int i = 0; i < n; i++)
        {
            if (selected[i] == 1)
                printf("%d ", a[i]);
        }
        printf("\n");
        return;
    }
    // Stop if all elements checked or sum exceeds target
    if (index == n || sum > target)
        return;
    // Include current element
    selected[index] = 1;
    subset(index + 1, sum + a[index]);
    // Exclude current element / Backtrack
    selected[index] = 0;
    subset(index + 1, sum);
}
int main()
{
    clock_t start, end;
    double time_taken;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    printf("Enter target sum: ");
    scanf("%d", &target);
    printf("\nPossible subsets are:\n");
    start = clock();
    subset(0, 0);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nExecution Time: %f seconds\n", time_taken);
    return 0;
}