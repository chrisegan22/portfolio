from cs50 import get_string

# Main program


def main():

    # Variable
    text = get_string("Text: ")

    # Returns from functions
    lc = count_letters(text)
    wc = count_words(text)
    sc = count_sentences(text)

    # Coleman-Liau formular
    calculation = (0.0588 * lc / wc * 100) - (0.296 * sc / wc * 100) - 15.8

    # Changing float to interger
    index = round(calculation)

    # Checking grade and printing correct print statement
    if (index <= 1):
        print("Before Grade 1")

    elif (index >= 16):
        print("Grade 16+")

    else:
        print("Grade", index)

# Count letters in text func


def count_letters(text):

    # Counter for letters
    letters = 0

    # Goes through the text one character at a time
    for i in range(len(str(text))):

        # Checks to see if a letter is alphabetical and upper or lower case letters
        if ((text[i] >= 'a' and text[i] <= 'z') or (text[i] >= 'A' and text[i] <= 'Z')):

            # Adds 1 to the counter for each letter found
            letters += 1
    # Returns value of letters count to lc in main
    return letters

# Count words in text function


def count_words(text):

    # Counter for words ( starts at one due to that it counts white space)
    words = 1

    # Goes throught the text one character at a time
    for i in range(len(str(text))):

        # Checks for white space to count word
        if (text[i] == ' '):

            # Adds 1 to words for each white space found
            words += 1
    # Retruns Value of words count to wc in main
    return words


# count sentences in text function
def count_sentences(text):

    # Counter
    sentence = 0

    # Goes through the text one character at a time
    for i in range(len(str(text))):

        # Checking for a point, question mark or an Exclamation mark to determine a sentence
        if (text[i] == '.' or text[i] == '?' or text[i] == '!'):

            # Adds 1 for each sentence found
            sentence += 1
    # Returns value of sentences count to sc in main
    return sentence


if __name__ == "__main__":
    main()