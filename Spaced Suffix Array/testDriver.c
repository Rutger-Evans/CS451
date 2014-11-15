/*
 * testDriver.c
 *
 *  Created on: Nov 6, 2014
 *      Author: rutger
 */

#include <stdio.h>
#include "Alphabet.h"
#include "DisLex.h"
#include "uthash.h"
#include "MaskedSuffixArray.h"
//#include <sary.h>;

int main(int argc, char *argv[])
{
	extern int *dLength;
	extern char **maskedSuffixArray;
	extern int *msaLength;
	int tLen = 12;
	int *tLength = (int*)malloc(sizeof(int));
	tLength = &tLen;
	char t[] = "acaaagtacttagcat";
	char *text = malloc(tLen * strlen(t));
	text = strcpy(text, t);

	int mLen = 3;
	char mask[] = "101";


	fromString(text, tLength, mask, mLen);
	createDisLex(text,*tLength, mask, mLen);
	createMaskedSuffixArray(text, *tLength, mask, mLen);

	int i;
	for (i = 0; i < *dLength;i++){
		printf("%s\n",maskedSuffixArray[i]);
	}
	return 0;
}
