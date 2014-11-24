/*
 * MaskedSuffixArray.c
 *
 *  Created on: Nov 10, 2014
 *      Author: rutger
 */

#include "MaskedSuffixArray.h"
#include <stdlib.h>
#include <stdio.h>
#include "sais.h"
#include <time.h>


int * msaLength;
int * suffixArray;
int *maskedSuffixArray;
void createMaskedSuffixArray(char *text, int tLength, char mask[], int mLength){
	extern int *dLength;
	extern int *msaLength;
	extern int *suffixArray;
	extern int k;
	int maskCount = 0;
	createSuffixArray(*dLength);

	msaLength = malloc(*dLength * sizeof(int));

	maskedSuffixArray = malloc(*dLength * (sizeof(int)));

	int i;
	for(i = 0; i < mLength; i++){
		if (mask[i] == '1'){
			maskCount++;
		}
	}

	//printf("length of suffix array: %d\n", *dLength);

	time_t start, end;
	start = clock();
	for(i = 0; i < *dLength; i++){
		int x = suffixArray[i]/(k+1);
		int y = suffixArray[i]%(k+1);
		int index = y * mLength + x;

		msaLength[i] = tLength - index;
		maskedSuffixArray[i] = index;
	}
	end = clock();
	int msec = (end - start) * 1000 / CLOCKS_PER_SEC;
	printf("Time taken to create masked suffix array of T %d seconds, %d milliseconds\n", msec/1000, msec%1000);
}

void createSuffixArray(int dLength){
	extern int * disLex;
	extern int * suffixArray;


	suffixArray = malloc(dLength * sizeof(int));
	time_t start, end;
	start = clock();
	sais_int(disLex, suffixArray, dLength, 25500000);
	end = clock();
	int msec = (end - start) * 1000 / CLOCKS_PER_SEC;
	printf("Time taken to create suffix array of Tprime %d seconds, %d milliseconds\n", msec/1000, msec%1000);
}
