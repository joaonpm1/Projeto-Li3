#ifndef HASHQ1RESERV_H
#define HASHQ1RESERV_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a key-value pair
struct Reservparse {
    char* id;
    char *user_id;
    char *hotel_id;
    char *hotel_name;
    char *hotel_stars;
    char *begin_date;
    char *end_date;
    double price_per_night;
    char *includes_breakfast;
    int rating;
    double numbernights;
    double totalprice;
    struct Reservparse* next;
};

// Define the structure for the hash table
struct HashReserv {
    int size;
    struct Reservparse** table;
};

struct HashReserv* createHashReserv (int size);
struct Reservparse* createReservparse(char* id, char *user_id, char *hotel_id, char *hotel_name, char *hotel_stars, char *begin_date, char *end_date, double price_per_night, char *includes_breakfast, int rating, double numernights, double totalprice);
void insertinHashReserv(struct HashReserv* hashTable, char* id, char *user_id, char *hotel_id, char *hotel_name, char *hotel_stars, char *begin_date, char *end_date, double price_per_night, char *includes_breakfast, int rating, double numbernights, double totalprice);
struct Reservparse* searchReservparse(struct HashReserv* hashTable, char* id);
void freeHashReserv(struct HashReserv* hashTable);
void freeReservparse(struct Reservparse* reservation);
#endif