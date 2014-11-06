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
#include <ctype.h>

void fromString(char * text, char * mask, int * ascii){
	struct rankedAlphabet *alphabet = NULL; /*initialize hash to NULL*/
	
	extern UT_array *dna;
	extern int k;

	toUpperCase(text);
	toAscii(text, ascii);
	createArray(dna);
	
	int tLength = strlen(text);
	int mLength = strlen(mask);
	int *p;

	int padding = 2 * mLength - 1;
	
	k = 1 + ((tLength - 1) / mLength);
	
	if ((tLength + padding) % mLength != 0){
		padding = padding + ((tLength+padding) % mLength);
	}
	
	for(int i = 0; i < padding; i++){
		int temp = -1 * (i + 1);
		utarray_push_back(dna, &temp);
	}
	
	for(int i = 0; i < (tLength + padding); i = i + mLength){
		struct rankedAlphabet *alph;
		alph = malloc(sizeof(struct rankedAlphabet));
		alph->letter = malloc(mLength * sizeof(int));
		
		for(int j = 0; j < mLength; j++){
			if(mask[j] != 0){
				alph->letter[j] = text[i + j];
			}
		}

		alph->rank = 0;
		
		HASH_ADD_PTR(alphabet, letter, alph);
		
		rankAlphabet();
	}
}

/* make the text all upper case */
void toUpperCase(char * text){
	while (*text != '\0'){
		if (islower(*text)){
			*text = toupper(*text);
		}
		text++;
	}
}

/* turn the text into an array of ints */
void toAscii(char * text, int * ascii){
	while (*text != '\0'){
		int c = (int) *text;
		*ascii = c;
		text++;
		ascii++;
	}
}

/* initialize the array of dna */
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

void rankAlphabet(){
	
}

int main(){

}
