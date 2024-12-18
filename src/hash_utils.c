// hash_utils.c
#include <stdlib.h>
#include <string.h>
#include "../include/hash_utils.h"

// Inserts the word in the corresponding bucket automatically
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

    strcpy(newNode->word, word);
    // Assigns a new next mode at the end of the linked-list bucket
    newNode->next = table->buckets[bucketIndex];
    table->buckets[bucketIndex] = newNode;
}

// Searches for a word in the word table
int searchWord(WordHashTable* table, const char* word)
{
    int length = strlen(word);
    int bucketIndex = length - 1; 

    Node* currentWord = table->buckets[bucketIndex];
    while (currentWord)
    {
        if (strncmp(currentWord->word, word, CHARS_PER_WORD) == 0)
        {
            return 1; // found 
        }
        currentWord = currentWord->next;
    }
    return 0; // not found
}
