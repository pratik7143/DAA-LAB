#include <stdio.h>
int main()
{
    int n = 10;
    int start[10]  = {10, 12, 14, 18, 20, 22, 24, 28, 30, 35};
    int finish[10] = {16, 18, 20, 22, 25, 27, 30, 32, 35, 40};
    int i = 0;
    printf("Selected Activities:\n");
    // Select the first activity
    printf("Activity %d = (%d, %d)\n", i + 1, start[i], finish[i]);
    // Greedy selection
    for (int j = 1; j < n; j++)
    {
        if (start[j] >= finish[i])
        {
            printf("Activity %d = (%d, %d)\n",
                   j + 1, start[j], finish[j]);
            i = j;
        }
    }
    return 0;
}