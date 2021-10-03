// Author: Jesus Carlos Martinez Gonzalez
// Date: 03/10/2021
// Objective: Predict the years it will takek a population of llamas to go from a start point to an end point.
// Relevant information: The population steadily grows at a 13/12 ratio every year.

#include <cs50.h> // For educational purposes
#include <stdio.h> 

int main(void)
{
    // Prompt for start size
    int current = 0;
    do
    {
        current = get_int("What's the llama population at the start? ");
    }
    while (current < 9);
    

    // Prompt for end size
    int goal = 0;
    do
    {
        goal = get_int("What's the llama population at the end? ");
    }
    while (goal < current);

    // Calculate number of years until we reach threshold
    int years = 0;
    while (current < goal)
    {
        current = current + (current / 3) - (current / 4);
        years++;
    }

    // Print number of years
    printf("Years: %i\n", years);
}