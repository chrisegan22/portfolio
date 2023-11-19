#include "helpers.h"
#include <stdio.h>
#include <math.h>


//defining Global varibles red green blue
#define RED_COLOR 0
#define GREEN_COLOR 1
#define BLUE_COLOR 2

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // going through rows
    for (int row = 0; row < width; row++)
    {
        // going through columns
        for (int column = 0; column < height; column++)
        {
            //making var to place the values in before calculation
            int red = image[column][row].rgbtRed;
            int green = image[column][row].rgbtGreen;
            int blue = image[column][row].rgbtBlue;

            // makeing the calculations, rounding the value and  returning the value to var avg
            int avg = round(((double)red + (double)green + (double)blue) / 3);
            {
                // replacing the values with avg value
                image[column][row].rgbtBlue = avg;
                image[column][row].rgbtGreen = avg;
                image[column][row].rgbtRed = avg;
            }
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // going through rows
    for (int row = 0; row < width; row++)
    {
        // going through columns
        for (int column = 0; column < height; column++)
        {
            //making var to place the values in before calculation
            int red = image[column][row].rgbtRed;
            int green = image[column][row].rgbtGreen;
            int blue = image[column][row].rgbtBlue;

            // making calculations to sepia
            int sepiaRed = round(0.393 * red + 0.769 * green + 0.189 * blue);

            // Checking to see if value is above 255
            if (sepiaRed > 255)
            {
                //Setting value to 255 if it is above 255
                image[column][row].rgbtRed = 255;
            }
            else
            {
                // Else setting rgbtRed value to sepiaRed
                image[column][row].rgbtRed = sepiaRed;
            }

            //Making calculations for SepiaGreen (same as above)
            int sepiaGreen = round(0.349 * red + 0.686 * green + 0.168 * blue);

            //Checking to see if value is above 255
            if (sepiaGreen > 255)
            {
                //Setting value to 255 if it is above 255
                image[column][row].rgbtGreen = 255;
            }
            else
            {
                //Else setting rgbtGreem value to sepiaGreen
                image[column][row].rgbtGreen = sepiaGreen;
            }

            //Making calculations for sepiaBlue (same as above)
            int sepiaBlue = round(0.272 * red + 0.534 * green + 0.131 * blue);

            //Checking to see if value is above 255
            if (sepiaBlue > 255)
            {
                //Setting value to 255 if it is above 255
                image[column][row].rgbtBlue = 255;
            }
            else
            {
                //Else setting rgbtBlue to sepiaBlue
                image[column][row].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // looping through columns
    for (int column = 0; column < height; column++)
    {
        //looping through rows
        for (int row = 0; row < (width / 2); row++)
        {
            // temp var
            RGBTRIPLE temp = image[column][row];

            //swapping rows
            image[column][row] = image[column][width - (row + 1)];
            image[column][width - (row + 1)] = temp;
        }
    }
    return;
}

//Blur calculation function
int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_pos)
{
    //Counter pixels
    float count = 0;
    int sum = 0;

    //Looping through rows from the pixels working on
    for (int row = i - 1; row <= (i + 1); row++)
    {
        //Looping through columns where working on
        for (int column = j - 1; column <= (j + 1); column++)
        {
            //Checking if out of bound from the borders working on
            if (row < 0 || row >= height || column < 0 || column >= width)
            {
                continue;
            }
            //checking which color working on
            if (color_pos == RED_COLOR)
            {
                sum += image[row][column].rgbtRed;
            }
            else if (color_pos == GREEN_COLOR)
            {
                sum += image[row][column].rgbtGreen;
            }
            else
            {
                sum += image[row][column].rgbtBlue;
            }
            count++;
        }
    }
    //Returning the blur calculation back to Blur fuction
    return round(sum / count);
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //An array to store copy of original image
    RGBTRIPLE ogimage[height][width];

    //Looping through columns
    for (int row = 0; row < height; row++)
    {
        //Looping through rows
        for (int column = 0; column < width; column++)
        {
            // origianl values
            ogimage[row][column] = image[row][column];
        }
    }
    //Looping through rows
    for (int row = 0; row < height; row++)
    {
        //Looping through columns
        for (int column = 0; column < width; column++)
        {
            //Changing value of pixels to calculated values
            image[row][column].rgbtRed = getBlur(row, column, height, width, ogimage, RED_COLOR);
            image[row][column].rgbtGreen = getBlur(row, column, height, width, ogimage, GREEN_COLOR);
            image[row][column].rgbtBlue = getBlur(row, column, height, width, ogimage, BLUE_COLOR);
        }
    }
    return;
}
