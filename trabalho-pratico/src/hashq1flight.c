#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashq1flight.h"
#include "hash.h"

struct Flightparse* createFlightparse(char* id, char *airline, char *plane_model, char *origin, char *destination, char *schedule_departure_date, char *schedule_arrival_date, int delay) {
    struct Flightparse* flight = (struct Flightparse*)malloc(sizeof(struct Flightparse));
    flight->id = strdup(id);
    flight->airline = strdup(airline);
    flight->plane_model = strdup(plane_model);
    flight->origin = strdup(origin);
    flight->destination = strdup(destination);
    flight->schedule_departure_date = strdup(schedule_departure_date);
    flight->schedule_arrival_date = strdup(schedule_arrival_date);
    flight->delay = delay;
    flight->next = NULL;
    return flight;
}

// Create a new hash table with a given size

struct HashFlight* createHashFlight (int size) {
    struct HashFlight* hashTable = (struct HashFlight*)malloc(sizeof(struct HashFlight));
    hashTable->size = size;
    hashTable->table = (struct Flightparse**)malloc(sizeof(struct Flightparse*) * size);

    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}
void insertinHashFlight(struct HashFlight* hashTable, char* id, char *airline, char *plane_model, char *origin, char *destination, char *schedule_departure_date, char *schedule_arrival_date, int delay) {
    unsigned int index = hashgen(id, hashTable->size);
    struct Flightparse* flight = hashTable->table[index];
    
    while (flight != NULL) {
        if (strcmp(id, flight->id) == 0) {
            // Key already exists, update the slot
            flight->id = strdup(id);
            flight->airline = strdup(airline);
            flight->plane_model = strdup(plane_model);
            flight->origin = strdup(origin);
            flight->destination = strdup (destination);
            flight->schedule_departure_date = strdup(schedule_departure_date);
            flight->schedule_arrival_date = strdup(schedule_arrival_date);
            flight->delay = delay;
    
            return;
        }
        flight = flight->next;
    }

    // Key doesn't exist, create a new slot and insert it at the beginning of the linked list
    struct Flightparse* current = createFlightparse (id, airline, plane_model, origin, destination, schedule_departure_date, schedule_arrival_date, delay);
    current->next = hashTable->table[index];
    hashTable->table[index] = current;
}

struct Flightparse* searchFlightparse(struct HashFlight* hashTable, char* id) {
    unsigned int index = hashgen(id, hashTable->size);
    struct Flightparse* current = hashTable->table[index];
    
    while (current != NULL) {
        if (strcmp(id, current->id) == 0) {
            return current;
        }
        current = current->next;
    }

    // Key not found, return a default value or handle the case as needed
    return NULL;
}

void freeFlightparse(struct Flightparse* flight) {
    // Free each dynamically allocated string
    free(flight->id);
    free(flight->airline);
    free(flight->plane_model);
    free(flight->origin);
    free(flight->destination);
    free(flight->schedule_departure_date);
    free(flight->schedule_arrival_date);

    // Free the Flightparse structure itself
    free(flight);
}

// Function to free memory allocated for a HashFlight structure
void freeHashFlight(struct HashFlight* hashTable) {
    // Iterate through each slot in the hash table
    for (int i = 0; i < hashTable->size; i++) {
        // Get the Flightparse structure in the current slot
        struct Flightparse* currentFlight = hashTable->table[i];

        // Iterate through the linked list in the current slot
        while (currentFlight != NULL) {
            // Get the next Flightparse structure in the linked list
            struct Flightparse* nextFlight = currentFlight->next;

            // Free the current Flightparse structure
            freeFlightparse(currentFlight);

            // Move to the next Flightparse structure in the linked list
            currentFlight = nextFlight;
        }
    }

    // Free the array of Flightparse pointers
    free(hashTable->table);

    // Free the HashFlight structure itself
    free(hashTable);
}
