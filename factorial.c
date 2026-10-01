#include <stdio.h>
int fact(int n)
{
    int p;
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return n * fact(n - 1);
    }
}
int main()
{
    int x, ans;
    printf("Enter the number: ");
    scanf("%d", &x);
    if (x <= 0)
    {
        printf("Factorial is undefined for -ve numbers");
    }
    ans = fact(x);
    printf("The factorial of %d is %d", x, ans);
    return 0;
}
