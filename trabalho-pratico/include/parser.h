#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hash.h"
#include "hashq1user.h"
#include "hashq1reserv.h"
#include "utility.h"
#include "hashq2.h"
#include "hashq1flight.h"
#include "hashq7.h"
#include "validation.h"

void parserreserv (struct HashTable* nreservas, struct HashReserv* reservas, struct Slot** listaids,struct Slot** reservsfromhotel, struct HashTable2* invalidusers, char *datasetspath);
void parserusers (struct HashUser* tabela, struct HashTable2* invalidusers, char *datasetspath);
void parsepassengers (struct HashTable2* tabela, struct HashTable2* npass, struct Slot** flightsid,struct HashTable2* invalidflights,struct HashTable2* invalidusers, char *datasetspath);
void parserflight (struct HashFlight* tabela, struct Tabelints** atrasos,struct Slot** flightsoforigin,struct HashTable2* invalidflights, char *datasetspath);

#endif
