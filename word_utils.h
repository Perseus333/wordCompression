// word_utils.h
#include <stdio.h>

#ifndef WORD_UTILS_H
#define WORD_UTILS_H

#define CHARS_PER_WORD 20
#define FILE_NAME_MAX_LEN 16

typedef struct
{
    char words[1][CHARS_PER_WORD];
} WordList;

WordList* allocateWordList(int wordListSize);
FILE* readFile(int wordListSize);
void populateWordList(FILE* file, WordList* wordList, int wordListSize);

#endif // UTILS_H