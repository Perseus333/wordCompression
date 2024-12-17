// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../include/word_utils.h"
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

// Compressing the words by 
void compressWords(WordHashTable* table, WordList* outputList)
{
    int outputListIndex = 0;
    /*
    We skip the first bucket because it contains single-character words and they cannot be compressed.
    The second bucket contains 2 character long words, which also cannot be compressed because the first bucket *should* contain all possible characters. Therefore it is also skipped.
    */
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
                int foundWord = searchWord(table, candidate);
                if ((foundWord == 1) && (strlen(candidate) < strlen(currentNode->word)))
                {
                    candidateLen++;
                }
                else
                {
                    strncpy(outputList->words[outputListIndex], candidate, CHARS_PER_WORD);
                    outputListIndex++;
                    validCandidate = true;
                }
            }
            currentNode = currentNode->next; 
        }
    }
}


int main()
{
    WordHashTable table = {0};
    clock_t startTime = clock();
    
    FILE* wordListFile = readFile(TOTAL_WORDS);
    WordList* wordList = allocateWordList(TOTAL_WORDS);
    populateWordList(wordListFile, wordList, TOTAL_WORDS);
    
    groupByLen(&table, wordList);
    WordList* orderedList = allocateWordList(TOTAL_WORDS);
    compressWords(&table, orderedList);

    clock_t endTime = clock();
    double elapsed_seconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.6f seconds\n", elapsed_seconds);
    
    // For debugging purposes
    // for (int i = 0; i < TOTAL_WORDS; i++) printf("%s\n", orderedList->words[i]);

    // Free the dynamically allocated elements
    free(wordList);
    free(orderedList);
    for (int bucketIndex = 0; bucketIndex < CHARS_PER_WORD; bucketIndex++)
        free(table.buckets[bucketIndex]);
    
    return 0;
}