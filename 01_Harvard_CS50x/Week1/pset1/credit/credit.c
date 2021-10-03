// Author: Jesus Carlos Martinez Gonzalez
// Date: 03/10/2021
// Objective: 

#include <cs50.h> // For educational purposes
#include <stdio.h> 

// Gets the card number's as input and returns the card type if valid, 'INVALID' if otherwise
string card_type(long int);

int main(void)
{
    long int number = get_long("Number: ");
    
    printf("%s\n", card_type(number));
}

string card_type(long int number)
{
    // Variables declaration
    int size = 0, first_digit = -1, second_digit = -1, checksum = 0, curr = 0, aux = 0;
    
    // Iterates over the number, starting from its last digit
    while (number > 0)
    {
        curr = number % 10;
        second_digit = first_digit;
        first_digit = curr;
        number /= 10;
        
        // If the digit is pair, it will get doubled
        if ((size + 1) % 2 == 0)
        {
            curr *= 2;
            
            // If the number is above 9, its first digit will go to curr, second one to aux
            if (curr >= 10)
            {
                aux = curr % 10;
                curr /= 10;
            }
        }
        
        // Adds to checksum
        checksum += curr + aux;
        aux = 0;
        size++;
    }
    
    // Does card-provider validation
    if (checksum % 10 == 0)
    {
        if ((first_digit == 3 && (second_digit == 4 || second_digit == 7)) && size == 15)
        {
            return "AMEX";
        }
        else if ((first_digit == 5 && (second_digit >= 1 && second_digit <= 5)) && size == 16)
        {
            return "MASTERCARD";
        }
        else if (first_digit == 4 && (size == 13 || size == 16))
        {
            return "VISA";
        }
    }
    
    // If validations fail
    return "INVALID";
}