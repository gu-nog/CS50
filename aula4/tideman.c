#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Tally: once voters have indicated preferences, get winner for each pair
// Sort: Sort these pairs in decreasing strength
// Lock: add each edge, pointing to the loser of each pair, if it doesn't create a cycle
// Winner: no arrows to him
// preferences[i][j] > how many i over than j

// graph: locked[i][j] > true when an edge goes from i to j

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
bool cycle(int target, int origin);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // if found, return true and update ranks[i], where i=0, is the first preference
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    
    // else, return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (j != i)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    // add pair(winner and loser indexes) to pairs array
                    pairs[pair_count].loser = j;
                    pairs[pair_count].winner = i;
                    // update pair_count array
                    pair_count++;
                }
            }
        }
    }
    
    return;
}

// Sort pairs in decreasing order by strength(more people prefered the winner) of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int max = -1;
        int max_index = 0;
        for (int j = i; j < pair_count; j++)
        {
            int strength = preferences[pairs[j].winner][pairs[j].loser];
            if (strength > max)
            {
                max = strength;
                max_index = j;
            }
        }
        int initial_loser = pairs[i].loser;
        int initial_winner = pairs[i].winner;
        pairs[i].loser = pairs[max_index].loser;
        pairs[i].winner = pairs[max_index].winner;
        pairs[max_index].loser = initial_loser;
        pairs[max_index].winner = initial_winner;
    }
    
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles()
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

bool cycle(int target, int origin)
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[origin][j])
        {
            if (j == target)
            {
                return true;
            }
            else if (cycle(target, j))
            {
                return true;
            }
        }
    }

    return false;
};

// Print the winner of the election
void print_winner(void)
{
    // source of graph - any edges pointing to them
    for (int j = 0; j < candidate_count; j++)
    {
        bool winner = true;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j])
            {
                winner = false;
            }
        }
        if (winner)
        {
            printf("%s\n", candidates[j]);
        }
    }
    return;
}