#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define Problems_Per_Row 10

typedef struct intPair {
	int num1;
	int num2;
} IntPair;

const IntPair pairs[] = {
	{ 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 1, 6 }, { 1, 7 }, { 1, 8 }, { 1, 9 }, { 2, 1 }, { 2, 2 }, { 2, 3 },
	{ 2, 4 }, { 2, 5 }, { 2, 6 }, { 2, 7 }, { 2, 8 }, { 2, 9 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 }, { 3, 6 },
	{ 3, 7 }, { 3, 8 }, { 3, 9 }, { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 }, { 4, 6 }, { 4, 7 }, { 4, 8 }, { 4, 9 },
	{ 5, 1 }, { 5, 2 }, { 5, 3 }, { 5, 4 }, { 5, 5 }, { 5, 6 }, { 5, 7 }, { 5, 8 }, { 5, 9 }, { 6, 1 }, { 6, 2 }, { 6, 3 },
	{ 6, 4 }, { 6, 5 }, { 6, 6 }, { 6, 7 }, { 6, 8 }, { 6, 9 }, { 7, 1 }, { 7, 2 }, { 7, 3 }, { 7, 4 }, { 7, 5 }, { 7, 6 },
	{ 7, 7 }, { 7, 8 }, { 7, 9 }, { 8, 1 }, { 8, 2 }, { 8, 3 }, { 8, 4 }, { 8, 5 }, { 8, 6 }, { 8, 7 }, { 8, 8 }, { 8, 9 },
	{ 9, 1 }, { 9, 2 }, { 9, 3 }, { 9, 4 }, { 9, 5 }, { 9, 6 }, { 9, 7 }, { 9, 8 }, { 9, 9 }
};

int main()
{
	FILE* fp = fopen("problems", "w");
	if (fp == NULL) {
		printf("Cannot create/open file problems\n");
		return 1;
	}

	int	  numDigits   = 3;
	int	  numProblems = 140;
	IntPair** problems    = malloc(sizeof(IntPair*) * numProblems);
	srand(100);

	for (int i = 0; i < numProblems; i++) {
		problems[i] = malloc(sizeof(IntPair) * numDigits);
		for (int j = 0; j < numDigits; j++) {
			int pairIndex  = rand() % 81;
			problems[i][j] = pairs[pairIndex];
		}
	}

	int rows = numProblems / Problems_Per_Row;

	for (int row = 1; row <= rows; row++) {
		int end	  = row * Problems_Per_Row;
		int start = end - Problems_Per_Row;

		for (int i = start; i < end; i++) {
			for (int j = 0; j < numDigits; j++) {
				if (j == 0) fprintf(fp, "  ");
				fprintf(fp, "%d ", problems[i][j].num1);
			}
			fprintf(fp, "   ");
		}
		fprintf(fp, "\n");
		for (int i = start; i < end; i++) {
			for (int j = 0; j < numDigits; j++) {
				if (j == 0) fprintf(fp, "+ ");
				fprintf(fp, "%d ", problems[i][j].num2);
			}
			fprintf(fp, "   ");
		}
		fprintf(fp, "\n\n\n\n");
	}
	fprintf(fp, "\n\n");
	fclose(fp);

	return 0;
}