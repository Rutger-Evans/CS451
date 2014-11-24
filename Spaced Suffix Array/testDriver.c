/*
 * testDriver.c
 *
 *  Created on: Nov 6, 2014
 *      Author: rutger
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Alphabet.h"
#include "DisLex.h"
#include "uthash.h"
#include "MaskedSuffixArray.h"
//#include <sary.h>;

/*
 * testDriver.c
 *
 *  Modified on: Nov 23, 2014
 *      Author: Manuel
 *
 *     	-- Write out to file using ">"
 */


int main(int argc, char *argv[]) {

	//File reader section

	int x;
	int y = -1;
	int w = 0;
	char * z;

	if (argc != 2) /* 	argc should be 3 for correct execution, including a mask
						but I haven't figured out how to hand this argument without crashing code */
	{
		/* We print argv[0] assuming it is the program name */
		printf("usage: %s filename mask\n", argv[0]);
	} else {
		// argv[1] is a filename to open
		FILE *file = fopen(argv[1], "r");

		// fopen returns 0 on failure
		if (file == 0) {
			printf("Could not open file\n");
		} else {
			y = -1;
			w = 0;

			//initial allocation, 0 bytes
			z = (char*) malloc(0 *sizeof(char*));

			while ((x = fgetc(file)) != EOF) {
				if (x == '>') {

					//on first run, z is empty and y = -1
					if (y != -1) {
						//printf("%s\n",z);
					}

					//printf to output to screen, for debugging purposes
					//printf("Sequence Name -- ");

					//w is the marker for sequence names, starts at '>'
					w = 1;

					//set y > -1, meaning that from here on out, z will be at new seq
					y = 0;
				}

				//if in a sequence name, print out. end at '\n'
				else if (w == 1){
					if (x == '\n') {
						w = 0;
					}
					//printf("%c", x);
				}

				//remove '\n' from sequences, and save into dynamic string z
				else if (x != '\n'){

					y++; //current position
					z = (char*) realloc(z, y * sizeof(char*)); //resize to add new char
					z[y-1]=x; //add new char at the end

				}

			}
//			printf("%s\n",z); //print out last one
//			printf("%d\n",y);

		}

		fclose(file);
	}


	//char* mask = argv[2];
	//int* mLen = (int) argv[3];


	extern int *dLength;
	extern char **maskedSuffixArray;
	extern int *msaLength;
	int tLen = y;
	//char* t[] = z;
	int mLen = 5;
	char mask[] = "10110";
	char *text = malloc(tLen * strlen(z));
	text = strcpy(text, z);
	int *tLength = (int*)malloc(sizeof(int));
	tLength = &tLen;

	fromString(text, tLength, mask, mLen);
	createDisLex(text,*tLength, mask, mLen);
	createMaskedSuffixArray(text, *tLength, mask, mLen);

	printf("%s\n", text);
	printf("%s\n", mask);
	printf("%d\n", *dLength);
	int i;
	for (i = 0; i < *dLength;i++){
		printf("%s\n",maskedSuffixArray[i]);
	}
	return 0;
}
