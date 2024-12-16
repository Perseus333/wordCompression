// hash_utils.c
#include <stdlib.h>
#include <string.h>
#include "../include/hash_utils.h"

void insertWord(WordHashTable* table, const char* word)
{
    int length = strlen(word);
    int bucketIndex = length - 1;

    Node* newNode = malloc(sizeof(Node));
    if (!newNode)
    {
        fprintf(stderr, "Node memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // Ask GPT to explain this block of code better
    strcpy(newNode->word, word);
    newNode->next = table->buckets[bucketIndex];
    table->buckets[bucketIndex] = newNode;
}

int searchWord(WordHashTable* table, const char* word)
{
    int length = strlen(word);
    int bucketIndex = length - 1; 

    Node* currentWord = table->buckets[bucketIndex];
    while (currentWord)
    {
        if (strncmp(currentWord->word, word, CHARS_PER_WORD) == 0)
        {
            return 1; // Word found 
        }
        currentWord = currentWord->next;
    }
    return 0; // Word not found
}

