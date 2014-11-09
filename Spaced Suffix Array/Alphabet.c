/*
 * Alphabet.c
 *
 *  Created on: Nov 4, 2014
 *      Author: root
 */

#include "Alphabet.h"
#include "uthash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void fromString(char * text, int tLength, char mask[], int mLength, struct rankedAlphabet *alphabet){
	extern int k;
	extern char sentinel[29];
	setSentinels();

	toUpperCase(text, tLength);

	int padding = 2 * mLength - 1;
	
	k = 1 + ((tLength - 1) / mLength);

	if ((tLength + padding) % mLength != 0){
		padding = padding + ((tLength+padding) % mLength);
	}
	
	text = realloc(text, sizeof(char) * (tLength + padding));

	int i;
	for(i = 0; i < padding; i++){
		text[tLength + i] = sentinel[i];
	}

	printf("%s",text);

	/* create the length m letter and initialize it with rank 0 */
	for(i = 0; i < (tLength + padding); i = i + mLength){
		char newLetter[15];
		int j;
		for(j = 0; j < mLength; j++){
			newLetter[j] = text[i + j];
		}

		addAlphabetLetter(alphabet, newLetter, 0);
	}

	/* rank the alphabet */
	rankAlphabet(alphabet, mLength);
}

/* make the text all upper case */
void toUpperCase(char * text, int tLength){
	int i;
	for (i = 0; i < tLength; i++){
		if (islower(text[i])){
			text[i] = toupper(text[i]);
		}
	}
}

void rankAlphabet(struct rankedAlphabet *alphabet, int mLength){
	struct rankedAlphabet *a;

	HASH_SORT(alphabet, letter_sort);

	int i = 0;
	for (a=alphabet; a != NULL; a=a->hh.next){
		a->rank = i;
		i++;
	}
}

void addAlphabetLetter(struct rankedAlphabet *alphabet, char newLetter[], int rank){
	struct rankedAlphabet *alph;
	alph = malloc(sizeof(struct rankedAlphabet));

	HASH_FIND_STR(alphabet, newLetter, alph);
	if(alph != NULL){
		strncpy(alph->letter, newLetter, 15);
		alph->rank = 0;

		HASH_ADD_STR(alphabet, letter, alph);
	}
}

int letter_sort(struct rankedAlphabet *a, struct rankedAlphabet *b) {
    return strcmp(a->letter,b->letter);
}

void setSentinels(){
	extern char sentinel[29];
	sentinel[0] = '!';
	sentinel[1] = '"';
	sentinel[2] = '#';
	sentinel[3] = '$';
	sentinel[4] = '%';
	sentinel[5] = '&';
	sentinel[6] = '\'';
	sentinel[7] = '(';
	sentinel[8] = ')';
	sentinel[9] = '*';
	sentinel[10] = '+';
	sentinel[11] = ',';
	sentinel[12] = '-';
	sentinel[13] = '.';
	sentinel[14] = '/';
	sentinel[15] = '0';
	sentinel[16] = '1';
	sentinel[17] = '2';
	sentinel[18] = '3';
	sentinel[19] = '4';
	sentinel[20] = '5';
	sentinel[21] = '6';
	sentinel[22] = '7';
	sentinel[23] = '8';
	sentinel[24] = '9';
	sentinel[25] = ':';
	sentinel[26] = ';';
	sentinel[27] = '<';
	sentinel[28] = '=';
}
