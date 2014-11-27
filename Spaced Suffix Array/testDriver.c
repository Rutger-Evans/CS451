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
#include <time.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

	if (argc != 3) /* argc should be 2 for correct execution */
	{
		/* We print argv[0] assuming it is the program name */
		printf("usage: %s filename mask", argv[0]);
	} else {
		// argv[1] is a filename to open
		FILE *file = fopen(argv[1], "r");

		// fopen returns 0 on failure
		if (file == 0) {
			printf("Could not open file\n");

		} else {
			int x;
			int tLen = -1;
			int w = 0;
			char * text;

			char * mask = argv[2];
			int mLen = strlen(mask);

			bool isValidMask = true;

			int i;
			for(i = 0; i < mLen; i++){
				if(mask[i] != '0' && mask[i] != '1'){
					isValidMask = false;
				}
			}

			if(!isValidMask){
				printf("Invalid mask. The mask must only contain 1 and 0.\n");
				return 0;
			}

			if(mLen > 18){
				printf("Invalid mask. The mask must be less than 18 characters long.\n");
				return 0;
			}
			//initial allocation, 0 bytes
			text = (char*) malloc(0 *sizeof(char*));

			while ((x = fgetc(file)) != EOF) {
				if (x == '>') {

					//on first run, z is empty and y = -1
					if (tLen != -1) {
						//printf("%s\n",text);
					}

					//printf to output to screen, for debugging purposes
					//printf("Sequence Name -- ");

					//w is the marker for sequence names, starts at '>'
					w = 1;

					//set y > -1, meaning that from here on out, z will be at new seq
					tLen = 0;
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

					tLen++; //current position
					text = (char*) realloc(text, tLen * sizeof(char*)); //resize to add new char
					text[tLen-1]=x; //add new char at the end
				}
			}


			//sample function call
			//fromString(z, y, ('1','0','1'), 3, int * ascii);

			extern int *dLength;
			//extern char **maskedSuffixArray;
			extern int *maskedSuffixArray;
			//extern int *msaLength;
			//printf("%s\n",text);
			int *tLength = (int*)malloc(sizeof(int));
			tLength = &tLen;
			//int mLen = 3;
			//char mask[] = "101";

			//printf("length of text: %d\n", tLen);

			//time_t start, end;
			//start = clock();
			fromString(text, tLength, mask, mLen);
			//end = clock();
			//int msec = (end - start) * 1000 / CLOCKS_PER_SEC;
			//printf("Time taken to create alphabet %d seconds, %d milliseconds\n", msec/1000, msec%1000);
			//printf("%s\n",text); //print out last one

			//start = clock();
			createDisLex(text,*tLength, mask, mLen);
			//end = clock();
			//msec = (end - start) * 1000 / CLOCKS_PER_SEC;
			//printf("Time taken to create Tprime %d seconds, %d milliseconds\n", msec/1000, msec%1000);

			createMaskedSuffixArray(text, *tLength, mask, mLen);



			free(dLength);
			free(maskedSuffixArray);
		}
		fclose(file);
	}
	return 0;
}
