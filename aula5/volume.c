// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef int8_t BYTE;
typedef int16_t BYTE_2;

int main(int argc, char *argv[])
{
    // argc = 4;
    // argv[1] = "input.wav";
    // argv[2] = "out.wav";
    // argv[3] = "2.0";
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
    printf("%f\n", factor);


    // TODO: Copy header from input file to output file
    BYTE header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    BYTE_2 sample;
    // TODO: Read samples from input file and write updated data to output file
    while (fread(&sample, sizeof(BYTE_2), 1, input) == 1)
    {
        printf("%u>", sample);
        sample = sample * factor;
        printf("%u\n", sample);
        fwrite(&sample, sizeof(BYTE_2), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
