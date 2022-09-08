#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void print_arr(int *list, int size);
void push_item(int *list, int size, int n);

int main(void)
{
    // add item to array:
    // could just use Omega(1) when next item is free to O(n) when we need to realloc all data another time
    // 1st - initialize array
    int len = 3;
    int *list = malloc(sizeof(int) * len);
    if (list == NULL)
    {
        return 1;
    }
    for (int i = 0; i < len; i++)
    {
        list[i] = i + 1;
    }
    print_arr(list, len);

    // 2nd - add item
    // with malloc and auxiliar array only:
        // int *aux = malloc(sizeof(int) * len + 1);
        // if (aux == NULL)
        // {
        //     return 1;
        // }
        // for (int i = 0; i < len; i++)
        // {
        //     aux[i] = list[i];
        // }
        // len++;
        // aux[3] = 4;
        // free(list);
        // list = aux;
        // print_arr(list, len);
    // with realloc: try to just add the new item or return a new address with the first array restored
    len++;
    list = realloc(list, len * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }
    list[3] = 4;
    print_arr(list, len-1);
    free(list);


    // Be faster don't moving things on memory
    // Tip: -> operator access an atribute of an adress object (*n).atribute = n->atribute
    // Linked list: A item point to the next one(so it can be anywhere in mem)
    typedef struct node
    {
        int n;
        struct node *next; // this is to have declared this struct as a type when
        // we are declaring itself, because the computer needs to know that has n and next in another node, not just n
    }
    node;

    printf("%lu\n", sizeof(node)); // 16 bytes: int(4) + pointer(8) + next_int(4)

    node *linked_list = NULL; // empty
    node *n = malloc(sizeof(node));
    n->n = 2;
    n->next = NULL;
    linked_list = n;

    // - add number: O(1) if order doesn't matter, else is O(n) to maintain sorted
    n = malloc(sizeof(node));
    n->n = 4;
    n->next = NULL;
    linked_list->next = n;

    // - more one
    n = malloc(sizeof(node));
    n->n = 6;
    n->next = NULL;
    linked_list->next->next = n;

    // - see the list > this is O(n) used for search, because is impossible to do bin search
    for (node *tmp = linked_list; tmp != NULL; tmp = tmp->next) // until a null node, go to next
    {
        printf("%i, ", tmp->n);
    }

    // - free
    while (linked_list != NULL)
    {
        node *tmp = linked_list->next;
        free(linked_list);
        linked_list = tmp;
    }



    return 0;
}

void print_arr(int *list, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%i, ", list[i]);
    }
    printf("\n");
}
