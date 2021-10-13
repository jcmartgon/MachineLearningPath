// Author: Jesus Carlos Martinez Gonzalez
// Date: 12/10/2021
// Objective: Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <ctype.h> // To access tolower()
#include <stdio.h> // To access the null data type
#include <string.h> // To access strcmp()
#include <stdlib.h> // To access malloc()

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1024 * 512;
const unsigned int PRIME = 97;

// Hash table
node *table[N];

// Number of words
int words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Word in lowercase form
    char word_lc[LENGTH + 1];
    
    // Iterate over word, adding each value into word_lc, in lowercase
    int curr = 0;
    while (word[curr] != '\0') // While it's not the end of the word
    {
        word_lc[curr] = tolower(word[curr]);
        curr++;
    }
    word_lc[curr] = '\0';

    node *n = table[hash(word_lc)];
    while (n != NULL) // While not empty
    {
        if (strcmp(n->word, word_lc) == 0) // Found
        {
            return true;
        }
        else // Keep searching
        {
            n = n->next;
        }
    }
    
    // Not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Iterates over word
    int curr = 0;
    unsigned int hash = 0;
    while (word[curr] != '\0') 
    {
        hash = hash * PRIME + word[curr];
        curr++;
    } 
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) // File doesn't exist
    {
        printf("Could not open file.\n");
        return false;
    }
    
    char word[LENGTH + 1];
    // Iterates over word
    while (fscanf(file, "%s", word) != EOF)
    {
        words++;
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Not enough memory in system. \n");
            return false;
        }
        strcpy(n->word, word);
        unsigned int h = hash(word);
        if (table[h] == NULL)
        {
            table[h] = n;
            n->next = NULL;
        }
        else
        {
            node *head = table[h];
            n->next = head->next;
            head->next = n;
        }
    }
    fclose(file); // dont forget to close dictionary file
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N ; i++) 
    {
        // for each bucket, free each node
        node *n = table[i];
        while (n != NULL)
        {
            node *tmp = n;
            n = n->next;
            free(tmp);
        }
    }
    return true;
}
