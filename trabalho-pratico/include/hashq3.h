#ifndef HASHQ3_H
#define HASHQ3_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a key-value pair
struct SlotofHash2 {
    char* key;
    double value;
    struct SlotofHash2* next;
};

// Define the structure for the hash table
struct HashTable2 {
    int size;
    struct SlotofHash2** table;
};

struct HashTable2* createHashTable2 (int size);
struct SlotofHash2* createSlotofHash2(char* key, double value);
void insertin2(struct HashTable2* hashTable, char* key, double value);
struct SlotofHash2* search2(struct HashTable2* hashTable, char* key);
double searchvalue2 (struct HashTable2* hashTable, char* key);
void freeHashTable2(struct HashTable2* hashTable);
void freeSlotofHash2(struct SlotofHash2* slot);
#endif