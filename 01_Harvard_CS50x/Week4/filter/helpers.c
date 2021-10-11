// Author: Jesus Carlos Martinez Gonzalez
// Date: 10/10/2021
// Objective: Implement multiple image filters

#include "helpers.h"
#include "math.h" // To access the round function

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            
            // For each pixel, get the average of its red, green, and blue values
            float sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            int avg = round(sum / 3);
            
            // Turn the pixel grey
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over every pixel
    for (int i = 0; i < height; i++)
    {
        int opposite = width - 1; // The pixel opposite to j
        for (int j = 0; j < opposite; j++)
        {
            // Swap j with opposite, using a temporary RGBTRIPLE temp
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][opposite];
            image[i][opposite] = temp;
            
            // Substact 1 to opposite to make it match the next j in the loop
            opposite--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{   
    RGBTRIPLE temp[height][width]; // Temporary image temp
    
    // Iterate over every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int neighbors = 0; // Number of pixels being taken into account for the given pixel
            float nbhd_blue = 0,  nbhd_green = 0, nbhd_red = 0; // Total values of each color for the current neighborhood
            
            // Iterate over the neighborhood for the current pixel
            for (int i_nb = -1; i_nb < 2; i_nb++)
            {
                for (int j_nb = -1; j_nb < 2; j_nb++)
                {
                    if (i + i_nb > height - 1 || i + i_nb < 0 || j + j_nb > width - 1 || j + j_nb < 0) // Ignore pixels outside of the grid
                    {
                        continue;
                    }
                    else // Add the values for each color to the neighbood's total
                    {
                        nbhd_blue += image[i + i_nb][j + j_nb].rgbtBlue;
                        nbhd_green += image[i + i_nb][j + j_nb].rgbtGreen;
                        nbhd_red += image[i + i_nb][j + j_nb].rgbtRed;
                        neighbors++;
                    }
                }
            }
            
            // Add the pixel to temp
            temp[i][j].rgbtBlue = round(nbhd_blue / neighbors);
            temp[i][j].rgbtGreen = round(nbhd_green / neighbors);
            temp[i][j].rgbtRed = round(nbhd_red / neighbors);
        }
    }

    // Copy temp to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    
    RGBTRIPLE temp[height][width]; // Temporary image temp
    
    // Iterate over every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float GxB = 0, GxG = 0, GxR = 0, GyB = 0, GyG = 0, GyR = 0; // Gx and Gy values for each color of the pixel
            
            // Sobel operator
            float sobel[3][3] =
            {
                {-1, 0, 1},
                {-2, 0, 2},
                {-1, 0, 1}
            };

            // Iterate over the neighborhood for the current pixel
            for (int i_nb = -1; i_nb < 2; i_nb++)
            {
                for (int j_nb = -1; j_nb < 2; j_nb++)
                {
                    if (i + i_nb > height - 1 || i + i_nb < 0 || j + j_nb > width - 1 || j + j_nb < 0) // Ignore pixels outside of the grid
                    {
                        continue;
                    }
                    else // Add the values for each color times its corresponding value in the sobel matrix to the neighbood's total 
                    {
                        GxB += image[i + i_nb][j + j_nb].rgbtBlue * sobel[i_nb + 1][j_nb + 1];
                        GxG += image[i + i_nb][j + j_nb].rgbtGreen * sobel[i_nb + 1][j_nb + 1];
                        GxR += image[i + i_nb][j + j_nb].rgbtRed * sobel[i_nb + 1][j_nb + 1];

                        GyB += image[i + i_nb][j + j_nb].rgbtBlue * sobel[j_nb + 1][i_nb + 1];
                        GyG += image[i + i_nb][j + j_nb].rgbtGreen * sobel[j_nb + 1][i_nb + 1];
                        GyR += image[i + i_nb][j + j_nb].rgbtRed * sobel[j_nb + 1][i_nb + 1];
                    }
                }
            }

            int blue = round(sqrt(pow(GxB, 2) + pow(GyB, 2)));
            int green = round(sqrt(pow(GxG, 2) + pow(GyG, 2)));
            int red = round(sqrt(pow(GxR, 2) + pow(GyR, 2)));

            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (red > 255)
            {
                red = 255;
            }

            if (blue < 0)
            {
                blue = 0;
            }
            if (green < 0)
            {
                green = 0;
            }
            if (red < 0)
            {
                red = 0;
            }

            // Add the pixel to temp
            temp[i][j].rgbtBlue = blue;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtRed = red;
        }
    }

    // Copy temp to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
