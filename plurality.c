#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // check if name is valid
    //take input and check against each name in array
    for (int y = 0; y < candidate_count; y++)
    {
        if (strcmp(name, candidates[y].name) == 0)
        {
            // if yes, update vote total
            candidates[y].votes = (candidates[y].votes + 1);
            return true;
        }
    }
    //if no, return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Sort the list by votes
    int i = 0;
    string hold;
    int h;
    for (int y = 1; y < candidate_count; y++)
    {
        if (candidates[i].votes == candidates[y].votes)
        {
            h = candidates[i + 1].votes;
            candidates[i + 1].votes = candidates[y].votes;
            candidates[y].votes = h;
            hold = candidates[i + 1].name;
            candidates[i + 1].name = candidates[y].name;
            candidates[y].name = hold;
            i = i + 1;
        }
        else if (candidates[i].votes > candidates[y].votes)
        {
            continue;
        }
        else if (candidates[i].votes < candidates[y].votes)
        {
            h = candidates[i].votes;
            candidates[i].votes = candidates[y].votes;
            candidates[y].votes = h;
            hold = candidates[i].name;
            candidates[i].name = candidates[y].name;
            candidates[y].name = hold;
        }

    }
    //see if theres a tie
    for (int y = 0; y <= i; y++)
    {
        printf("%s\n", candidates[y].name);
    }
    return;
}