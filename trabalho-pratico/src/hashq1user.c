#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashq1user.h"
#include "hash.h"

// Create a new key-value pair
struct Userparse* createUserparse (char* id, char *name, char *birthdate, char *sex, char *passport, char *countrycode, double nreservas, double nvoos, double totalgasto) {
    struct Userparse* user = (struct Userparse*)malloc(sizeof(struct Userparse));
    user->id = strdup(id);
    user->name = strdup(name);
    user->birthdate = strdup(birthdate);
    user->sex = strdup(sex);
    user->passport = strdup(passport);
    user->countrycode = strdup(countrycode);
    user->nreservas = nreservas;
    user->nvoos = nvoos;
    user->totalgasto = totalgasto;
    user->next = NULL;
    return user;
}

// Create a new hash table with a given size
struct HashUser* createHashUser (int size) {
    struct HashUser* hashTable = (struct HashUser*)malloc(sizeof(struct HashUser));
    hashTable->size = size;
    hashTable->table = (struct Userparse**)malloc(sizeof(struct Userparse*) * size);

    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

void insertinHashUser(struct HashUser* hashTable, char* id, char *name, char *birthdate, char *sex, char *passport, char *countrycode, double nreservas, double nvoos, double totalgasto) {
    unsigned int index = hashgen(id, hashTable->size);
    struct Userparse* current = hashTable->table[index];
    
    while (current != NULL) {
        if (strcmp(id, current->id) == 0) {
            // Key already exists, update the slot
            current->name = strdup(name);
            current->birthdate = strdup(birthdate);
            current->sex = strdup (sex);
            current->passport = strdup (passport);
            current->countrycode = strdup(countrycode);
            current->nreservas = nreservas;
            current->nvoos = nvoos;
            current->totalgasto = totalgasto;
            return;
        }
        current = current->next;
    }

    // Key doesn't exist, create a new slot and insert it at the beginning of the linked list
    struct Userparse* user = createUserparse (id, name, birthdate, sex, passport, countrycode, nreservas, nvoos, totalgasto);
    user->next = hashTable->table[index];
    hashTable->table[index] = user;
}

struct Userparse* searchUserparse(struct HashUser* hashTable, char* id) {
    unsigned int index = hashgen(id, hashTable->size);
    struct Userparse* current = hashTable->table[index];
    
    while (current != NULL) {
        if (strcmp(id, current->id) == 0) {
            return current;
        }
        current = current->next;
    }

    // Key not found, return a default value or handle the case as needed
    return NULL;
}

char* searchUserid(struct HashUser* hashTable, char* id) {
    unsigned int index = hashgen(id, hashTable->size);
    struct Userparse* current = hashTable->table[index];
    
    while (current != NULL) {
        if (strcmp(id, current->id) == 0) {
            return current->id;
        }
        current = current->next;
    }

    // Key not found, return a default value or handle the case as needed
    return NULL;
}

// Function to free memory allocated for a Userparse structure
void freeUserparse(struct Userparse* user) {
    // Free each dynamically allocated string
    free(user->id);
    free(user->name);
    free(user->birthdate);
    free(user->sex);
    free(user->passport);
    free(user->countrycode);

    // Free the Userparse structure itself
    free(user);
}

// Function to free memory allocated for a HashUser structure
void freeHashUser(struct HashUser* hashTable) {
    // Iterate through each slot in the hash table
    for (int i = 0; i < hashTable->size; i++) {
        // Get the Userparse structure in the current slot
        struct Userparse* currentUser = hashTable->table[i];

        // Iterate through the linked list in the current slot
        while (currentUser != NULL) {
            // Get the next Userparse structure in the linked list
            struct Userparse* nextUser = currentUser->next;

            // Free the current Userparse structure
            freeUserparse(currentUser);

            // Move to the next Userparse structure in the linked list
            currentUser = nextUser;
        }
    }

    // Free the array of Userparse pointers
    free(hashTable->table);

    // Free the HashUser structure itself
    free(hashTable);
}
