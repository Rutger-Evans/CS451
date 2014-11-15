/*
 * MaskedSuffixArray.c
 *
 *  Created on: Nov 10, 2014
 *      Author: rutger
 */

#include "MaskedSuffixArray.h"
#include <stdlib.h>
#include <stdio.h>

int * msaLength;
int * suffixArray;
char **maskedSuffixArray;
void createMaskedSuffixArray(char *text, int tLength, char mask[], int mLength){
	extern int *dLength;
	extern int *msaLength;
	extern int *suffixArray;
	extern char **maskedSuffixArray;
	extern int k;
	int maskCount = 0;
	createSuffixArray(*dLength);

	msaLength = malloc(*dLength * sizeof(int));

	maskedSuffixArray = malloc(*dLength * (sizeof(char*)));

	int i;
	for(i = 0; i < mLength; i++){
		if (mask[i] == '1'){
			maskCount++;
		}
	}
	for(i = 0; i < *dLength; i++){
		int x = suffixArray[i]/(k+1);
		int y = suffixArray[i]%(k+1);
		int index = y * mLength + x;

		msaLength[i] = tLength - index;
		maskedSuffixArray[i] = malloc((tLength - index) * sizeof(char));
		int empty = 0;
		int j;
		for(j = 0; j < tLength - index; j++){
			if(mask[j % mLength] == '1'){
				maskedSuffixArray[i][empty] = text[index + j];
				empty++;
			}
		}
	}
}

void createSuffixArray(int dLength){
	extern int * disLex;
	extern int * suffixArray;

	suffixArray = malloc(dLength * sizeof(int));
	int value = 0;
	int count = 0;
	int i;
	for(i = dLength - 1; value < dLength; i--){
		if(disLex[i] == value){
			suffixArray[count] = i;
			count++;
		}
		if(i == 0){
			value++;
			i = dLength - 1;
		}
	}
}
