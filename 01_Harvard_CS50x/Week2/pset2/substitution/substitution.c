// Author: Jesus Carlos Martinez Gonzalez
// Date: 05/10/2021
// Objective: Cipher a plaintext string, given a key 
// Input: cipher key as a command line argument
// Output: ciphertext

#include <stdio.h>
#include <cs50.h> // For educational purposes
#include <ctype.h> // To access case-related functions
#include <string.h> // To access strlen()

// Functions which handles all the key validations
int validate_key(string, int);

int main(int argc, string argv[])
{
    if (argc == 2) // If the user passed 1 command line argument
    {
        string key = argv[1], plain_text = "";
        int size = strlen(key);
        char curr = '$';

        // If the key is valid
        if (validate_key(key, size) == 1)
        {
            return 1;
        }

        // The text to translate and its translation
        string plaintext = get_string("plaintext: ");
        string ciphertext = plaintext;

        // Translation process
        for (int i = 0, n = strlen(plaintext); i < n; i++) // Iterates over each character in plaintext
        {
            curr = plaintext[i];
            
            // If the current character is uppercase, cast it to int and remove the base for uppercase letters (A's int value)
            if (isupper(curr))
            {
                ciphertext[i] = toupper(key[(int) curr - 65]);
            }
            
            // If the current character is lowercase, cast it to int and remove the base for lowercase letters (a's int value)
            else if (islower(curr))
            {
                ciphertext[i] = tolower(key[(int) curr - 97]);
            }

        }
        
        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

int validate_key(string key, int size)
{
    if (size == 26) // Valid size
    {
        for (int i = 0; i < size - 1; i++) // Iterates over the key's characters
        {
            if (isalpha(key[i]) == 0) // Not a letter
            {
                printf("ERROR: Key must only contain letters\n");
                return 1;
            }
            for (int j = i + 1; j < size; j++) // Iterates over the letters after i
            {
                if (key[i] == key[j]) // Repeated element
                {
                    printf("ERROR: Key must only contain unique values\n");
                    return 1;
                }
            }
            key[i] = tolower(key[i]);
        }
        return 0;
    }
    printf("ERROR: Key must contain 26 characters.\n");
    return 1;
}