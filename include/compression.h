// compression.h
#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "hash_utils.h"

void groupByLen(WordHashTable* table, WordList* wordList);
void compressWords(WordHashTable* table, WordList* outputList);

#endif // COMPRESSION_H