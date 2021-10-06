// Author: Jesus Carlos Martinez Gonzalez
// Date: 06/10/2021
// Objective: Scrabble simulator between two players

#include <ctype.h> // To access case-related functions
#include <cs50.h> // For educational purposes
#include <stdio.h>
#include <string.h> // To access strlen()

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Computes the score for the given score
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Prints the winner, based on their respective scores
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int score = 0;
    char curr = '$';
    for (int i = 0, n = strlen(word); i < n; i++) // Iterates over the word
    {
        curr = word[i]; // Current character
        if (isalpha(curr))
        {
            curr = tolower(curr);
            score += POINTS[(int)curr - 97]; 
        }
    }
    return score;
}