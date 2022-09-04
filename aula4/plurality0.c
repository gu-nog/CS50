#include <stdio.h>
#include <cs50.h>
#include <string.h>

typedef struct
{
    string name;
    int votes;
}
candidate;

candidate candidates[9];

int main(int argc, string argv[]){
    int winner_votes = 0;
    for (int i = 1; i < argc; i++)
    {
        candidates[i-1].name = argv[i];
        candidates[i-1].votes = 0;
    }

    int total_votes = get_int("Number of voters: ");

    for (int c = 0; c < total_votes; c++)
    {
        string vote = get_string("Vote: ");
        bool valid = false;
        // search for this candidate and count the vote or reject it
        for (int i = 0; i < argc-1; i++)
        {
            if (strcmp(candidates[i].name, vote) == 0)
            {
                candidates[i].votes++;
                if (candidates[i].votes > winner_votes)
                {
                    winner_votes = candidates[i].votes;
                }
                valid = true;
            }
        }
        if (!valid)
        {
            printf("Invalid vote.\n");
            c--;
        }
    }

    for (int i = 0; i < argc-1; i++)
    {
        if (candidates[i].votes >= winner_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    
    
    return 0;
}
