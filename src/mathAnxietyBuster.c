#include "../include/mathAnxietyBuster.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	FILE*	 file	     = NULL;
	Problem* problems    = NULL;
	int	 numDigits   = 0;
	int	 numProblems = 0;
	bool	 success     = false;

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

	success = InitializeProblems(&problems, numDigits, numProblems);
	if (!success) {
		printf("Cannot Initialize problems\n");
		return 3;
	}

	PrintProblems(problems, numDigits, numProblems, file);

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
bool InitializeProblems(Problem** problems, int numDigits, int numProblems)
{
	*problems = malloc(sizeof(Problem) * numProblems);
	if (*problems == NULL) return false;

	srand(100);
	for (int i = 0; i < numProblems; i++) {
		Problem problem	 = { 0 };
		problem.question = malloc(sizeof(IntPair) * numDigits);

		if (problem.question == NULL) return false;

		problem.position = i + 1;
		for (int j = 0; j < numDigits; j++) {
			int pIndex	    = rand() % 81;
			problem.question[j] = pairs[pIndex];
		}

		// Todo: Fix below loop to correctly calculate answer.
		for (int j = 0; j < numDigits; j++) {
			problem.answer += problem.question[j].num1 + problem.question[j].num2;
		}

		(*problems)[i] = problem;
	}
	return true;
}
void PrintProblems(Problem* problems, int numDigits, int numProblems, FILE* file)
{
	int rows = numProblems / Problems_Per_Row;
	for (int row = 1; row <= rows; row++) {
		int end	  = row * Problems_Per_Row;
		int start = end - Problems_Per_Row;
		for (int i = start; i < end; i++) {
			fprintf(file, "%3d.   ", problems[i].position);
			for (int j = 0; j < numDigits; j++) {
				fprintf(file, "%d ", problems[i].question[j].num1);
			}
			fprintf(file, Spaces_1);
		}
		fprintf(file, New_Line_1);
		for (int i = start; i < end; i++) {
			fprintf(file, "%5c", Space_Bar);
			for (int j = 0; j < numDigits; j++) {
				if (j == 0) fprintf(file, Plus_Sign);
				fprintf(file, "%d ", problems[i].question[j].num2);
			}
			fprintf(file, Spaces_1);
		}
		fprintf(file, New_Line_4);
	}

	// Todo: printing the answers neatly
	for (int i = 0; i < numProblems; i++) {
		fprintf(file, "%d. %d| ", problems[i].position, problems[i].answer);
		free(problems[i].question);
	}
}