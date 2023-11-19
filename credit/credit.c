#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>

// Function prototypr slot

bool validity_checker(long long ccnum);
int find_length_cc(long long ccnum);
bool checksum(long long ccnum);
void print_credit_card_name(long long ccnum);

int main(void)
{
    long long ccnum;
// asking for credit card nummber
    do
    {
        ccnum = get_long("Enter your credit card number: \n");
    }
    while (ccnum <= 0);
// checking credit card if valid or invalid
    if (validity_checker(ccnum))
    {
        print_credit_card_name(ccnum);
    }
    else
    {
        printf("INVALID\n");
    }
}

// creating function bodies
// Comparing length to size credit card number
bool validity_checker(long long ccnum)
{
    int len = find_length_cc(ccnum);
    return ((len == 13 || len == 15 || len == 16) && checksum(ccnum));
}
// Checking length of credit card number
int find_length_cc(long long ccnum)
{
    int len = 0;
    while (ccnum != 0)
    {
        ccnum = ccnum / 10;
        len++;
    }
    return len;
}
// Getting the last digit credit card number
bool checksum(long long ccnum)
{
    int sum = 0;
    long long tempccnum = ccnum;
    while (tempccnum > 0)
    {
        int lastdigit = tempccnum % 10;
        sum = sum + lastdigit;
        tempccnum = tempccnum / 100;
    }
// Getting secondlast digit credit card number
// Calculating every other number plus multiply by 2 and adding remainder numbers
    tempccnum = ccnum / 10;
    while (tempccnum > 0)
    {
        int secondlastdigit = (tempccnum % 10);
        int tempmultiply = secondlastdigit * 2;
        sum = sum + (tempmultiply % 10) + (tempmultiply / 10);
        tempccnum = tempccnum / 100;
    }
    return (sum % 10) == 0;
}
// printing credit card name
void print_credit_card_name(long long ccnum)
{
    if ((ccnum >= 34e13 && ccnum < 35e13) || (ccnum >= 37e13 && ccnum < 38e13))
    {
        printf("AMEX\n");
    }
    else if (ccnum >= 51e14 && ccnum < 56e14)
    {
        printf("MASTERCARD\n");
    }
    else if ((ccnum >= 4e12 && ccnum < 5e12) || (ccnum >= 4e15 && ccnum < 5e15))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}