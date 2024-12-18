// hash_utils.h
#ifndef HASH_UTILS_H
#define HASH_UTILS_H

#include "word_utils.h"

// Creates a linked list where each node represents a word
typedef struct Node
{
    char word[CHARS_PER_WORD];
    struct Node* next;
} Node;


// To search for words more effectively they are split into buckets by their lenght
typedef struct
{
    Node* buckets[CHARS_PER_WORD];
} WordHashTable;

void insertWord(WordHashTable* table, const char* word);
int searchWord(WordHashTable* table, const char* word);

#endif // HASH_UTILS_H