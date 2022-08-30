#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (argv[1][i] > 57 || argv[1][i] < 48)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    int len = strlen(plaintext);
    printf("ciphertext: ");
    for (int i = 0; i < len; i++)
    {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            printf("%c", 'a' - 1 + (((plaintext[i] - 'a' + 1) + key) % 26));
        }
        else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            printf("%c", 'A' - 1 + (((plaintext[i] - 'A' + 1) + key) % 26));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}
