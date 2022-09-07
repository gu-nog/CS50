#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open card.raw
    FILE *card = fopen(argv[1], "r");
    const int CHUNKS_SIZE = 512;
    BYTE last_chunk[CHUNKS_SIZE];
    int file_counter = 0;
    FILE *recover_file;

    // Until EOF, read 512 bytes
    while (fread(last_chunk, 1, CHUNKS_SIZE, card) == CHUNKS_SIZE)
    {
        // if start new JPEG
        if (last_chunk[0] == 0xff && last_chunk[1] == 0xd8 && last_chunk[2] == 0xff
            && (last_chunk[3] & 0xf0) == 0xe0)
        {
            // if first
            if (file_counter == 0)
            {
                recover_file = fopen("000.jpg", "w");
                fwrite(last_chunk, 1, CHUNKS_SIZE, recover_file);
            }
            // else
            else
            {
                fclose(recover_file);
                char *filename = malloc(8);
                sprintf(filename, "%03i.jpg", file_counter);
                recover_file = fopen(filename, "w");
                free(filename);
                fwrite(last_chunk, 1, CHUNKS_SIZE, recover_file);
            }
            file_counter++;
        }
        // else, if already found the first JPEG
        else if (file_counter != 0)
        {
            fwrite(last_chunk, 1, CHUNKS_SIZE, recover_file);
        }
    }
    // clean open files
    if (file_counter != 0)
    {
        fclose(recover_file);
        fclose(card);
    }
}
