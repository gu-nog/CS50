#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");
    int letters = strlen(text);
    int sentences = 0;
    int words = 1;
    for (int i = 0, n = letters; i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
        if (!(text[i] >= 'a' && text[i] <= 'z') && !(text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters--;
        }
    }
    // printf("%i %i %i\n", letters, sentences, words);
    int level = round(0.0588 * (letters / (float) words * 100) - 0.296 * (sentences / (float) words * 100) - 15.8);
    if (level >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (level > 1)
    {
        printf("Grade %i\n", level);
    }
    else
    {
        printf("Before Grade 1\n");
    }
}
