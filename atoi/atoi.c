#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // exit claus
    int num = 0;
    int n = strlen(input);
    // looping through single characters
    for (int i = 0; i < n; i++)
    {
        // converting to int from string 48 is the value to ascii '0'
        num = num * 10 + (input[i] - '0');
    }
    return (num);
}