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

void fromString(char * text, int tLength, char mask[], int mLength){
	extern struct rankedAlphabet *alphabet;
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

	printf("%s\n",text);

	/* create the length m letter and initialize it with rank 0 */
	for(i = 0; i < (tLength + padding) - mLength; i++){
		char newLetter[15];
		int j;
		for(j = 0; j < mLength; j++){
			if(mask[j] != '0'){
				newLetter[j] = text[i + j];
			}
			else{
				newLetter[j] = '*';
			}
		}
		newLetter[mLength] = '\0';
		addAlphabetLetter(newLetter);
	}

	/* rank the alphabet */
	rankAlphabet(mLength);
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
	extern char sentinel[29];
	sentinel[28] = '!';
	sentinel[27] = '"';
	sentinel[26] = '#';
	sentinel[25] = '$';
	sentinel[24] = '%';
	sentinel[23] = '&';
	sentinel[22] = '\'';
	sentinel[21] = '(';
	sentinel[20] = ')';
	sentinel[19] = '*';
	sentinel[18] = '+';
	sentinel[17] = ',';
	sentinel[16] = '-';
	sentinel[15] = '.';
	sentinel[14] = '/';
	sentinel[13] = '0';
	sentinel[12] = '1';
	sentinel[11] = '2';
	sentinel[10] = '3';
	sentinel[9] = '4';
	sentinel[8] = '5';
	sentinel[7] = '6';
	sentinel[6] = '7';
	sentinel[5] = '8';
	sentinel[4] = '9';
	sentinel[3] = ':';
	sentinel[2] = ';';
	sentinel[1] = '<';
	sentinel[0] = '=';
}
