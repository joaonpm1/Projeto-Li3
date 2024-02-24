#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/inputparser.h"

// Function to parse the file and store the content in the ParsedData structure
ParsedData parseFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    ParsedData parsedData;
    parsedData.queries = NULL;
    parsedData.numQueries = 0;

    char line[MAX_STRING_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove newline character if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Allocate memory for a new query
        parsedData.queries = realloc(parsedData.queries, (parsedData.numQueries + 1) * sizeof(Query));
        if (parsedData.queries == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        // Parse the line and store the information in the query structure
        sscanf(line, "%s %[^\n]", parsedData.queries[parsedData.numQueries].indicator,
                                  parsedData.queries[parsedData.numQueries].input);

        // Increment the number of queries
        parsedData.numQueries++;
    }

    fclose(file);
    return parsedData;
}

// Function to free the memory allocated for the ParsedData structure
void freeParsedData(ParsedData* parsedData) {
    free(parsedData->queries);
    parsedData->numQueries = 0;
}
