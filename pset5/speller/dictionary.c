// Implements a dictionary's functionality

#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26 * 26 * 26;

// Hash table
node *table[N];

// Size of the dictionary;
unsigned int size_n = 0;

// To indicate if the dictionary is loaded.
bool load_flag = false;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hash_n = hash(word);
    for (node *tmp = table[hash_n]; tmp != NULL; tmp = tmp->next)
    {
        if (!strcasecmp(word, tmp->word))
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned int number = 0;
    for (int i = 0; i < 3 && word[i] != '\0'; i++)
    {
        number += (tolower(word[i]) - 'a') * pow(26, i);
    }
    if (number > N - 1)
    {
        number = number % N;
    }
    return number;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        printf("Error: can't open file.\n");
        return false;
    }

    char tmp_word[LENGTH + 1] = {0};
    unsigned int hash_n = 0;
    // Reading strings from file one at a time.
    while (fscanf(input, "%s", tmp_word) != EOF)
    {
        // Create a new node for each word and obtain its hash value
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Error: can't allocate memory.\n");
            fclose(input);
            return false;
        }
        strcpy(n->word, tmp_word);
        n->next = NULL;
        hash_n = hash(tmp_word);
        size_n++;

        // Insert node into hash table at that location
        if (table[hash_n] == NULL)
        {
            table[hash_n] = n;
        }
        else
        {
            n->next = table[hash_n]->next;
            table[hash_n]->next = n;
        }

    }
    fclose(input);
    load_flag = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (load_flag)
    {
        return size_n;
    }
    else
    {
        printf("Not yet loaded\n");
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    if (load_flag)
    {
        for (int i = 0; i < N; i++)
        {
            while (table[i] != NULL)
            {
                node *tmp = table[i]->next;
                free(table[i]);
                table[i] = tmp;
            }
        }
        
        load_flag = false;
        return true;
    }
    
    else
    {
        return false;
    }
}
