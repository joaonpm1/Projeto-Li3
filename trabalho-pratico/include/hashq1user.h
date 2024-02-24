#ifndef HASHQ1USER_H
#define HASHQ1USER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a key-value pair
struct Userparse {
    char* id;
    char *name;
    char *birthdate;
    char *sex;
    char *passport;
    char *countrycode;
    double nreservas;
    double nvoos;
    double totalgasto;
    struct Userparse* next;
};

// Define the structure for the hash table
struct HashUser {
    int size;
    struct Userparse** table;
};

struct HashUser* createHashUser (int size);
struct Userparse* createUserparse(char* id, char *name, char *birthdate, char *sex, char *passport, char *countrycode, double nreservas, double nvoos, double totalgasto);
void insertinHashUser(struct HashUser* hashTable, char* id, char *name, char *birthdate, char *sex, char *passport, char *countrycode, double nreservas, double nvoos, double totalgasto);
struct Userparse* searchUserparse(struct HashUser* hashTable, char* id);
char* searchUserid(struct HashUser* hashTable, char* id);
void freeHashUser(struct HashUser* hashTable);
void freeUserparse(struct Userparse* user);
#endif

