#include "../include/mathAnxietyBuster.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	FILE*	  file	      = NULL;
	IntPair** problems    = NULL;
	int	  numDigits   = 0;
	int	  numProblems = 0;
	bool	  success     = false;

	success = ExtractArguments(argc, argv, &numDigits, &numProblems);
	if (!success) {
		printf("Invalid arguments, should be in format <program> 3d 100p\n");
		return 1;
	}

	success = CreateTextFile(&file);
	if (!success) {
		printf("Cannot create/open text file '%s'\n", Problems_File_Path);
		return 2;
	}

	success = InitializeMemoryForProblems(&problems, numDigits, numProblems);
	if (!success) {
		printf("Cannot Initialize memory for problems\n");
		return 3;
	}

	int rows = numProblems / Problems_Per_Row;

	for (int row = 1; row <= rows; row++) {
		int end	  = row * Problems_Per_Row;
		int start = end - Problems_Per_Row;

		for (int i = start; i < end; i++) {
			for (int j = 0; j < numDigits; j++) {
				if (j == 0) fprintf(file, Spaces_2);

				fprintf(file, "%d ", problems[i][j].num1);
			}
			fprintf(file, Spaces_3);
		}
		fprintf(file, New_Line_1);
		for (int i = start; i < end; i++) {
			for (int j = 0; j < numDigits; j++) {
				if (j == 0) fprintf(file, Plus_Sign);

				fprintf(file, "%d ", problems[i][j].num2);
			}
			fprintf(file, Spaces_3);
		}
		fprintf(file, New_Line_4);
	}
	fprintf(file, New_Line_2);

	for (int i = 0; i < numProblems; i++) {
		free(problems[i]);
	}
	free(problems);
	fclose(file);

	return 0;
}
bool ExtractArguments(int argc, char** argv, int* numDigits, int* numProblems)
{
	if (argc != 3) return false;
	if (sscanf(argv[1], "%d", numDigits) == 0) return false;
	if (sscanf(argv[2], "%d", numProblems) == 0) return false;

	return true;
}
bool CreateTextFile(FILE** file)
{
	*file = fopen(Problems_File_Path, "w");
	return *file != NULL;
}
bool InitializeMemoryForProblems(IntPair*** problems, int numDigits, int numProblems)
{
	*problems = malloc(sizeof(IntPair*) * numProblems);
	if (*problems == NULL) return false;

	srand(100);

	for (int i = 0; i < numProblems; i++) {
		(*problems)[i] = malloc(sizeof(IntPair) * numDigits);

		if ((*problems)[i] == NULL) return false;

		for (int j = 0; j < numDigits; j++) {
			int pairIndex	  = rand() % 81;
			(*problems)[i][j] = pairs[pairIndex];
		}
	}

	return true;
}