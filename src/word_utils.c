// word_utils.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/word_utils.h"

WordList* allocateWordList(int wordListSize)
{
    // the size of the WordList words is defined by the size of the WordList type, and the total amount of cells, which are words * characters
    WordList* words = calloc(1, sizeof(WordList) + (sizeof(char[CHARS_PER_WORD])) * (wordListSize - 1));
    if (!words) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return words;
}

FILE* readFile(int wordListSize)
{
    char fileName[FILE_NAME_MAX_LEN]; 
    sprintf(fileName, "%s/%d.txt", DATA_DIR, wordListSize);
    printf(fileName);
    
    FILE* file = fopen(fileName, "r");
    
    if (!file) {
        fprintf(stderr, "Could not read file");
        exit(EXIT_FAILURE);
    }

    return file;
}

void populateWordList(FILE* file, WordList* wordList, int wordListSize)
{    
    char wordBuffer[CHARS_PER_WORD];
    int wordPos = 0;
    int len = CHARS_PER_WORD;
    
    while (fgets(wordBuffer, sizeof(wordBuffer), file))
    {
        int wordLen = 0;
        // Finds the end of line
        for (int i = 0; i < len; ++i)
        {
            if (wordBuffer[i] == '\n')
            {
                wordBuffer[i] = '\0';
                wordLen = i;
                break;
            }
        }
        strncpy(wordList->words[wordPos], wordBuffer, wordLen);
        
        ++wordPos;
            
        if (wordPos >= wordListSize)
            break;
    }
}