#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int pontuation(string s) 
{
    int points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int len = strlen(s);
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        if (toupper(s[i]) >= 65 && toupper(s[i]) <= 90)
        {
            sum += points[toupper(s[i]) - 65];
        }
    }
    return sum;
}

int main(void)
{
    int first = pontuation(get_string("Player 1: "));
    int second = pontuation(get_string("PLayer 2: "));
    if (first == second)
    {
        printf("Tie!\n");
    }
    else if (first > second)
    {
        printf("Player 1 wins!");
    }
    else
    {
        printf("Player 2 wins!");
    }
}
