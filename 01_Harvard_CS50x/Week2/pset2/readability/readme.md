# Text readability

Determine the reading level of a given text, based on Coleman-Liau index formula.

Coleman-Liau index formula for determining reading levels based on U.S. scholar grades: 

index = 0.0588 * L - 0.296 * S - 15.8

Where:
-L is the average number of letters per 100 words in the text
-S is the average number of sentences per 100 words in the text

## Running

To run:
1. Make sure you've got a C compiler installed
2. Use the "./readability" command

## Technology stack

The C library "cs50.h" was used for educational purposes to assist with input fetching.
The C library "string.h" was used to acces strlen().
The C library "math.h" was used to acces round().