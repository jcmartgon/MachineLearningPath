// Author: Jesus Carlos Martinez Gonzalez
// Date: 08/10/2021
// Objective: Implement a Tideman election system
// Input: The names of the candidates to participate in the election as command prompt arguments
// Output: The name of the winner

#include <cs50.h> // For educational purposes
#include <stdio.h>
#include <string.h> // For string-related functions

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

void merge_pairs(pair arr[], int, int, int);
void merge_sort_pairs(pair arr[], int, int);
bool check_loop(int, int);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++) // Iterates over the candidates array
    {
        if (strcmp(candidates[i], name) == 0) // If name matches the name of the ith candidate
        {
            ranks[rank] = i; // Adds the value correpsonding to the candidate from the candidates array to the proper rank in the ranks array
            return true; // Valid candidate
        }
    }
    return false; // Invalid candidate
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    merge_sort_pairs(pairs, 0, pair_count - 1);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (check_loop(pairs[i].winner, pairs[i].loser) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool winner = false;
    int win_int = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                winner = false;
            }
        }
        if (winner)
        {
            win_int = i;
        }
    }
    printf("%s\n", candidates[win_int]);
    return;
}

// Merge portion of the merge sort, adapted to work with the pair structure
void merge_pairs(pair arr[], int start, int half, int end)
{
    int i, j, k;
    int left_size = half - start + 1;
    int right_size = end - half;
  
    pair left_side[left_size], right_side[right_size];
  
    // Populates temporary arrays for left and right side of arr
    for (i = 0; i < left_size; i++)
    {
        left_side[i] = arr[start + i];
    }
    for (j = 0; j < right_size; j++)
    {
        right_side[j] = arr[half + 1 + j];
    }
  
    i = 0;
    j = 0;
    k = start;
    while (i < left_size && j < right_size) 
    {
        // Instead of comparing the sizes of the elements at the ith position, their corresponding victory strengths are compared
        if (preferences[left_side[i].winner][left_side[i].loser] > preferences[right_side[j].winner][right_side[j].loser]) 
        {
            arr[k] = left_side[i];
            i++;
        }
        else 
        {
            arr[k] = right_side[j];
            j++;
        }
        k++;
    }
    while (i < left_size) 
    {
        arr[k] = left_side[i];
        i++;
        k++;
    }
    while (j < right_size) 
    {
        arr[k] = right_side[j];
        j++;
        k++;
    }
    return;
}

// Merge sort algorithm
void merge_sort_pairs(pair arr[], int start, int end)
{
    if (start < end) 
    {
        int half = start + (end - start) / 2;
        merge_sort_pairs(arr, start, half);
        merge_sort_pairs(arr, half + 1, end);
  
        merge_pairs(arr, start, half, end);
    }
    return;
}

// Checks whether or not a loop would be created if two nodes from the graph are connected
bool check_loop(int winner, int loser)
{
    if (winner == loser)
    {
        return false;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][winner] == true)
        {
            if (check_loop(i, loser) == false)
            {
                return false;
            }
        }
    }
    return true;
}