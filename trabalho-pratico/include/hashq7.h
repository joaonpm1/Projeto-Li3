#ifndef HASHQ7_H
#define HASHQ7_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE1 10000

// Definition of a structure for a hash table slot
struct Tabelints {
    char* key;
    struct Tabelints* next;
    struct Valor* values; // Linked list of values associated with the key
};

// Definition of a structure for values associated with a key
struct Valor {
    int info;
    struct Valor* next;
};

struct Valor* searchlint(struct Tabelints* table[], char* key);
void insertlint(struct Tabelints* table[], char* key, int info);
struct Tabelints* createNlint(char* key);
unsigned int hashlint(char* key);
struct Tabelints** createTablint();
void printValint(struct Valor* values);
void copyTablint(struct Tabelints** sourceTable, struct Tabelints** destinationTable);
int median(struct Valor* node);
int getLinkedListLength(struct Valor *list);
struct Valor* sortLinkedList(struct Valor *list);
void swapValues1(struct Valor *a, struct Valor *b);
void freeIntTable(struct Tabelints* table[]);
#endif