/*
 * testDriver.c
 *
 *  Created on: Nov 6, 2014
 *      Author: rutger
 */

#include <stdio.h>
#include "Alphabet.h"
#include "uthash.h"


int main(int argc, char *argv[])
{
	extern struct rankedAlphabet *alphabet;

	int tLen = 12;
	char t[] = "acgtacgtacgt";
	char *text = malloc(tLen * strlen(t));
	text = strcpy(text, t);

	int mLen = 3;
	char mask[] = "101";


	fromString(text, tLen, mask, mLen);

	struct rankedAlphabet *a;

	unsigned int count;
	count = HASH_COUNT(alphabet);

	printf("%d", count);
	for (a=alphabet; a != NULL; a=a->hh.next){
		printf("%s\n",a->letter);
	}
	return 0;
}

