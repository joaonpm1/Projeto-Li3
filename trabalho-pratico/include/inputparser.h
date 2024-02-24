#ifndef INPUTPARSER_H
#define INPUTPARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 70

// Define a structure to store information for each type of query
typedef struct {
    char indicator[MAX_STRING_LENGTH];
    char input[MAX_STRING_LENGTH];
} Query;

// Define a structure to represent the content of the file
typedef struct {
    Query* queries;
    int numQueries;
} ParsedData;

ParsedData parseFile(const char* filename);
void freeParsedData(ParsedData* parsedData);
#endif