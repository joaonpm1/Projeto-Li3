#ifndef HASHQ1FLIGHT_H
#define HASHQ1FLIGHT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a key-value pair
struct Flightparse {
    char* id;
    char *airline;
    char *plane_model;
    char *origin;
    char *destination;
    char *schedule_departure_date;
    char *schedule_arrival_date;
    int delay;
    struct Flightparse* next;
};

// Define the structure for the hash table
struct HashFlight {
    int size;
    struct Flightparse** table;
};

struct HashFlight* createHashFlight (int size);
struct Flightparse* createFlightparse(char* id, char *airline, char *plane_model, char *origin, char *destination, char *schedule_departure_date, char *schedule_arrival_date, int delay);
void insertinHashFlight(struct HashFlight* hashTable, char* id, char *airline, char *plane_model, char *origin, char *destination, char *schedule_departure_date, char *schedule_arrival_date, int delay);
struct Flightparse* searchFlightparse(struct HashFlight* hashTable, char* id);
void freeFlightparse(struct Flightparse* flight);
void freeHashFlight(struct HashFlight* hashTable);
#endif