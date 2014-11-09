/*
 * Alphabet.h
 *
 *  Created on: Nov 4, 2014
 *      Author: root
 */

#ifndef SPACEDSUFFIXARRAY_ALPHABET_H_
#define SPACEDSUFFIXARRAY_ALPHABET_H_

#include "uthash.h"

int k;

char sentinel[29];

struct rankedAlphabet{
	char letter[15];
	int rank;
	UT_hash_handle hh;
};

void fromString(char * text, int tLength, char mask[], int mLength, struct rankedAlphabet *alphabet);

void toUpperCase(char * text, int tLength);

void rankAlphabet(struct rankedAlphabet *alphabet, int mLength);

void addAlphabetLetter(struct rankedAlphabet *alphabet, char newLetter[], int rank);

int letter_sort(struct rankedAlphabet *a, struct rankedAlphabet *b);

void setSentinels();

#endif /* SPACEDSUFFIXARRAY_ALPHABET_H_ */
