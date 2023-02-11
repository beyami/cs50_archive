/*
選挙を実施し、
同票の候補者がいた場合
tideman方式で当選者を決めるプログラム
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
bool check_cycle(int s);
bool check_visit(int s, bool visit[MAX][MAX]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void merge_sort(pair x[], int left, int right);
int search_winner(int w);

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)  //もし与えられた名前が候補者名と一致したら
        {
            ranks[rank] = i;  //その希望順位を記録
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)  //すべての候補者と候補者の組み合わせについてなので-1
    {
        for (int j = i + 1; j < candidate_count; j++)  //同様にj = i+1から
        {
            preferences[ranks[i]][ranks[j]]++;  //rank[j]にいるのは全てrank[i]に負けたものなのでそれらを++
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int i, j, k = 0;
    for (i = 0; i < candidate_count; i++)
    {
        for (j = 0; j < candidate_count; j++)
        {
            //すべての候補者の二重ループに対し
            if (i == j)
            {
                //同じ候補者は対立しないのでスルー
                continue;
            }
            if (preferences[i][j] > preferences[j][i])
            {
                //もし優劣が存在したらそれをpairsに記録
                pairs[k].winner = i;
                pairs[k].loser = j;
                k++;
            }
        }
    }

    pair_count = k;

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    merge_sort(pairs, 0, pair_count - 1);
    //この関数はソートを呼び出すだけ(再帰したいのでもう一個関数を作る必要がある ))
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        //すべてのペアに対し
        locked[pairs[i].winner][pairs[i].loser] = true;  //lockをtrueに
        if (check_cycle(pairs[i].loser))
        {
            //ただし、もしそのロックでサイクルが生成された場合取り消し
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int i, j;
    for (i = 0; i < candidate_count; i++)
    {
        for (j = 0; j < candidate_count; j++)
        {
            //ロックされているどこかのijのペアを探す
            if (locked[i][j])
            {
                //見つけたらループ抜ける
                break;
            }
        }
        if (locked[i][j])
        {
            break;
        }
    }
    int winner = search_winner(i);//そのiからwinnerを探す

    printf("%s\n", candidates[winner]);//表示
    return;
}

void merge_sort(pair x[], int left, int right)
{
    //マージソートするだけ
    int i, j, k, mid;
    pair temp[pair_count];//比較用の配列

    if (left >= right)
    {
        //渡されたインデックスがすでに終了を意味していたらおしまい
        return;
    }

    mid = (left + right) / 2;

    //左右にマージし再帰
    merge_sort(x, left, mid);
    merge_sort(x, mid + 1, right);

    //真ん中分けで後ろ半分は降順に
    for (i = mid; i >= left; i--)
    {
        temp[i] = x[i];
    }

    for (j = mid + 1; j <= right; j++)
    {
        temp[right - (j - (mid + 1))] = x[j];
    }

    i = left;
    j = right;

    for (k = left; k <= right; k++)
    {
        if (preferences[temp[i].winner][temp[i].loser] >= preferences[temp[j].winner][temp[j].loser])
        {
            x[k] = temp[i++];
            //降順に並び替え
        }
        else
        {
            x[k] = temp[j--];
        }
    }

    return;
}

bool check_cycle(int s)
{
    bool visit[MAX][MAX] = {0};
    return check_visit(s, visit);
    //配列を用意,初期化して再帰を呼び出し
}

bool check_visit(int s, bool visit[MAX][MAX])
{
    for (int i = 0; i < candidate_count; i++)//すべての候補者について
    {
        if (locked[s][i])//ｓがiに勝っていて
        {
            if (visit[s][i])//かつ訪れたことがあればサイクルあり、真を返す
            {
                return true;
            }
            else
            {
                //そうでなければ訪れたことにし
                visit[s][i] = true;
                if (check_visit(i, visit))//再帰呼び出し、サイクルあればそこでおしまい、真を返す
                {
                    return true;
                }
            }
        }
    }

    //ループを抜ける=サイクル無なら偽を返す
    return false;
}

int search_winner(int w)
{
    bool search = false;
    while (!search) //勝者が見つかるまで
    {
        for (int i = 0; i < candidate_count; i++) //すべての候補者について
        {
            if (locked[i][w])  //渡されたwに勝ってるやつがいれば
            {
                //wとiを交換しfor文をぬける　ただしみつかってないのでまた最初から
                w = i;
                break;
            }
        }
        //もしfor文を終えたら==wが真の勝者なら見つかったフラグを立てwhileを抜ける
        search = true;
    }

    //勝者を返す
    return w;
}
