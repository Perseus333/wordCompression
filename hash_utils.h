#ifndef HASH_UTILS

#include <stdlib.h>
#include <string.h>
#include "word_utils.h"

// Ask GPT to explain this better
typedef struct Node {
    char word[CHARS_PER_WORD];
    struct Node* next;
} Node;

typedef struct {
    Node* buckets[TOTAL_WORDS];
} WordHashTable;

void insertWord(WordHashTable* table, const char* word)
{
    int bucketIndex = strlen(word);
    
}

#endif // HASH_UTILS