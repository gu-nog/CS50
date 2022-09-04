#include <stdio.h>
#include <cs50.h>
#include <string.h>
#define BIG_INT_LIMIT 5

int numbers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int linear_search(int v){
    for (int i = 0; i < 10; i++) 
    {
        if (numbers[i] == v) 
        {
            return 1;
        }
    }
    
    return 0;
}


typedef struct
{
    int number[BIG_INT_LIMIT];
    int size;
}
big_int;

big_int sum(big_int a, big_int b) // a needs to be bigger
{
    big_int c;
    int carry = 0;
    for (int i = 0; i < a.size; i++)
    {
        if (b.size >= i+1)
        {
            int r = a.number[i] + b.number[i] + carry;
            if (r >= 10)
            {
                c.number[i] = r - 10;
                c.size++;
                carry = 1;
            } 
            else
            {
                c.number[i] = r;
                c.size++;
                carry = 0;
            }
        }
        else
        {
            c.size++;
            c.number[i] = a.number[i] + carry;
            carry = 0;
        }
    }
    if (carry > 0)
    {
        c.number[a.size] = carry;
        c.size++;
    }
    
    return c;
}

int* selection_sort(int a[5])
{
    int start = 0;
    while (start != 4) 
    {
        int min[2] = {0, a[start]};
        for (int i = start; i < 5; i++)
        {
            if (a[i] < min[1])
            {
                min[0] = i;
                min[1] = a[i];
            }
        }
        a[min[0]] = a[start];
        a[start] = min[1];
        start++;
    }
    return a;
}

int* bubble_sort(int a[5])
{
    int end = 5;
    bool modified = true;
    while (modified)
    {
        modified = false;
        for (int i = 0; i <= end-2; i++)
        {
            if (a[i] > a[i+1])
            {
                modified = true;
                int first = a[i];
                a[i] = a[i+1];
                a[i+1] = first;
            }
        }
        end--;
    }
    return a;
}


int main(void){
    int n;
    n = get_int("Search in numbers: ");
    if (linear_search(n) == 0) 
    {
        printf("Not found :(\n");
    } else 
    {
        printf("Found :)\n");
    }

    // Comparing two strings, because as they are not std of c, it's different to compare an array of vars - string library
    if (strcmp("str", "str") == 0)
    {
        printf("'str' is equal to 'str' :)\n");
    }


    // Data structures - you can create your own type with information that you think are related all together
    typedef struct
    {
        string name;
        int age;
    }
    person; // name of it
    int guys_qty = get_int("People quantity: ");
    person people[guys_qty];
    for (int i = 0; i < guys_qty; i++)
    {
        people[i].name = get_string("Name of %i guy: ", i+1); // '.' acess this atribute of our struct
        people[i].age = get_int("Age of %i guy: ", i+1);
    }
    // but without functions/methods, so aren't classes
    big_int a;
    string a_str = get_string("a[xxxxx]: ");
    for (int i = 0; i < BIG_INT_LIMIT; i++)
    {
        if (a_str[(BIG_INT_LIMIT-1)-i] - 48 > 0)
        {
            a.size = i+1;
        }
        a.number[i] = a_str[(BIG_INT_LIMIT-1)-i] - 48;
    }
    big_int b;
    string b_str = get_string("b[xxxxx]: ");
    for (int i = 0; i < BIG_INT_LIMIT; i++)
    {
        if (b_str[(BIG_INT_LIMIT-1)-i] - 48 > 0)
        {
            b.size = i+1;
        }
        b.number[i] = b_str[(BIG_INT_LIMIT-1)-i] - 48;
    }
    big_int c;
    if (a.size >= b.size)
    {
        c = sum(a, b);
    }
    else
    {
        c = sum(b, a);
    }
    for (int i = c.size-1; i >= 0; i--)
    {
        printf("%i", c.number[i]);
    }

    int to_sort[5] = {5, 4, 1, 6, 3};
    printf("\nBefore: %i, %i, %i, %i, %i\n", to_sort[0], to_sort[1], to_sort[2], to_sort[3], to_sort[4]);
    // Faster searching: binary search in an sorted array O(log n)
    // Sort:
    // - Selection sort: go swapping(because to move, we'd need to realoc every other 
    // item instead of 2) the smallest item to the begin and moving the start of iteration
    int* sorted = selection_sort(to_sort);
    printf("After: %i, %i, %i, %i, %i\n", sorted[0], sorted[1], sorted[2], sorted[3], sorted[4]);
    // n steps + n-1 steps + .... n-n steps; > n²/2 + n/2 > O(n²)
    // Omega(n²)
    
    // - Bubble sort: go seeing the numbers in pairs and swapping then if the first is higher; repeat it ignoring 
    // -1 item per iteration until any swap
    int to_sort_2[5] = {5, 4, 1, 6, 3};
    printf("Before: %i, %i, %i, %i, %i\n", to_sort_2[0], to_sort_2[1], to_sort_2[2], to_sort_2[3], to_sort_2[4]);
    sorted = bubble_sort(to_sort_2);
    printf("After: %i, %i, %i, %i, %i\n", sorted[0], sorted[1], sorted[2], sorted[3], sorted[4]);
    // n²-2n+1 > O(n²)
    // Omega()

    // - with recursion(function call itself with a simpler problem and a base case), not procedural(step by step from top to bottom):
    // Merge sort: sort left, right and merge(iterating and seeing the 'first' item of each half) 
    // except if len is 1, then just return
    // merge complexity: O(n) because you only look about one time each element(the 1st's) and you merge log n times,
    // because you go dividing the list by 2

    // time ./executable gives the runtime of a program

    return 0;
}
