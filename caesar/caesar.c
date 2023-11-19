#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// prototype functions
bool only_digits(string word);
char rotate(char x, int y);
// main program
int main(int argc, string argv[])
{
    // checking to see if you enter 2 commandline aruguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // checking to see that all are digits with function
    // if false prints instructions to the screen
    if (only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // changing argv to real numbers and not strings
    int key = atoi(argv[1]);
    // getting text from the user
    string plain = get_string("plaintext: ");
    printf("ciphertext: ");
    char encrypt;
    for (int i = 0, len = strlen(plain); i < len ; i++)
    {
        encrypt = rotate(plain[i], key);
        printf("%c", encrypt);
    }
    printf("\n");
}
// fuction to check digits and compare it and return true or false
bool only_digits(string word)
{
    int length = 0;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isdigit(word[i]))
        {
            length += 1;
        }
    }
    if (length == strlen(word))
    {
        return true;
    }
    return false;
}
// encrypting the plaintext with the key and returns it to user
char rotate(char s, int k)
{
    char p = 0;
    if (isupper(s))
    {
        p = ((s - 'A' + k) % 26 + 'A');
    }
    else if (islower(s))
    {
        p = ((s - 'a' + k) % 26 + 'a');
    }
    else
    {
        p = s;
    }
    return p;
}