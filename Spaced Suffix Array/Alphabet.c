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

void fromString(char * text, int tLength, char mask[], int mLength, int * ascii){
	struct rankedAlphabet *alphabet = NULL; /*initialize hash to NULL*/
	struct DNAValues *dna = NULL;
	
	extern int k;

	toUpperCase(text);
	toAscii(text, ascii);
	createDNAHash(dna);
	
	int *p;

	int padding = 2 * mLength - 1;
	
	k = 1 + ((tLength - 1) / mLength);
	
	if ((tLength + padding) % mLength != 0){
		padding = padding + ((tLength+padding) % mLength);
	}
	
	/* create the length m letter and initialize it with rank 0 */
	for(int i = 0; i < (tLength + padding); i = i + mLength){
		int newLetter[mLength];
		
		for(int j = 0; j < mLength; j++){
			if(mask[j] != 0){
				newLetter[j] = (int)text[i + j];
			}
		}

		addAlphabetLetter(alphabet, newLetter, mLength, 0);
	}

	/* rank the alphabet */
	rankAlphabet();
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
void createDNAHash(struct DNAValues *hash, int paddingLength){
	int A = 65;
	int C = 66;
	int G = 71;
	int T = 84;

	addDNALetter(A, A);
	addDNALetter(C, C);
	addDNALetter(G, G);
	addDNALetter(T, T);

	for(int i = 0; i < paddingLength; i++){
		int letter = -1 * (i + 1);
		int value = -1 * (i + 1);
		addDNALetter(hash, letter, value);
	}
}

void rankAlphabet(){

}

void addDNALetter(struct DNAValues *dna, int letter, int value){
	struct DNAValues *alph;
	alph = malloc(sizeof(struct DNAValues));
	alph->letter = letter;
	alph->value = value;

	Hash_ADD_INT(dna, letter, alph);
}

void addAlphabetLetter(struct rankedAlphabet *alphabet, int newLetter[], int mLength, int rank){
	struct rankedAlphabet *alph;
	alph = malloc(sizeof(struct rankedAlphabet));
	alph->letter = malloc(mLength * sizeof(int));

	for(int i = 0; i < mLength; i++){
		alph->letter[i] = newLetter[i];
	}

	alph->rank = 0;
	
	HASH_ADD_PTR(alphabet, letter, alph);
}
/*
int main(){

}
*/
