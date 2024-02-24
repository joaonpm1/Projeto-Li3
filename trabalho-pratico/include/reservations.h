#ifndef RESERVATIONS_H
#define RESERVATIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

double Q3 (struct HashTable2 * q3, struct HashTable *medias);
void QRESERVAS (struct HashReserv* reservas, struct HashTable* nreservas, struct HashTable2 * q3, struct Slot** reservids, char *datasetspath);
#endif
