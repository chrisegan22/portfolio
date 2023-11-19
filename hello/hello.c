#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asks user for there name
    string name = get_string("What is your name? ");
    // prints hello plus users name to screen
    printf("Hello, %s", name);
    // prints an newline
    printf("\n");
}
