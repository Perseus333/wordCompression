// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../include/compression.h"
#include "../include/word_utils.h"
#include "../include/hash_utils.h"

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
    writeOutputFile(orderedList);

    clock_t endTime = clock();
    double elapsed_seconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.6f seconds\n", elapsed_seconds);

    double ratio = calculateCompressionRatio();
    printf("Compression rate: %.3f%%\n", ratio*100);
    
    // For debugging purposes
    // for (int i = 0; i < TOTAL_WORDS; i++) printf("%s\n", orderedList->words[i]);

    // Free the dynamically allocated elements
    free(wordList);
    free(orderedList);
    for (int bucketIndex = 0; bucketIndex < CHARS_PER_WORD; bucketIndex++)
        free(table.buckets[bucketIndex]);
    
    return 0;
}