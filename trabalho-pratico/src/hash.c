#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// Create a new key-value pair
struct SlotofHash* createSlotofHash(char* key, double value, double times) {
    struct SlotofHash* pair = (struct SlotofHash*)malloc(sizeof(struct SlotofHash));
    pair->key = strdup(key);
    pair->value = value;
    pair->next = NULL;
    pair->times = times;
    return pair;
}

// Create a new hash table with a given size
struct HashTable* createHashTable(int size) {
    struct HashTable* hashTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    hashTable->size = size;
    hashTable->table = (struct SlotofHash**)malloc(sizeof(struct SlotofHash*) * size);

    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }

    return hashTable;
}

// Hash function to map a string key to an index
unsigned int hashgen(char* key, int size) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + (*key);
        key++;
    }
    return hash % size;
}

void insertin(struct HashTable* hashTable, char* key, double value, double times) {
    unsigned int index = hashgen(key, hashTable->size);
    struct SlotofHash* current = hashTable->table[index];
    
    while (current != NULL) {
        if (strcmp(key, current->key) == 0) {
            // Key already exists, update the value and times
            current->value = value;
            current->times = times;
            return;
        }
        current = current->next;
    }

    // Key doesn't exist, create a new slot and insert it at the beginning of the linked list
    struct SlotofHash* pair = createSlotofHash(key, value, times);
    pair->next = hashTable->table[index];
    hashTable->table[index] = pair;
}

// Search for a value by key
double searchvalue(struct HashTable* hashTable, char* key) {
    unsigned int index = hashgen(key, hashTable->size);
    struct SlotofHash* current = hashTable->table[index];
    
    while (current != NULL) {
        if (strcmp(key, current->key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    // Key not found, return a default value or handle the case as needed
    return -1;
}

// Search for the times of a value by key
double searchtimes(struct HashTable* hashTable, char* key) {
    unsigned int index = hashgen(key, hashTable->size);
    struct SlotofHash* current = hashTable->table[index];
    
    while (current != NULL) {
        if (strcmp(key, current->key) == 0) {
            return current->times;
        }
        current = current->next;
    }

    // Key not found, return a default value or handle the case as needed
    return -1;
}

struct SlotofHash* search(struct HashTable* hashTable, char* key) {
    unsigned int index = hashgen(key, hashTable->size);
    struct SlotofHash* current = hashTable->table[index];
    
    while (current != NULL) {
        if (strcmp(key, current->key) == 0) {
            return current;
        }
        current = current->next;
    }

    // Key not found, return a default value or handle the case as needed
    return NULL;
}

// Clean up the hash table and free memory
void destroyHashTable(struct HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        struct SlotofHash* current = hashTable->table[i];
        while (current != NULL) {
            struct SlotofHash* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(hashTable->table);
    free(hashTable);
}

void printHashTable(struct HashTable* hashTable) {
    if (hashTable == NULL || hashTable->table == NULL) {
        printf("Invalid HashTable\n");
        return;
    }

    printf("Hash Table Elements:\n");
    for (int i = 0; i < hashTable->size; ++i) {
        struct SlotofHash* slot = hashTable->table[i];
        while (slot != NULL) {
            printf("Key: %s, Value: %f, Times: %f\n", slot->key, slot->value, slot->times);
            slot = slot->next;
        }
    }
}
