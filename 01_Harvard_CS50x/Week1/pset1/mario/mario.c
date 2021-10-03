// Author: Jesus Carlos Martinez Gonzalez
// Date: 03/10/2021
// Objective: Prompt the user for a number n, and display two mirrored pyramids, n-# tall and n-# wide at the base, each higher level of the pyramid should be made of 1 less #

#include <cs50.h> // For educational purposes
#include <stdio.h> 

// Function in charge of printing a given level in the pyramid
void draw_level(int, int);

int main(void)
{
    // Prompt user for the pyramid's height
    int height;
    do
    {
        height = get_int("What will be the height of the pyramids? ");
    }
    while (height <= 0 || height > 8);
    
    // Prints the pyramid
    for (int i = 0; i < height; i++)
    {
        draw_level(i, height);
        printf("\n");
    }
}

// Hashes represents the amount of hashes to print per side of the pyramid, max is the amount of hashes per side, of the base level
void draw_level(int hashes, int max)
{
    // The first half of the level
    for (int i = max - 1; i >= 0; i--)
    {
        if (hashes >= i)
        {
            printf("#");
        }
        else
        {
            printf(" ");
        }
    }
    
    // Space between halves
    printf("  ");
    
    // Second half of the level
    for (int i = 0; i < max; i++)
    {
        if (hashes >= i)
        {
            printf("#");
        }
    }
}