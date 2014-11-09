/*
 * testDriver.c
 *
 *  Created on: Nov 6, 2014
 *      Author: rutger
 */

#include <stdio.h>
#include "Alphabet.h"
#include "uthash.h"

int main()
{
	int tLen = 12;
	char t[] = "acgtacgtacgt";
	char *text = malloc(tLen * sizeof(char));
	text = strcpy(text, t);

	int mLen = 3;
	char mask[] = "101";

	struct rankedAlphabet *alphabet = NULL; /*initialize hash to NULL*/

	fromString(text, tLen, mask, mLen, alphabet);


	return 0;
}
