/*
 * Alphabet.h
 *
 *  Created on: Nov 4, 2014
 *      Author: root
 */

#ifndef SPACEDSUFFIXARRAY_ALPHABET_H_
#define SPACEDSUFFIXARRAY_ALPHABET_H_

#include <string.h>
#include "uthash.h"
#include "utarray.h"

UT_array *dna;
int k;

struct rankedAlphabet{
	int * letter;
	int rank;
	UT_hash_handle hh;
};

void fromString(char * text, char * mask, int * ascii);

void toUpperCase(char * text);

void toAscii(char * text, int * ascii);

void createArray(UT_array *array);

void rankAlphabet();

int main();

#endif /* SPACEDSUFFIXARRAY_ALPHABET_H_ */
