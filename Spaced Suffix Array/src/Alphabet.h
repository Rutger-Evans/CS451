/*
 * Alphabet.h
 *
 *  Created on: Nov 4, 2014
 *      Author: root
 */

#ifndef ALPHABET_H_
#define ALPHABET_H_

#include <string.h>
#include "uthash.h"
#include "utarray.h"

void fromString(char * text, char * mask);

void toUpperCase(char * text);

void toAscii(char * text, int * ascii);

void createArray(UT_array *array);

#endif /* ALPHABET_H_ */
