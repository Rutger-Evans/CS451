/*
 * Alphabet.c
 *
 *  Created on: Nov 4, 2014
 *      Author: root
 */

#include "Alphabet.h"
#include "uthash.h"
#include "utarray.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern UT_array *dna;

struct rankedAlphabet{
	int * letter;
	int rank;
	UT_hash_handle hh;
};

void fromString(char * text, char * mask, int * ascii){
	toUpperCase(text);
	toAscii(text, ascii);
	createArray(dna);

	int tLength = strlen(text);
	int mLength = strlen(mask);
	int *p;

	int padding = 2 * mLength - 1;

	if (tLength % mLength != 0){

	}

	for(int i = 0; i < sizeof(text); i = i + sizeof(mask)){
		struct rankedAlphabet *alph = NULL; /*initialize hash to NULL*/

		alph = malloc(sizeof(struct rankedAlphabet));
	}
}

/* make the text all upper case */
void toUpperCase(char * text){
	while (*text != '\0'){
		if (islower(*text)){
			*text = toupper(*text);
		}
	}
}

/* turn the text into an array of ints */
void toAscii(char * text, int * ascii){
	while (*text != '\0'){
		int c = (int) *text;
		*ascii = c;
	}
}

void createArray(UT_array *array){
	int A = 65;
	int C = 66;
	int G = 71;
	int T = 84;

	utarray_new(array, &ut_int_icd);

	utarray_push_back(array, &A);
	utarray_push_back(array, &C);
	utarray_push_back(array, &G);
	utarray_push_back(array, &T);
}
