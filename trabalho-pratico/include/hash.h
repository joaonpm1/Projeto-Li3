#ifndef HASH_H
#define HASH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a key-value pair
struct SlotofHash {
    char* key;
    double value;
    double times;
    struct SlotofHash* next;
};

// Define the structure for the hash table
struct HashTable {
    int size;
    struct SlotofHash** table;
};

struct HashTable* createHashTable (int size);
unsigned int hashgen(char* key, int size);
struct SlotofHash* createSlotofHash(char* key, double value, double times);
void insertin(struct HashTable* hashTable, char* key, double value, double times);
double searchvalue(struct HashTable* hashTable, char* key);
double searchtimes(struct HashTable* hashTable, char* key);
void destroyHashTable(struct HashTable* hashTable);
struct SlotofHash* search(struct HashTable* hashTable, char* key);
void printHashTable(struct HashTable* hashTable);
#endif