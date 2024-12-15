// word_compression.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "word_utils.h"


// Modify this value
const int totalWords = 10000;


// Ordering the words by length
void orderList(WordList* wordList, WordList* orderedList)
{
    int currentIndex = 0;
    
    for (int charLen = 1; charLen < CHARS_PER_WORD; charLen++)
    {
        for (unsigned int wordIndex = 0; wordIndex < totalWords; wordIndex++)
        {
            if (strlen(wordList->words[wordIndex]) == charLen)
            {
                strncpy(orderedList->words[currentIndex], wordList->words[wordIndex], CHARS_PER_WORD);
                currentIndex++;
            }
        }
    }
}

void compressWords(WordList* wordList)
{
    for (unsigned int wordIndex = 0; wordIndex < totalWords; wordIndex++)
    {
        bool validCandidate = false;
        int charIndex = 1;
        char candidate[CHARS_PER_WORD] = {'\0'};
        int wordLen = strlen(wordList->words[wordIndex]);

        while (!validCandidate)
        {   
            strncpy(candidate, wordList->words[wordIndex], charIndex);
            candidate[charIndex] = '\0';
            validCandidate = true;
            
            // Checks if it already exists in a previous word
            for (unsigned int i = 0; i < wordIndex; i++)
            {
                if (strcmp(wordList->words[i], candidate) == 0)
                {
                    charIndex++;
                    validCandidate = false;
                    // If new candidate is shorter than other candidates, extend the other conflicting compressedWord by 1 character
                    if (charIndex >= wordLen) {
                        // printf("Candidate longer than original\n");
                        // compressedList->words[i][wordLen+1] = 'z';
                    }
                    break;
                }
            }
        }
        // printf("%s\n", candidate);
        strncpy(wordList->words[wordIndex], candidate, charIndex);
        wordList->words[wordIndex][charIndex] = '\0';
    }
}


int main()
{
    clock_t startTime = clock();
    
    FILE* wordListFile = readFile(totalWords);
    WordList* wordList = allocateWordList(totalWords);
    populateWordList(wordListFile, wordList, totalWords);
    
    WordList* orderedList = allocateWordList(totalWords);
    orderList(wordList, orderedList);
    compressWords(orderedList);

    clock_t endTime = clock();
    double elapsed_seconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.6f seconds\n", elapsed_seconds);
    
    // for (int i = 0; i < totalWords; i++) printf("%s\n", orderedList->words[i]);

    // Free the dynamically allocated WordLists
    free(wordList);
    free(orderedList);
    
    return 0;
}