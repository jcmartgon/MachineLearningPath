// Author: Jesus Carlos Martinez Gonzalez
// Date: 07/10/2021
// Objective: Simulates a simple election
// Input: Receives the names of the candidates 
// Output: Prints out the name(s) of the candidate(s) with the most votes

#include <cs50.h> // For educational purposes
#include <stdio.h>
#include <string.h> // For string-related functions

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Iterates over the candidates array, if it finds the name in it, adds 1 vote to the candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return 1;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max_votes = 0, curr_votes = 0;
    
    // Iterates over the candidates array, stores the largest amount of votes in max_votes
    for (int i = 0; i < candidate_count; i++)
    {
        curr_votes = candidates[i].votes;
        if (curr_votes > max_votes)
        {
            max_votes = curr_votes;
        }
    }
    
    // iterates over the candidates array, prints out the names of the candidates with max_votes votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

