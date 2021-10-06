// Author: Jesus Carlos Martinez Gonzalez
// Date: 05/10/2021
// Objective: Determine the reading level of a given text

#include <stdio.h>
#include <cs50.h> // For educational purposes
#include <string.h> // To access strlen()
#include <math.h> // To access round()

// Coleman-Liau index formula constants
#define CONST1 0.0588
#define CONST2 0.296
#define CONST3 15.8

// Coleman-Liau index formula
int reading_level(int, int, int);

int main(void)
{
    int index = -1, words = 0, sentences = 0, letters = 0;

    // Request text to analyze
    string text = get_string("Text: ");

    // Iterate over the string, counting letters, words and sentences in it
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
    }
    words++;

    index = reading_level(letters, words, sentences);
    
    // Index-based output
    if (index < 1)
    {
        printf("Grade Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int reading_level(int letters, int words, int sentences)
{
    //  Coleman-Liau index formula for determining reading levels based on U.S. scholar grades:
    //      index = 0.0588 * L - 0.296 * S - 15.8
    //          L is the average number of letters per 100 words in the text
    //          S is the average number of sentences per 100 words in the text
    return round(CONST1 * (letters * 100 / (float)words) - CONST2 * (sentences * 100 / (float)words) - CONST3);
}