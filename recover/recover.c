#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Checking to see if you entered 2 comandline aruguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    //opening input_file
    FILE *input_file = fopen(argv[1], "r");

    //Checking if file is valid
    if (input_file == NULL)
    {
        printf("Could not open file\n");
        return 2;
    }
    //make buffer of 512 bytes in an array
    BYTE buffer[512];

    //Counter for counting images found
    int count_image = 0;

    //File pointer for recovered images
    FILE *output_file = NULL;

    //Char filename[8]
    char *filename = malloc(8 * sizeof(char));

    //Reading blocks of 512 bytes
    while (fread(buffer, sizeof(BYTE) * 512,  1, input_file) == 1)
    {
        //Looking for the begin of image
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Check if output can be used for valid input
            if (output_file != NULL)
            {
                fclose(output_file);
            }
            //Writing iamge to file
            sprintf(filename, "%03i.jpg", count_image++);

            //open output_file for writing
            output_file = fopen(filename, "w");
        }
        //Writing until new image is found
        if (output_file != NULL)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, output_file);
        }
    }
    //closing last open output_file
    if (output_file != NULL)
    {
        fclose(output_file);
    }
    // freeing memory from malloc and closing the input_file that was opened
    free(filename);
    fclose(input_file);

    return 0;
}