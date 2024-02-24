#ifndef HASHQ2_H
#define HASHQ2_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1400000

// Definition of a structure for a hash table slot
struct Slot {
    char* key;
    struct Slot* next;
    struct Value* values; // Linked list of values associated with the key
};

// Definition of a structure for values associated with a key
struct Value {
    char* info;
    struct Value* next;
};

struct Value* searchp(struct Slot* table[], char* key);
void insertp(struct Slot* table[], char* key, char* info);
struct Slot* createNodep(char* key);
unsigned int hashp(char* key);
struct Slot** createTablep();
void printValuesp(struct Value* values);
void parseDate(char *date, int *year, int *month, int *day);
int compareDates(char *date1, char *date2);
void swapValues(struct Value* a, struct Value* b);
void bubbleSort(struct Value *start);
void bubbleSort2(struct Value* start);
int compare(const void *a, const void *b);
void ordernatelist(struct Value **list);
int getLength(struct Value* head);
void splitString(char *input, char **name, char **med);
void freeTable(struct Slot** table);
#endif