// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *n = table[hash(word)];

    while( n != 0)
    {
        //ノードがある限り単語と比較
        if (strcasecmp(word, n -> word) == 0)
        {
            return true;
        }

        n = n -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int p = 0;
    for(int i = 0; i < strlen(word); i++)
    {
        p += 2 * word[i] * word[i] + 3 * word[i];
    }
    return (unsigned int)(p % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");

    if(file == NULL)
    {
        printf("Could not open %s\n", dictionary);
        return false;
    }
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if(n == NULL)
        {
            return false;
        }

        strcpy(n -> word, word);
        n -> next = table[hash(word)];
        table[hash(word)] = n;
        word_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if(word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n)
        {
            node *tmp = n;
            n = n -> next;
            free(tmp);
        }
        if (n == NULL)
        {
            return true;
        }
    }
    return false;
}
