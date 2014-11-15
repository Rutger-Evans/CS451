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

struct rankedAlphabet *alphabet = NULL; /*initialize hash to NULL*/


void fromString(char * text, int * tLength, char mask[], int mLength){
	extern struct rankedAlphabet *alphabet;
	extern int k;
	extern char sentinel[43];
	int maskCount = 0;
	setSentinels();

	//printf("%d\n", *tLength);

	toLowerCase(text, *tLength);

	int padding = 2 * mLength - 1;
	
	k = 1 + ((*tLength - 1) / mLength);

	if ((*tLength + padding - (mLength - 1)) % mLength != 0){
		padding = padding + ((*tLength + padding - (mLength - 1)) % mLength) - 1;
	}
	
	text = realloc(text, sizeof(char) * (*tLength + padding));

	int i;
	for(i = 0; i < padding; i++){
		text[*tLength + i] = sentinel[i];
	}
	for(i = 0; i < mLength; i++){
		if(mask[i] == '1'){
			maskCount++;
		}
	}
	/* create the length m letter and initialize it with rank 0 */
	for(i = 0; i < (*tLength + padding) - (mLength - 1); i++){
		char newLetter[15];
		int index = 0;
		int j;
		for(j = 0; j < mLength; j++){
			if(mask[j] != '0'){
				newLetter[index] = text[i + j];
				index++;
			}
		}
		newLetter[maskCount] = '\0';
		addAlphabetLetter(newLetter);
	}

	/* rank the alphabet */
	rankAlphabet(mLength);

	*tLength = *tLength + padding;
}

/* make the text all upper case */
void toLowerCase(char * text, int tLength){
	int i;
	for (i = 0; i < tLength; i++){
		if (!islower(text[i])){
			text[i] = tolower(text[i]);
		}
	}
}

void rankAlphabet( int mLength){
	extern struct rankedAlphabet *alphabet;
	struct rankedAlphabet *a;

	HASH_SORT(alphabet, letter_sort);

	int i = 0;
	for (a=alphabet; a != NULL; a=a->hh.next){
		a->rank = i;
		i++;
	}
}

void addAlphabetLetter(char newLetter[]){
	extern struct rankedAlphabet *alphabet;
	struct rankedAlphabet *alph;
	alph = malloc(sizeof(struct rankedAlphabet));

	HASH_FIND_STR(alphabet, newLetter, alph);
	if(alph == NULL){
		alph = (struct rankedAlphabet *)malloc(sizeof(struct rankedAlphabet));
		strncpy(alph->letter, newLetter,15);
		alph->rank = 0;

		HASH_ADD_STR(alphabet, letter, alph);
	}
}

int letter_sort(struct rankedAlphabet *a, struct rankedAlphabet *b) {
    return strcmp(a->letter,b->letter);
}

void setSentinels(){
	extern char sentinel[43];
	sentinel[42] = (char)54;
	sentinel[41] = (char)55;
	sentinel[40] = (char)56;
	sentinel[39] = (char)57;
	sentinel[38] = (char)58;
	sentinel[37] = (char)59;
	sentinel[36] = (char)60;
	sentinel[35] = (char)61;
	sentinel[34] = (char)62;
	sentinel[33] = (char)63;
	sentinel[32] = (char)64;
	sentinel[31] = (char)65;
	sentinel[30] = (char)66;
	sentinel[29] = (char)67;
	sentinel[28] = (char)68;
	sentinel[27] = (char)69;
	sentinel[26] = (char)70;
	sentinel[25] = (char)71;
	sentinel[24] = (char)72;
	sentinel[23] = (char)73;
	sentinel[22] = (char)74;
	sentinel[21] = (char)75;
	sentinel[20] = (char)76;
	sentinel[19] = (char)77;
	sentinel[18] = (char)78;
	sentinel[17] = (char)79;
	sentinel[16] = (char)80;
	sentinel[15] = (char)81;
	sentinel[14] = (char)82;
	sentinel[13] = (char)83;
	sentinel[12] = (char)84;
	sentinel[11] = (char)85;
	sentinel[10] = (char)86;
	sentinel[9] = (char)87;
	sentinel[8] = (char)88;
	sentinel[7] = (char)89;
	sentinel[6] = (char)90;
	sentinel[5] = (char)91;
	sentinel[4] = (char)92;
	sentinel[3] = (char)93;
	sentinel[2] = (char)94;
	sentinel[1] = (char)95;
	sentinel[0] = (char)96;
}
