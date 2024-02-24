#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashq7.h"

// Simple hash function
unsigned int hashlint(char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 7) + *key;
        key++;
    }
    return hash % TABLE_SIZE1;
}
struct Tabelints** createTablint() {
    struct Tabelints** table = (struct Tabelints**)malloc(TABLE_SIZE1 * sizeof(struct Tabelints*));
    
    // Initialize each slot to NULL
    for (int i = 0; i < TABLE_SIZE1; ++i) {
        table[i] = NULL;
    }

    return table;
}


// Function to create a new slot
struct Tabelints* createNlint(char* key) {
    struct Tabelints* newNode = (struct Tabelints*)malloc(sizeof(struct Tabelints));
    newNode->key = strdup(key);
    newNode->next = NULL;
    newNode->values = NULL;
    return newNode;
}

// Function to insert a key-value pair into the hash table
void insertlint(struct Tabelints* table[], char* key, int info) {
    unsigned int index = hashlint(key);

    if (table[index] == NULL) {
        table[index] = createNlint(key);
    }

    struct Tabelints* currentKey = table[index];
    while (currentKey != NULL) {
        if (strcmp(currentKey->key, key) == 0) {
            // Key already exists, add the new value to the list
            struct Valor* newValueNode = (struct Valor*)malloc(sizeof(struct Valor));
            newValueNode->info = info;
            newValueNode->next = currentKey->values;
            currentKey->values = newValueNode;
            return;
        }
        if (currentKey->next == NULL) {
            currentKey->next = createNlint(key);
            break;
        }
        currentKey = currentKey->next;
    }
}


// Function to search for values in the hash table based on the key
struct Valor* searchlint(struct Tabelints* table[], char* key) {
    unsigned int index = hashlint(key);
    struct Tabelints* currentKey = table[index];
    
    while (currentKey != NULL) {
        if (strcmp(currentKey->key, key) == 0) {
            // Key found, return the list of values
            return currentKey->values;
        }
        currentKey = currentKey->next;
    }

    return NULL; // Key not found, return NULL
}

void printValint(struct Valor* values) {
    struct Valor* current = values;

    while (current != NULL) {
        printf("%d\n", current->info);
        current = current->next;
    }
}

void copyTablint(struct Tabelints** sourceTable, struct Tabelints** destinationTable) {
    // Iterate through each slot in the source table
    for (int i = 0; i < TABLE_SIZE1; ++i) {
        struct Tabelints* sourceSlot = sourceTable[i];

        // Copy each linked list in the slot to the destination table
        while (sourceSlot != NULL) {
            // Create a new node for the destination table
            struct Tabelints* newSlot = createNlint(sourceSlot->key);

            // Copy the linked list of values
            struct Valor* sourceValues = sourceSlot->values;
            while (sourceValues != NULL) {
                struct Valor* newValueNode = (struct Valor*)malloc(sizeof(struct Valor));
                newValueNode->info = sourceValues->info;
                newValueNode->next = newSlot->values;
                newSlot->values = newValueNode;
                sourceValues = sourceValues->next;
            }

            // Insert the new slot into the destination table
            unsigned int index = hashlint(newSlot->key);
            if (destinationTable[index] == NULL) {
                destinationTable[index] = newSlot;
            } else {
                struct Tabelints* currentSlot = destinationTable[index];
                while (currentSlot->next != NULL) {
                    currentSlot = currentSlot->next;
                }
                currentSlot->next = newSlot;
            }

            sourceSlot = sourceSlot->next;
        }
    }
}

// Function to calculate the length of the linked list
int getLinkedListLength(struct Valor *list) {
    int length = 0;
    while (list != NULL) {
        length++;
        list = list->next;
    }
    return length;
}

// Function to swap two values in a linked list
void swapValues1(struct Valor *a, struct Valor *b) {
    int temp = a->info;
    a->info = b->info;
    b->info = temp;
}

// Function to sort a linked list in ascending order
struct Valor* sortLinkedList(struct Valor *list) {
    int swapped;
    struct Valor *ptr1;
    struct Valor *lptr = NULL;

    if (list == NULL) {
        return NULL; // Empty list, nothing to sort
    }
    do {
        swapped = 0;
        ptr1 = list;
        while (ptr1->next != lptr) {
            if (ptr1->info > ptr1->next->info) {
                swapValues1(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    return list;
}

int median(struct Valor* node) {
    struct Valor* current = node;
    int length = 0;
    // Calculate the length of the linked list
    while (current != NULL) {
        length++;
        current = current->next;
    }

    // If the length of the linked list is even, return the average of the two middle elements.
    // Otherwise, return the middle element.
    if (length % 2 == 0) {
        current = node;
        for (int i = 0; i < length / 2 - 1; i++) {
            current = current->next;
        }
        return (current->info + current->next->info) / 2;
    } else {
        current = node;
        for (int i = 0; i < length / 2; i++) {
            current = current->next;
        }
        return current->info;
    }
}
void freeIntTable(struct Tabelints* table[]) {
    // Free each slot and its associated values
    for (int i = 0; i < TABLE_SIZE1; ++i) {
        struct Tabelints* currentSlot = table[i];
        while (currentSlot != NULL) {
            struct Tabelints* tempSlot = currentSlot;
            currentSlot = currentSlot->next;

            // Free values associated with the key
            struct Valor* currentValue = tempSlot->values;
            while (currentValue != NULL) {
                struct Valor* tempValue = currentValue;
                currentValue = currentValue->next;
                free(tempValue);
            }

            free(tempSlot->key);
            free(tempSlot);
        }
    }

    // Free the array of slots
    free(table);
}