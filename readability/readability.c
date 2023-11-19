// Libraries needed
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// prototype functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int grade_calculate(float);

// Main program
int main(void)
{
    // variable
    string text;
    // asking user for some text
    text = get_string("Text: ");
    // returns from functions
    int lc = count_letters(text);
    int wc = count_words(text);
    int sc = count_sentences(text);
    // Coleman-Liau formular
    float calculation = (0.0588 * lc / wc * 100) - (0.296 * sc / wc * 100) - 15.8;
    // Changing float to integer
    int index = round(calculation);
    // checking grade and printing correct print statement
    if (index < 1)
    {
        // prints if grade is 1 or lower
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        // prints if index if bigger than 16
        printf("Grade 16+\n");
    }
    else
    {
        // prints grade with index number of grade
        printf("Grade %i\n", index);
    }
}
// count letters in text func
int count_letters(string text)
{
    // counter for letters
    int letters = 0;
    // goes through the text one character at a time
    for (int i = 0; i < strlen(text); i++)
    {
        // Checks to see if a letter is alphabetical and upper or lower case letters
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            // Adds 1 to counter for each letter found
            letters++;
        }
    }
    // Returns value of letters count to lc in main
    return letters;
}
// count words in text function
int count_words(string text)
{
    // counter for words (starts at one due to that it counts white space for words)
    int words = 1;
    // goes through the text one character at a time
    for (int i = 0; i < strlen(text); i++)
    {
        // checks for white space to count a word
        if (text[i] == ' ')
        {
            // Adds 1 to words for each white space found
            words++;
        }
    }
    // Returns value of words count to wc in main
    return words;
}
// count sentences in text function
int count_sentences(string text)
{
    // counter
    int sentences = 0;
    // goes through the text one character at a time
    for (int i = 0; i < strlen(text); i++)
    {
        // checking for a point, question mark or an exclamation mark to determine a sentence
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            // Adds 1 for each sentence found
            sentences++;
        }
    }
    // returns value of sentences count to sc in main
    return sentences;
}