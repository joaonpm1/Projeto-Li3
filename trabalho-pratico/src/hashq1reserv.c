#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashq1reserv.h"
#include "hash.h"


struct Reservparse* createReservparse(char* id, char *user_id, char *hotel_id, char *hotel_name, char *hotel_stars, char *begin_date, char *end_date, double price_per_night, char *includes_breakfast, int rating, double numbernights, double totalprice) {
    struct Reservparse* reserv = (struct Reservparse*)malloc(sizeof(struct Reservparse));
    reserv->id = strdup(id);
    reserv->user_id = strdup(user_id);
    reserv->hotel_id = strdup(hotel_id);
    reserv->hotel_name = strdup(hotel_name);
    reserv->hotel_stars = strdup(hotel_stars);
    reserv->begin_date = strdup(begin_date);
    reserv->end_date = strdup(end_date);
    reserv->price_per_night = price_per_night;
    reserv->includes_breakfast = strdup (includes_breakfast);
    reserv->rating = rating;
    reserv->numbernights = numbernights;
    reserv->totalprice = totalprice;
    reserv->next = NULL;
    return reserv;
}

// Create a new hash table with a given size

struct HashReserv* createHashReserv (int size) {
    struct HashReserv* hashTable = (struct HashReserv*)malloc(sizeof(struct HashReserv));
    hashTable->size = size;
    hashTable->table = (struct Reservparse**)malloc(sizeof(struct Reservparse*) * size);

    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

void insertinHashReserv(struct HashReserv* hashTable, char* id, char *user_id, char *hotel_id, char *hotel_name, char *hotel_stars, char *begin_date, char *end_date, double price_per_night, char *includes_breakfast, int rating, double numbernights, double totalprice) {
    unsigned int index = hashgen(id, hashTable->size);
    struct Reservparse* reserv = hashTable->table[index];
    
    while (reserv != NULL) {
        if (strcmp(id, reserv->id) == 0) {
            // Key already exists, update the slot
            reserv->hotel_id = strdup(hotel_id);
            reserv->user_id = strdup(user_id);
            reserv->hotel_name = strdup(hotel_name);
            reserv->hotel_stars = strdup(hotel_stars);
            reserv->begin_date = strdup(begin_date);
            reserv->end_date = strdup(end_date);
            reserv->price_per_night = price_per_night;
            reserv->includes_breakfast = strdup (includes_breakfast);
            reserv->rating = rating;
            reserv->numbernights = numbernights;
            reserv->totalprice = totalprice;
    
            return;
        }
        reserv = reserv->next;
    }

    // Key doesn't exist, create a new slot and insert it at the beginning of the linked list
    struct Reservparse* current = createReservparse (id, user_id, hotel_id, hotel_name, hotel_stars, begin_date, end_date, price_per_night, includes_breakfast, rating, numbernights, totalprice);
    current->next = hashTable->table[index];
    hashTable->table[index] = current;
}

struct Reservparse* searchReservparse(struct HashReserv* hashTable, char* id) {
    unsigned int index = hashgen(id, hashTable->size);
    struct Reservparse* current = hashTable->table[index];
    
    while (current != NULL) {
        if (strcmp(id, current->id) == 0) {
            return current;
        }
        current = current->next;
    }

    // Key not found, return a default value or handle the case as needed
    return NULL;
}

void freeReservparse(struct Reservparse* reservation) {
    // Free each dynamically allocated string
    free(reservation->id);
    free(reservation->user_id);
    free(reservation->hotel_id);
    free(reservation->hotel_name);
    free(reservation->hotel_stars);
    free(reservation->begin_date);
    free(reservation->end_date);
    free(reservation->includes_breakfast);

    // Free the Reservparse structure itself
    free(reservation);
}

// Function to free memory allocated for a HashReserv structure
void freeHashReserv(struct HashReserv* hashTable) {
    // Iterate through each slot in the hash table
    for (int i = 0; i < hashTable->size; i++) {
        // Get the Reservparse structure in the current slot
        struct Reservparse* currentReservation = hashTable->table[i];

        // Iterate through the linked list in the current slot
        while (currentReservation != NULL) {
            // Get the next Reservparse structure in the linked list
            struct Reservparse* nextReservation = currentReservation->next;

            // Free the current Reservparse structure
            freeReservparse(currentReservation);

            // Move to the next Reservparse structure in the linked list
            currentReservation = nextReservation;
        }
    }

    // Free the array of Reservparse pointers
    free(hashTable->table);

    // Free the HashReserv structure itself
    free(hashTable);
}