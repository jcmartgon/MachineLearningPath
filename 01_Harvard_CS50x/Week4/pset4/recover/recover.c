// Author: Jesus Carlos Martinez Gonzalez
// Date: 10/10/2021
// Objective: Recover jpg files from a forensic image
// Input: Raw file as a command prompt argument
// Output: Restores the jpg files within the raw file

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Validate proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }
    
    // Open file
    FILE *file = fopen(argv[1], "r");
    
    // Validate file's validity
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    int curr_img = -1; // Latest image
    int block; // Memory block
    char str[10] = {"\0"};
    BYTE buffer[512];
    
    FILE *temp = NULL; // Files being read
    temp = fopen("001.jpg", "w");
    
    while (1)
    {
        block = fread(buffer, 512, 1, file);
        
        // Stop the cycle
        if (block == 0) 
        {
            break;
        }
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) // It's an image
        {
            curr_img++;
            fclose(temp);
            sprintf(str, "%03d.jpg", curr_img);
            printf("%03d.jpg", curr_img);
            temp = fopen(str, "w");

        }
        fwrite(buffer, 512, 1, temp);
    }
    printf("%d\n", curr_img);

    // Close file, end program
    fclose(file);
    return 0;
}