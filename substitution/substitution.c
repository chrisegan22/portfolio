#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// prototype functions
bool only_alpha(string word);
bool len_key(string word);
bool double_char(string word);
string encrypting(string plain, char word[]);
// main program
int main(int argc, string argv[])
{
    if (argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // checking if it is only letters
    if (only_alpha(argv[1]) == false)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // checking if only 2 commandline aruguments is filled in
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // checking if the length and if there are no double characters in the key
    if (len_key(argv[1]) != true || double_char(argv[1]) != true)
    {
        printf("Key must contain 26 unique characters.\n");
        return 1;
    }
    // getting plain text from user
    string plain = get_string("Plaintext: ");
    // encrypting plain text to ciphertext
    string cipherText = encrypting(plain, argv[1]);
    // printing ciphertext to user
    printf("ciphertext: %s\n", cipherText);
}
// checking if the key is only letters
bool only_alpha(string word)
{
    int length = 0;

    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isalpha(word[i]))
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
// checking the length of the key
bool len_key(string word)
{
     if (strlen(word) == 26)
    {
        return true;
    }
    return false;
}
// checking for double letters in the key
bool double_char(string word)
{
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (toupper(word[i]) == toupper(word[j]) || word[i] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}
// encrypting the plain text to the cipher text
string encrypting(string plain, char word[])
{
    for (int i = 0, len = strlen(plain); i < len; i++)
    {
        if (islower(plain[i]))
        {
            plain[i] = tolower(word[plain[i] - 'a']);
        }
        else if (isupper(plain[i]))
        {
            plain[i] = toupper(word[plain[i] - 'A']);
        }
    }
    return plain;
}