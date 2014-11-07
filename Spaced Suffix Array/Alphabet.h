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

UT_array *dna;
int k;

struct rankedAlphabet{
	int *letter;
	int rank;
	UT_hash_handle hh;
};

struct DNAValues{
	int letter;
	int value;
	UT_hash_handle hh;
};

void fromString(char * text, int tLength, char mask[], int mLength, int * ascii);

void toUpperCase(char * text);

void toAscii(char * text, int * ascii);

void createDNAHash(struct DNAValues *hash);

void rankAlphabet(struct rankedAlphabet *alphabet);

void addDNALetter(struct DNAValues *dna, int letter, int value);

void addAlphabetLetter(struct rankedAlphabet *alphabet, int newLetter[], int rank);

#endif /* SPACEDSUFFIXARRAY_ALPHABET_H_ */
