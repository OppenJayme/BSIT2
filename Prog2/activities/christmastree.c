#include <stdio.h>

int main()
{
    int n = 3;

    int i = 0;
    int *ptr = &i;

    while (*ptr < n)
    {
        for (int j = 0; j < n - *ptr - 1; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < 2 * (*ptr) + 1; j++)
        {
            printf("*");
        }
        printf("\n");
        (*ptr)++;
    }

    return 0;
}