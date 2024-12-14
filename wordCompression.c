#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CHARS_PER_WORD 20

// Modify this value
const int wordListSize = 10000;
const char vowels[5] = {'e', 'a', 'o', 'i', 'u'};

typedef struct
{
    int wordChars;
    int wordAmount;
    char words[1][CHARS_PER_WORD];
} WordList;
/*
WordList *allocateWordList(int wordListSize)
{
    WordList *words = malloc(sizeof(WordList) + (sizeof(char[CHARS_PER_WORD]))*(wordListSize-1));
    
    words->wordChars = CHARS_PER_WORD;
    words->wordAmount = wordListSize;
    
    for (int i = 0; i < wordListSize; ++i)
    {
        for (int j = 0; j < CHARS_PER_WORD; ++j)
        {
            words->words[i][j] = '\0';
        }
    }
    return words;
}
*/

// New GPT Code
WordList* allocateWordList(int wordListSize)
{
    WordList* words = calloc(1, sizeof(WordList) + (sizeof(char[CHARS_PER_WORD])) * (wordListSize - 1));
    if (!words) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    words->wordChars = CHARS_PER_WORD;
    words->wordAmount = wordListSize;
    return words;
}

WordList* readFile(int wordListSize)
{
    FILE *file;
    char fileName[16]; 
    sprintf(fileName, "%d.txt", wordListSize);
    file = fopen(fileName, "r");

    WordList* wordList = allocateWordList(wordListSize);
    
    char buffer[CHARS_PER_WORD];
    int wordPos = 0;
    size_t len = CHARS_PER_WORD;
    
    while (fgets(buffer, sizeof(buffer), file))
    {
        int wordLen = 0;
        // Finds the end of line
        for (int i = 0; i < len; ++i)
        {
            if (buffer[i] == '\n')
            {
                buffer[i] = '\0';
                wordLen = i;
                break;
            }
        }
        strncpy(wordList->words[wordPos], buffer, wordLen);
        
        ++wordPos;
            
        if (wordPos >= wordListSize)
            break;
    }

    return wordList;
}

int getWordLen(char* word)
{
    int len = 0;
    for (int ch = 0; ch < sizeof(word); ch++)
    {
        if (word[ch] == '\0') break;
        len++;
    }
    return len;
}

WordList* compressWords(WordList* wordList)
{
    WordList* compressedList = allocateWordList(wordListSize);
    for (unsigned int wordIndex = 0; wordIndex < wordListSize; wordIndex++)
    {
        bool validCandidate = false;
        int ch = 1;
        char candidate[CHARS_PER_WORD] = {'\0'};
        int wordLen = getWordLen(wordList->words[wordIndex]);

        while (!validCandidate)
        {   
            strncpy(candidate, wordList->words[wordIndex], ch);
            candidate[ch] = '\0';
            
            // Checks if it already exists in a previous word
            validCandidate = true;
            for (unsigned int i = 0; i < wordIndex; i++)
            {
                if (strcmp(compressedList->words[i], candidate) == 0)
                {
                    ch++;
                    validCandidate = false;
                    // If new candidate is shorter than other candidates, extend the other conflicting compressedWord by 1 character
                    if (ch >= wordLen) {
                        // printf("Candidate longer than original\n");
                        compressedList->words[i][wordLen+1] = 'z';
                    }
                    break;
                }
            }
        }
        printf("%s\n", candidate);
        strncpy(compressedList->words[wordIndex], candidate, ch);
        compressedList->words[wordIndex][ch] = '\0';
    }
    return compressedList;
}


int main()
{
    WordList* wordList = readFile(wordListSize);
    // for (int i = 0; i < wordListSize; i++) printf(wordList->words[i]);
    WordList* compressedList = compressWords(wordList);
    return 0;
}