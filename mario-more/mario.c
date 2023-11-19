#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // declare a variable
    int n, i, j, k, l;
    // start do loop
    do
    {
        // asks user for an integer between 1 - 8
        n = get_int("Please enter a positive integer between 1 - 8: ");
    }
    // keeps looping until user enters an integer between 1 - 8
    while (n <= 0 || n > 8);
    // prints row
    for (i = n; i >= 1; i--)
    {
        // prints column
        for (j = i; j >= 2; j--)
        {
            printf(" ");
        }
        // prints bricks
        for (k = 1; k <= n - i + 1; k++)
        {
            printf("#");
        }
        // Adds two spaces after a brick
        for (l = k; l == k; l--)
        {
            printf(" ");
            printf(" ");
        }
        // does the right side of the bricks
        for (k = 1; k <= n - i + 1; k++)
        {
            printf("#");
        }
        // prints newline
        printf("\n");
    }
}