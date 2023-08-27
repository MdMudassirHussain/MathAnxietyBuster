#include "../include/mathAnxietyBuster.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	FILE*	 problemsFile  = NULL;
	FILE*	 solutionsFile = NULL;
	Problem* problems      = NULL;
	int	 numDigits     = 0;
	int	 numProblems   = 0;
	bool	 success       = false;

	srand(time(NULL));

	success = ExtractArguments(argc, argv, &numDigits, &numProblems);
	if (!success) {
		printf("Invalid arguments, should be in format <program> 3d 100p\n");
		return 1;
	}

	success = CreateTextFile(&problemsFile, Problems_File_Path);
	if (!success) {
		printf("Cannot create/open problems text file '%s'\n", Problems_File_Path);
		return 2;
	}

	success = CreateTextFile(&solutionsFile, Solutions_File_Path);
	if (!success) {
		printf("Cannot create/open soutions text file '%s'\n", Solutions_File_Path);
		return 3;
	}

	success = InitializeProblems(&problems, numDigits, numProblems);
	if (!success) {
		printf("Cannot Initialize problems\n");
		return 4;
	}

	PrintHeader(problemsFile);
	PrintProblems(problems, numDigits, numProblems, problemsFile);
	PrintAnswers(numProblems, problems, solutionsFile);

	free(problems);
	fclose(problemsFile);
	fclose(solutionsFile);

	return 0;
}
bool ExtractArguments(int argc, char** argv, int* numDigits, int* numProblems)
{
	if (argc != 3) return false;
	if (sscanf(argv[1], "%d", numDigits) == 0) return false;
	if (sscanf(argv[2], "%d", numProblems) == 0) return false;

	return true;
}
bool CreateTextFile(FILE** file, char* filePath)
{
	*file = fopen(filePath, "w");
	return *file != NULL;
}
bool InitializeProblems(Problem** problems, int numDigits, int numProblems)
{
	*problems = malloc(sizeof(Problem) * numProblems);
	if (*problems == NULL) return false;

	for (int i = 0; i < numProblems; i++) {
		Problem problem	 = { 0 };
		short	num1s	 = 0;
		short	num2s	 = 0;
		problem.question = malloc(sizeof(IntPair) * numDigits);

		if (problem.question == NULL) return false;

		problem.position = i + 1;
		for (int j = 0; j < numDigits; j++) {
			problem.question[j] = pairs[(rand() % 81)];

			num1s = (num1s + problem.question[j].num1) * 10;
			num2s = (num2s + problem.question[j].num2) * 10;
		}
		problem.answer = (num1s / 10 + num2s / 10);
		(*problems)[i] = problem;
	}
	return true;
}
void PrintHeader(FILE* problemsFile)
{
	struct tm* ptr;
	time_t	   t;
	t   = time(NULL);
	ptr = localtime(&t);
	fprintf(problemsFile, "  %s", asctime(ptr));
	fprintf(problemsFile, "  ------------------------\n");
}
void PrintProblems(Problem* problems, int numDigits, int numProblems, FILE* file)
{
	int rows = numProblems / Problems_Per_Row;
	for (int row = 1; row <= rows; row++) {
		int end	  = row * Problems_Per_Row;
		int start = end - Problems_Per_Row;
		PrintRow(start, end, numDigits, file, problems);
		if (row < rows) fprintf(file, New_Line_4);
	}
}
void PrintRow(int start, int end, int numDigits, FILE* file, Problem* problems)
{
	// print first line num1's
	for (int i = start; i < end; i++) {
		fprintf(file, "%3d)   ", problems[i].position);
		for (int j = 0; j < numDigits; j++) {
			fprintf(file, "%d ", problems[i].question[j].num1);
		}
		fprintf(file, Spaces_1);
	}
	fprintf(file, New_Line_1);

	// print second line num2's
	for (int i = start; i < end; i++) {
		fprintf(file, "%5c", Space_Bar);
		for (int j = 0; j < numDigits; j++) {
			if (j == 0) fprintf(file, Plus_Sign);
			fprintf(file, "%d ", problems[i].question[j].num2);
		}
		fprintf(file, Spaces_1);
	}
}
void PrintAnswers(int numProblems, Problem* problems, FILE* solutionsFile)
{
	for (int i = 0; i < numProblems; i++) {
		fprintf(solutionsFile, "%3d)%5d ", problems[i].position, problems[i].answer);
		if ((i + 1) % 10 == 0) fprintf(solutionsFile, New_Line_2);
		free(problems[i].question);
	}
}