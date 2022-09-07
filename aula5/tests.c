#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(void)
{
    // how do we represent familiar things as images with a limit amount of memory
    int n = 10;
    int *p = &n;

    printf("%p=%i\n", p, *p);

    int to_alloc = 3;

    int *pointer = malloc(to_alloc * sizeof(int));
    if (pointer == NULL)
    {
        printf("Memory denied!");
        return 1;
    }
    printf("%p\n", pointer);
    for (int i = 0; i < to_alloc; i++)
    {
        pointer[i] = 0;
        printf("%p>%i\n", pointer+i, pointer[i]);
    }
    free(pointer);
    printf("\n");


    return 0;
}
