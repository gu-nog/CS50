#include <stdio.h>
#include <cs50.h>

void print_chars(string str, int times)
{ 
    // print a character x times
    for (int i = 0; i < times; i++)
    {
        printf("%s", str);
    }
}

int main(void)
{
    int height;
    do 
    {
        height = get_int("height: ");
    } 
    while (height > 8 || height < 1); // verifies if it is a valid height
    for (int i = 1; i <= height; i++)
    {
        print_chars(" ", height - i);
        print_chars("#", i);
        printf("  ");
        print_chars("#", i);
        printf("\n");
    }
}
