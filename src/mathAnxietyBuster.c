#include "../include/mathAnxietyBuster.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* fp = fopen("./build/problems", "w");
	if (fp == NULL) {
		printf("Cannot create/open text file 'problems'\n");
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
				if (j == 0) fprintf(fp, Spaces_2);

				fprintf(fp, "%d ", problems[i][j].num1);
			}
			fprintf(fp, Spaces_3);
		}
		fprintf(fp, New_Line_1);
		for (int i = start; i < end; i++) {
			for (int j = 0; j < numDigits; j++) {
				if (j == 0) fprintf(fp, Plus_Sign);

				fprintf(fp, "%d ", problems[i][j].num2);
			}
			fprintf(fp, Spaces_3);
		}
		fprintf(fp, New_Line_4);
	}
	fprintf(fp, New_Line_2);

	for (int i = 0; i < numProblems; i++) {
		free(problems[i]);
	}
	free(problems);
	fclose(fp);

	return 0;
}