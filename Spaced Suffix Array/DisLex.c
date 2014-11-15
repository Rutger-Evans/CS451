/*
 * DisLex.c
 *
 *  Created on: Nov 9, 2014
 *      Author: rutger
 */
#include "Alphabet.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int *disLex;
int *dLength;

void createDisLex(char * text, int tLength, char mask[], int mLength){
	extern struct rankedAlphabet *alphabet;
	int *tempdis;
	int runTotal = 0;
	int tempRun = 0;
	int count = 0;
	int index;
	int maskCount = 0;

	int i;
	for (i = 0; i < mLength; i++){
		if(mask[i] == '1'){
			maskCount++;
		}
	}

	for (i = 0; i < mLength; i++){
		int tempTotal = (tLength - i) / mLength;
		tempRun = tempRun + tempTotal;
		int j;
		for(j = 0; j < tempTotal; j++){
			char letter[15];

			int empty = 0;
			int m;
			for(m = 0; m < mLength; m++){
				if (mask[m] != '0'){
					index = i + (j * mLength) + m;
					letter[empty] = text[index];
					empty ++;
				}
			}

			letter[maskCount] = '\0';

			struct rankedAlphabet *alph;
			alph = malloc(sizeof(struct rankedAlphabet));

			HASH_FIND_STR(alphabet, letter, alph);

			if(i == 0 && j == 0){
				tempdis = malloc(tempRun * sizeof(int));
			}
			else if(i != 0 && j == 0){
				tempdis = realloc(tempdis, tempRun * sizeof(int));
			}


			index = runTotal + j;
			tempdis[index] = alph->rank;
			count++;
		}

		runTotal = runTotal + tempTotal;
	}
	dLength = malloc(sizeof(int));
	*dLength = count;
	disLex = malloc(count * sizeof(int));
	for (i = 0; i < count; i++){
		disLex[i] = tempdis[i];
	}
}
