//
// Created by tyyp- on 21.09.2020.
//

#ifndef SPELLER_DICTIONARY_H
#define SPELLER_DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}node;

// Prototypes
void * AllocateMemory(size_t size);
node * InitializeSllNode(const char * word);
node * InsertItemToHead( node * pHead,const char * word);
bool SearchWord(node * pHead,const char * word);
void DestroySllItem(node * pItem);


bool load(const char *dictionary);
unsigned int size(void);
bool check(const char *word);
bool unload(void);

void printTest();

#endif //SPELLER_DICTIONARY_H
