#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashq3.h"
#include "hash.h"

// Create a new key-value pair
struct SlotofHash2* createSlotofHash2(char* key, double value) {
    struct SlotofHash2* pair = (struct SlotofHash2*)malloc(sizeof(struct SlotofHash2));
    pair->key = strdup(key);
    pair->value = value;
    pair->next = NULL;
    return pair;
}

// Create a new hash table with a given size
struct HashTable2* createHashTable2(int size) {
    struct HashTable2* hashTable = (struct HashTable2*)malloc(sizeof(struct HashTable2));
    hashTable->size = size;
    hashTable->table = (struct SlotofHash2**)malloc(sizeof(struct SlotofHash2*) * size);

    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

void insertin2(struct HashTable2* hashTable, char* key, double value) {
    unsigned int index = hashgen(key, hashTable->size);
    struct SlotofHash2* current = hashTable->table[index];
    
    while (current != NULL) {
        if (strcmp(key, current->key) == 0) {
            // Key already exists, update the value and times
            current->value = value;
            return;
        }
        current = current->next;
    }

    // Key doesn't exist, create a new slot and insert it at the beginning of the linked list
    struct SlotofHash2* pair = createSlotofHash2(key, value);
    pair->next = hashTable->table[index];
    hashTable->table[index] = pair;
}

struct SlotofHash2* search2(struct HashTable2* hashTable, char* key) {
    unsigned int index = hashgen(key, hashTable->size);
    struct SlotofHash2* current = hashTable->table[index];
    
    while (current != NULL) {
        if (strcmp(key, current->key) == 0) {
            return current;
        }
        current = current->next;
    }

    // Key not found, return a default value or handle the case as needed
    return NULL;
}

double searchvalue2 (struct HashTable2* hashTable, char* key) {
    unsigned int index = hashgen(key, hashTable->size);
    struct SlotofHash2* current = hashTable->table[index];
    
    while (current != NULL) {
        if (strcmp(key, current->key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    // Key not found, return a default value or handle the case as needed
    return 0;
}

// Function to free memory allocated for a SlotofHash2 structure
void freeSlotofHash2(struct SlotofHash2* slot) {
    // Free the dynamically allocated key string
    free(slot->key);

    // Free the SlotofHash2 structure itself
    free(slot);
}

// Function to free memory allocated for a HashTable2 structure
void freeHashTable2(struct HashTable2* hashTable) {
    // Iterate through each slot in the hash table
    for (int i = 0; i < hashTable->size; i++) {
        // Get the SlotofHash2 structure in the current slot
        struct SlotofHash2* currentSlot = hashTable->table[i];

        // Iterate through the linked list in the current slot
        while (currentSlot != NULL) {
            // Get the next SlotofHash2 structure in the linked list
            struct SlotofHash2* nextSlot = currentSlot->next;

            // Free the current SlotofHash2 structure
            freeSlotofHash2(currentSlot);

            // Move to the next SlotofHash2 structure in the linked list
            currentSlot = nextSlot;
        }
    }

    // Free the array of SlotofHash2 pointers
    free(hashTable->table);

    // Free the HashTable2 structure itself
    free(hashTable);
}