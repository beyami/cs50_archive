/*
候補者名と投票を受け取り、
多数決として当選者を決めるプログラム
使い方:
./plurality [候補者1 候補者2…]
Number of voters: [候補者数]
Vote: [候補者名]

*/

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
    // TODO
    //候補者の数だけループ
    for (int i = 0; i < candidate_count; i++)
    {
        //候補者と同じ名前の票が入ったら
        if (strcmp(candidates[i].name, name) == 0)
        {
            //その名前の候補者の投票数をインクリメント
            candidates[i].votes++;
            return true;
        }

    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int winner = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        //候補者全員に対しループ
        if (candidates[i].votes > winner)  //今の最大値より得票数が大きければ
        {
            winner = candidates[i].votes;
            //最大値を記録
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == winner)    //最大値と得票数が同じならば
        {
            printf("%s\n", candidates[i].name);
            //その候補者の名前を表示
        }
    }
    return;
}
