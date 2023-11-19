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
            double red = image[column][row].rgbtRed;
            double green = image[column][row].rgbtGreen;
            double blue = image[column][row].rgbtBlue;

            // makeing the calculations, rounding the value and  returning the value to var avg
            int avg = round((red + green + blue) / 3);
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



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Copy of image
    RGBTRIPLE cpyimage[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            cpyimage[row][column] = image[row][column];
        }
    }

    //Gx and Gy factor
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    //looping through each row and column
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            int redRow = 0;
            int greenRow = 0;
            int blueRow = 0;
            int redColumn = 0;
            int greenColumn = 0;
            int blueColumn = 0;

            //looping through each pixel for neighbouring pixels
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    //checking for valid pixels
                    if (row - 1 + x < 0 || row - 1 + x > height - 1 || column - 1 + y < 0 || column - 1 + y > width - 1)
                    {
                        continue;
                    }

                    //Calculate Gx for each color
                    redRow = redRow + (image[row - 1 + x][column - 1 + y].rgbtRed * Gx[x][y]);
                    greenRow = greenRow + (image[row - 1 + x][column - 1 + y].rgbtGreen * Gx[x][y]);
                    blueRow = blueRow + (image[row - 1 + x][column - 1 + y].rgbtBlue * Gx[x][y]);

                    //calculate Gy for each color
                    redColumn = redColumn + (image[row - 1 + x][column - 1 + y].rgbtRed * Gy[x][y]);
                    greenColumn = greenColumn + (image[row - 1 + x][column - 1 + y].rgbtGreen * Gy[x][y]);
                    blueColumn = blueColumn + (image[row - 1 + x][column - 1 + y].rgbtBlue * Gy[x][y]);
                }
            }
            // Calculate square root of Gx2 and Gy2
            int red = round(sqrt((redRow * redRow) + (redColumn * redColumn)));
            int green = round(sqrt((greenRow * greenRow) + (greenColumn * greenColumn)));
            int blue = round(sqrt((blueRow * blueRow) + (blueColumn * blueColumn)));

            //maxout value at 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            //Copy values into ogimage
            cpyimage[row][column].rgbtRed = red;
            cpyimage[row][column].rgbtGreen = green;
            cpyimage[row][column].rgbtBlue = blue;
        }
    }

    //copy new pixels to  original image
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            image[row][column].rgbtRed = cpyimage[row][column].rgbtRed;
            image[row][column].rgbtGreen = cpyimage[row][column].rgbtGreen;
            image[row][column].rgbtBlue = cpyimage[row][column].rgbtBlue;
        }
    }
    return;
}
