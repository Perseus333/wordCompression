// compression.c
#include <stdbool.h>
#include <string.h>
#include "../include/hash_utils.h"

// Ordering the words by length in linked-list buckets
void groupByLen(WordHashTable* table, WordList* wordList)
{
    for (unsigned int wordIndex = 0; wordIndex < TOTAL_WORDS; wordIndex++)
    {
        const char* word = wordList->words[wordIndex];
        insertWord(table, word);
    }
}


// Compressing the words
void compressWords(WordHashTable* table, WordList* outputList)
{
    int outputListIndex = 0;
    // To keep track of duplicates
    WordHashTable compressedWordsTable = {0};
    /*
    We don't modify the first bucket because it contains single-character words and they cannot be compressed.
    The second bucket contains 2 character long words, which also cannot be compressed because the first bucket *should* contain all possible characters. Therefore it is also unaltered.
    */
    for (int bucketIndex = 0; bucketIndex < 2; bucketIndex++)
    {
        Node* currentNode = table->buckets[bucketIndex];

        while(currentNode)
        {
            strncpy(outputList->words[outputListIndex], currentNode->word, CHARS_PER_WORD);
            insertWord(&compressedWordsTable, currentNode->word);
            outputListIndex++;
            currentNode = currentNode->next;
        }
    }

    // From bucket 2 (length >= 3) onwards they can be compressed
    for (int bucketIndex = 2; bucketIndex < CHARS_PER_WORD; bucketIndex++)
    {
        Node* currentNode = table->buckets[bucketIndex];
        
        while (currentNode)
        {
            char candidate[CHARS_PER_WORD] = {0};

            bool validCandidate = false;
            // We start the candidates at length two because all single-character words (letters) should be already taken
            int candidateLen = 2;
            
            while (!validCandidate)
            {
                strncpy(candidate, currentNode->word, candidateLen);
                // 0 = not found; 1 = found
                int foundWord = searchWord(&compressedWordsTable, candidate);
                if ((foundWord == 1) && (strlen(candidate) < strlen(currentNode->word)))
                {
                    candidateLen++;
                }
                else
                {
                    strncpy(outputList->words[outputListIndex], candidate, CHARS_PER_WORD);
                    insertWord(&compressedWordsTable, candidate);
                    outputListIndex++;
                    validCandidate = true;
                }
            }
            currentNode = currentNode->next; 
        }
    }
}
