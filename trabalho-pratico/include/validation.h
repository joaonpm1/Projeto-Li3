#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "hashq3.h"

int reservavalida(char *informacao, struct HashTable2* invalidusers);
int uservalido(char *informacao, struct HashTable2* invalidusers);
int voovalido(char *informacao, struct HashTable2* invalidflights);
int passengervalido(char *informacao, struct HashTable2* invalidflights, struct HashTable2* invalidusers);
#endif
