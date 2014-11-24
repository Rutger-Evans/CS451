#include <stdio.h>
#include <stdlib.h>

/*----------------------------------------------------------------------------------------
 *
 * FILE READER FROM WIKIPEDIA
 *
 *----------------------------------------------------------------------------------------*/
#define BUF_SIZE ( 256 )

char *readLine(FILE *f, uint line_no) {
	char buf[BUF_SIZE];
	size_t curr_alloc = BUF_SIZE, curr_ofs = 0;
	char *line = malloc( BUF_SIZE);
	uint in_line = line_no == 1;
	size_t bytes_read;

	/* Illegal to ask for a line before the first one. */
	if (line_no < 1)
		return NULL;

	/* Handle out-of-memory by returning NULL */
	if (!line)
		return NULL;

	/* Scan the file looking for newlines */
	while (line_no && (bytes_read = fread(buf, 1, BUF_SIZE, f)) > 0) {
		uint i;

		for (i = 0; i < bytes_read; i++) {
			if (in_line) {
				if (curr_ofs >= curr_alloc) {
					curr_alloc <<= 1;
					line = realloc(line, curr_alloc);

					if (!line) /* out of memory? */
						return NULL;
				}
				line[curr_ofs++] = buf[i];
			}

			if (buf[i] == '\n') {
				line_no--;

				if (line_no == 1)
					in_line = 1;

				if (line_no == 0)
					break;
			}
		}
	}

	/* Didn't find the line? */
	if (line_no != 0) {
		free(line);
		return NULL;
	}

	/* Resize allocated buffer to what's exactly needed by the string
	 and the terminating NUL character.  Note that this code *keeps*
	 the terminating newline as part of the string.
	 */
	line = realloc(line, curr_ofs + 1);

	if (!line) /* out of memory? */
		return NULL;

	/* Add the terminating NUL. */
	line[curr_ofs] = '\0';

	/* Return the line.  Caller is responsible for freeing it. */
	return line;
}

// START SSA Searcher and related functions

char *readAt(char* file, uint line) {
	FILE *fl = fopen(file, "r");
	return readLine(fl, line);
}

uint size(char *ptr) {
	uint offset = 0;
	uint count = 0;

	//While loop that tests whether the end of the array has been reached
	while (*(ptr + offset) != '\0') {
		//increment the count variable
		++count;
		//advance to the next element of the array
		++offset;
	}
	return count - 1;
}

uint lnToUint(char a[]) {
	uint c, n;

	n = 0;

	for (c = 0; a[c] != '\n'; c++) {
		n = n * 10 + a[c] - '0';
	}

	return n;
}

int main(int argc, char *argv[]) {
	if (argc != 3) /* 	argc should be 3 for correct execution, including a mask
	 but I haven't figured out how to hand this argument without crashing code */
	{
		/* We print argv[0] assuming it is the program name */
		printf("usage: %s filename query\n", argv[0]);
	} else {
		// argv[1] is a filename to open

		char *file = argv[1];
		char *query = argv[2];

		char *t = readAt(file, 1);
		uint tLen = size(t);
		char *mask = readAt(file, 2);
//		uint mLen = size(mask);
		uint mLen = 5;
		uint len = (uint) lnToUint(readAt(file, 3));
		const uint offset = 4;

		char *line = readAt(file, 1);
		//printf(line);
		free(line);

		//Stats
		printf("Mask applied: %s", mask);
		printf("Length of array: %d\n", len);
		printf("Length of T': %d\n", tLen);
		printf("Length of mask: %d\n", mLen);

		//create masked query and calc unmasked items
		uint umLen = 0;
		uint x = 0;
		for (x = 0; x < mLen; x++) {
			if (mask[x] == '1')
				umLen++;
		}

		char mQ[umLen];
		uint y = 0;

		for (x = 0; x < mLen; x++) {
			if (mask[x] == '1') {
				mQ[y] = query[x];
				y++;
			}
		}

		printf("Unmasked items: %d\n", umLen);

		printf("Masked query: %s\n", mQ);

		y = 0; //size of results array
		uint *z = malloc(0 * sizeof(uint)); //results array

		x = len - 1; //current line to read
		uint mult = 0; //var to sense whether query is less than or greater than objective
		uint min, max;
		min = 0;
		max = x;
		int end = 0;

		uint i = 0; //for char loop on current suffix and masked query
		uint j = 0; //for char loop in T'

		//recursion to seek matches
		while (end == 0) {
			mult = 0;
			x = ((max - min) / 2) + min;

			printf("%d - %d  --> %d\n", max, min, x);
			line = readAt(file, (x + offset));

			i = 0;

			//loop through mask and first chars of line, move max and min as needed

			for (i = 0; i < umLen; i++) {
				if (mult == 0) {
					if (line[i] > mQ[i]) {
						mult = 1;
						max = x;
					} else if (line[i] < mQ[i]) {
						min = x;
						mult = 3;
					}
				}
			}

			//if match, print
			if (mult == 0) {
				free(line);

				//min towards middle
				while (min < x) {
					min++;
					int match = 1;
					line = readAt(file, (min + offset));

					//look for mismatch, if found, move to the next item
					for (i = 0; i < umLen; i++) {
						if (line[i] != mQ[i]) {
							match = 0;
						}
					}
					if (match == 1) {
						x = min;
						printf("Min line %d: %s \n", x, line);
					}
				}
				//max towards middle
				while (max > x) {
					max--;
					int match = 1;
					line = readAt(file, (max + offset));

					//look for mismatch, if found, move to the next item
					for (i = 0; i < umLen; i++) {
						if (line[i] != mQ[i]) {
							match = 0;
						}
					}
					if (match == 1) {
						x = max;
						printf("Max line %d: %s \n", x, line);

					}
				}

				printf("Iterations: %d\n", j);
				end = 1;
			}

			if (max == min) {
				printf("Not found!");
				end = 1;
			}
			free(line);
			j++;

		}
	}
	return 0;
}
