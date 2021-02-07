//
// Created by tyyp- on 21.09.2020.
//

// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>

// Represents number of buckets in a hash table
#define N 26


void * AllocateMemory(size_t size)
{
    void * pvMem = malloc(size);
    if (!pvMem)
        exit(1);
    return pvMem;
}




//Initializes a sll node item to given word.
node * InitializeSllNode(const char * word)
{
    node * pHead = AllocateMemory(sizeof(node));
    strcpy(pHead->word, word);
    pHead->next = NULL;

    return pHead;
}

//Inserts a data sll which is already created-initialized.
node * InsertItemToHead( node * pHead,const char * word)
{
    node * pItem = InitializeSllNode(word);
    pItem->next = pHead;
    pHead = pItem;
    return pHead;
}

//Search a word data in sll.
bool SearchWord(node * pHead,const char * word)
{
    while (NULL != pHead)
    {
        for (int i = 0; i < strlen(word); ++i) {
            if (word[i] != pHead->word[i])
                return false;
        }
        pHead = pHead->next;
    }
    return true;
}

//Destroys one sll item.
void DestroySllItem(node * pItem)
{
    pItem->next = NULL;
    free(pItem);
}

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    unsigned int hashIndex;
    node * pHead;
    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {

        //Determine  hash location.
        hashIndex = hash(word);
        pHead = hashtable[hashIndex];
        if ( ! pHead )
            hashtable[hashIndex] = InitializeSllNode(word);

        else
            hashtable[hashIndex] = InsertItemToHead(pHead, word);
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    node * pIter;
    unsigned int counter = 0;
    // TODO
    for (int i = 0; i < N; ++i) {
        pIter = hashtable[i];
        while ( NULL != pIter)
        {
            counter++;
            pIter = pIter->next;
        }
    }

    return counter;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    unsigned hashIndex = hash(word);
    return  ( SearchWord (hashtable[hashIndex] ,word ) );

}


void printTest()
{
    node * pIter;
    for (int i = 0; i < N; ++i) {
        while ( hashtable[i] != NULL)
        {
            printf("hashtable[%d] -> %s          ",i, hashtable[i]->word);
            hashtable[i] = hashtable[i]->next;
        }
        printf("\n");
    }
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node * pIter;
    for (int i = 0; i < N; ++i) {
        while ( hashtable[i] != NULL)
        {
            pIter = hashtable[i];
            hashtable[i] = hashtable[i]->next;
            free(pIter);
        }
        pIter = NULL;
    }
    return true;
}


