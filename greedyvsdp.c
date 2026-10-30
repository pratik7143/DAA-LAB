#include <stdio.h>
#include <time.h>
struct Item
{
    int weight;
    int profit;
    float ratio;
};
int max(int a, int b)
{
    return (a > b) ? a : b;
}
int main()
{
    int n, capacity;
    printf("Enter number of items: ");
    scanf("%d", &n);
    struct Item item[n];
    printf("\nEnter weight and profit of each item:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Item %d: ", i + 1);
        scanf("%d %d", &item[i].weight, &item[i].profit);
        item[i].ratio =
            (float)item[i].profit / item[i].weight;
    }
    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);
    // GREEDY APPROACH
    clock_t start = clock();
    // Sort according to profit/weight ratio
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (item[i].ratio < item[j].ratio)
            {
                struct Item temp = item[i];
                item[i] = item[j];
                item[j] = temp;
            }
        }
    }
    int greedyProfit = 0;
    int currentWeight = 0;
    printf("\nItems selected by Greedy:\n");
    for (int i = 0; i < n; i++)
    {
        if (currentWeight + item[i].weight <= capacity)
        {
            currentWeight += item[i].weight;
            greedyProfit += item[i].profit;
            printf("Weight = %d, Profit = %d\n",
                   item[i].weight, item[i].profit);
        }
    }
    clock_t end = clock();
    double greedyTime =(double)(end - start) / CLOCKS_PER_SEC;
    start = clock();
    int dp[n + 1][capacity + 1];
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            else if (item[i - 1].weight <= w)
            {
                dp[i][w] = max(
                    item[i - 1].profit +
                    dp[i - 1][w - item[i - 1].weight],

                    dp[i - 1][w]
                );
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    int dpProfit = dp[n][capacity];
    end = clock();
    double dpTime =(double)(end - start) / CLOCKS_PER_SEC;
    printf("\n------ Result ------\n");
    printf("Greedy Profit = %d\n", greedyProfit);
    printf("DP Profit     = %d\n", dpProfit);
    printf("\nGreedy Time = %.6f seconds\n", greedyTime);
    printf("DP Time     = %.6f seconds\n", dpTime);
    return 0;
}