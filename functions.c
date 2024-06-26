#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "functions.h"


void noArgs() {
	char* inputLine = NULL;
	size_t inputLen = 0;
	
	char** lines = NULL;
	int lineCount = 0;
	
	// Get lines from user and store each line in the array of lines
	while (getline(&inputLine, &inputLen, stdin) > 1) {
		// Allocate memory
		char* line = malloc(inputLen * sizeof(char));
		char** temp = realloc(lines, (lineCount + 1) * sizeof(char*));
		
		// Check that allocation was successful
		if (temp == NULL) {
			fprintf(stderr, "malloc failed\n");
			for (int i = 0; i < lineCount; i++) {
				free(lines[i]);
			}
			free(inputLine);
			free(line);
			exit(1);
		} else {
			lines = temp;
		}
		
		// Copy the input line to allocated line and increase line count
		strcpy(line, inputLine);
		lines[lineCount] = line;
		lineCount++;
	}
	
	// Print the lines backwards
	for (int i = lineCount; i > 0; i--) {
		printf("%s", lines[i - 1]);
	}
	
	// Free allocated memory
	for (int i = 0; i < lineCount; i++) {
		free(lines[i]);
	}
	free(inputLine);
	free(lines);
	
	return;
}


void oneArg(char* inputFileName) {
	// Open input file with error checking
	FILE* inputFile = fopen(inputFileName, "r");
	if (inputFile == NULL) {
		fprintf(stderr, "reverse: cannot open file '%s'\n", inputFileName);
		exit(1);
	}
	
	char* inputLine = NULL;
	size_t inputLen = 0;

	char** lines = NULL;
	int lineCount = 0;
	
	// Read lines from input file
	while (getline(&inputLine, &inputLen, inputFile) > 0) {
		// Allocate memory for new line and resize array of lines
		char* line = malloc(inputLen * sizeof(char));
		char** temp = realloc(lines, (lineCount + 1) * sizeof(char*));
		
		// Check that allocation was successful
		if (temp == NULL) {
			fprintf(stderr, "malloc failed\n");
			for (int i = 0; i < lineCount; i++) {
				free(lines[i]);
			}
			free(inputLine);
			free(line);
			fclose(inputFile);
			exit(1);
		} else {
			lines = temp;
		}

		// Copy the input line to allocated line and increase line count
		strcpy(line, inputLine);
		lines[lineCount] = line;
		lineCount++;
	}
	fclose(inputFile);
	
	// Print the lines reversed
	for (int i = lineCount; i > 0; i--) {
		printf("%s", lines[i - 1]);
	}
	
	// Free allocated memory
	for (int i = 0; i < lineCount; i++) {
		free(lines[i]);
	}
	free(inputLine);
	free(lines);
	
	return;
}


void twoArgs(char* inputFileName, char* outputFileName) {
	struct stat inStat, outStat;

	// Get input file information
	if (stat(inputFileName, &inStat) != 0){
		fprintf(stderr, "reverse: cannot open file '%s'\n", inputFileName);
		exit(1);
	}

	// Open input file with error checking
	FILE* inputFile = fopen(inputFileName, "r");
	if (inputFile == NULL) {
		fprintf(stderr, "reverse: cannot open file '%s'\n", inputFileName);
		exit(1);
	}
	
	char* inputLine = NULL;
	size_t inputLen = 0;
	
	char** lines = NULL;
	int lineCount = 0;
	
	// Read lines from input file
	while (getline(&inputLine, &inputLen, inputFile) > 0) {
		// Allocate memory for new line and resize array of lines
		char* line = malloc(inputLen * sizeof(char));
		char** temp = realloc(lines, (lineCount + 1) * sizeof(char*));
		
		// Check that allocation was successful
		if (temp == NULL) {
			fprintf(stderr, "malloc failed\n");
			for (int i = 0; i < lineCount; i++) {
				free(lines[i]);
			}
			free(inputLine);
			free(line);
			fclose(inputFile);
			exit(1);
		} else {
			lines = temp;
		}
		
		// Copy the input line to allocated line and increase line count
		strcpy(line, inputLine);
		lines[lineCount] = line;
		lineCount++;
	}
	fclose(inputFile);
	
	// Open or create output file with error checking
	FILE* outputFile = fopen(outputFileName, "w");
	if (outputFile == NULL) {
		fprintf(stderr, "reverse: cannot open file %s\n", outputFileName);
		for (int i = 0; i < lineCount; i++) {
			free(lines[i]);
		}
		free(inputLine);
		free(lines);
		exit(1);
	}

	// Get output file information
	if (stat(outputFileName, &outStat) != 0){
		fprintf(stderr, "reverse: cannot open file '%s'\n", outputFileName);
		fclose(outputFile);
                for (int i = 0; i < lineCount; i++) {
                        free(lines[i]);
                }
                free(inputLine);
                free(lines);
		exit(1);
	}

	// Check if output file is different from output file
	if (inStat.st_ino == outStat.st_ino) { 
		fprintf(stderr, "reverse: input and output file must differ\n");
		fclose(outputFile);
                for (int i = 0; i < lineCount; i++) {
                        free(lines[i]);
                }
                free(inputLine);
                free(lines);
		exit(1);
	}

	// Write reversed lines to file
	for (int i = lineCount; i > 0; i--) {
		fprintf(outputFile, "%s", lines[i - 1]);
	}
	fclose(outputFile);
	
	// Free allocated memory
	for (int i = 0; i < lineCount; i++) {
		free(lines[i]);
	}
	free(inputLine);
	free(lines);
	
	return;
}
