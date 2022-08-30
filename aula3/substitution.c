#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if ((!(argv[1][i] <= 'Z' && argv[1][i] >= 'A') && !(argv[1][i] <= 'z' && argv[1][i] >= 'a')))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        for (int c = 0, n = i; c < n; c++)
        {
            if (argv[1][i] == argv[1][c])
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }
    string key = argv[1];
    string plaintext = get_string("plaintext: ");
    int len = strlen(plaintext);
    printf("ciphertext: ");
    for (int i = 0; i < len; i++)
    {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            printf("%c", tolower(key[plaintext[i] - 'a']));
        }
        else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            printf("%c", toupper(key[plaintext[i] - 'A']));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}
