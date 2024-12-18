// word_utils.h
#include <stdio.h>

#ifndef WORD_UTILS_H
#define WORD_UTILS_H

// Change this values to configure the program
#define TOTAL_WORDS 10000
#define CHARS_PER_WORD 20
#define FILE_NAME_MAX_LEN 16
#define DATA_DIR "data"
#define OUTPUT_DIR "output"

typedef struct
{
    char words[1][CHARS_PER_WORD];
} WordList;

WordList* allocateWordList(int wordListSize);
FILE* readFile(int wordListSize);
void writeOutputFile(WordList* finalWordList);
void populateWordList(FILE* file, WordList* wordList, int wordListSize);

#endif // WORD_UTILS