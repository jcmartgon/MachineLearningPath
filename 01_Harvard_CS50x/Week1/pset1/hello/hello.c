// Author: Jesus Carlos Martinez Gonzalez
// Date: 03/10/2021
// Objective: Program which requests a name to the user, and uses it to greet them

#include <stdio.h>
#include <cs50.h> // For educational purposes

int main(void)
{
    // Greet user with their name
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}