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
    
    FILE* file = fopen(fileName, "r");
    
    if (!file)
    {
        fprintf(stderr, "Could not read file");
        exit(EXIT_FAILURE);
    }

    return file;
}

void writeOutputFile(WordList* finalWordList)
{
    char outputFileName[FILE_NAME_MAX_LEN];
    sprintf(outputFileName, "%s/output.txt", OUTPUT_DIR);

    FILE* outputFile = fopen(outputFileName, "w");
    if (!outputFile)
    {
        fprintf(stderr, "Could not create outputfile");
        exit(EXIT_FAILURE);
    }

    for (int wordIndex = 0; wordIndex < TOTAL_WORDS; wordIndex++)
    {
        char line[CHARS_PER_WORD+1];
        sprintf(line, "%s\n", finalWordList->words[wordIndex]);
        fprintf(outputFile, line);
    }
}

void populateWordList(FILE* file, WordList* wordList, int wordListSize)
{    
    char wordBuffer[CHARS_PER_WORD];
    int wordPos = 0;
    int len = CHARS_PER_WORD;
    
    /*
    The wordlist file must have a the specific format of:
    word1
    word2
    word3
    ...
    And preferably be ordered by frequency
    */
    while ((fgets(wordBuffer, sizeof(wordBuffer), file)) && (wordPos < wordListSize))
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
    }
}

unsigned int countCharsInFile(char filePath[FILE_NAME_MAX_LEN])
{
    FILE* file = fopen(filePath, "r");
    if (!file)
    {
        fprintf(stderr, "Could not open file%s\n", filePath);
        exit(EXIT_FAILURE);
    }
    unsigned int characterCount = 0;
    char character;
    // Counts characters until it reaches the EndOfFile
    while ((character = fgetc(file)) != EOF)
    {
        // Ignore newlines for more accurate results
        if (character != '\n')
            characterCount++;
    }

    return characterCount;
}

double calculateCompressionRatio()
{
    char dataFilePath[FILE_NAME_MAX_LEN*3] = {0};
    sprintf(dataFilePath, "%s/%d.txt", DATA_DIR, TOTAL_WORDS);
    char outputFilePath[FILE_NAME_MAX_LEN*3] = {0};
    sprintf(outputFilePath, "%s/output.txt", OUTPUT_DIR);

    unsigned int originalCharAmount = countCharsInFile(dataFilePath);
    unsigned int compressedCharAmount = countCharsInFile(outputFilePath);
    double ratio = (double)compressedCharAmount / (double)originalCharAmount;
    
    return ratio;
}