// Author: Jesus Carlos Martinez Gonzalez
// Date: 10/10/2021
// Objective: Modifies the volume of an audio file
// Input: Receives from the user the name of a source audio file, that of an expected output audio file and the modifying factor
// Output: Creates the modified file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Array of 8-bit unisigned integers to store the header at
    uint8_t header[HEADER_SIZE];
    
    // Reads from input, HEADER_SIZE elements of size 1 byte into the header array
    fread(header, 1, HEADER_SIZE, input);
    
    // Writes from the heder array, HEADER_SIZE elements of size 1 byte into output
    fwrite(header, 1, HEADER_SIZE, output);

    // Buffer in which samples are being stored
    int16_t samples;
    
    // Modifies each sample by factor and adds it to output
    while (fread(&samples, sizeof(int16_t), 1, input))
    {
        samples *= factor;
        fwrite(&samples, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
