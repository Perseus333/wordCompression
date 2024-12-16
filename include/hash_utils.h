// hash_utils.h
#include "word_utils.h"

#ifndef HASH_UTILS_H
#define HASH_UTILS_H

typedef struct Node
{
    char word[CHARS_PER_WORD];
    struct Node* next;
} Node;

typedef struct
{
    // Create as many buckets as word lenghts
    Node* buckets[CHARS_PER_WORD];
} WordHashTable;

void insertWord(WordHashTable* table, const char* word);
int searchWord(WordHashTable* table, const char* word);

#endif // HASH_UTILS_H