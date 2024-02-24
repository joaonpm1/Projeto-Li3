#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Interative.h"
#include "../include/parser.h"

void IterativeMode () {
    char datasetspath[30];
    printf("Please, present the data/path you'd like to acess: ");
    fgets(datasetspath, sizeof(datasetspath), stdin);

    // Remove the newline character at the end of the input, if present
    if (datasetspath[strlen(datasetspath) - 1] == '\n') {
        datasetspath[strlen(datasetspath) - 1] = '\0';
    }
    struct HashUser* q1users = createHashUser(170000);
    struct HashTable2* invalidusers = createHashTable2(600);
    parserusers(q1users, invalidusers, datasetspath);

    struct HashReserv* q1reserv = createHashReserv(1000000);
    struct HashTable* nreservas = createHashTable(1000000);
    struct Slot** reservids = createTablep();
    struct Slot** reservsfromhotel = createTablep();
    parserreserv(nreservas, q1reserv, reservids, reservsfromhotel, invalidusers, datasetspath);

    struct HashFlight* q1flights = createHashFlight(10000);
    struct Tabelints** medatrasos = createTablint();
    struct Slot** flightsoforigin = createTablep();
    struct HashTable2* invalidflights = createHashTable2(600);
    parserflight(q1flights, medatrasos,flightsoforigin, invalidflights, datasetspath);

    struct HashTable2* nvoos = createHashTable2(70000);
    struct HashTable2* npass = createHashTable2(70000);
    struct Slot** flightsid = createTablep();
    parsepassengers(nvoos, npass, flightsid, invalidflights, invalidusers, datasetspath);

    //A query7 está essencialmente toda resolvida aqui, primeiro é ordenada por ordem crescente a lista dos atrasos de um aeroporto, depois é calculado o valor da mediana
    //dos atrasos dessa lista e por fim esse valor é concatenado com o respetivo aeroprto em uma única string no formato "aeroporto;mediana".
    char *array7[25];
    int indice = 0;
    for (int i=0; i<TABLE_SIZE1; i++) {
        if (medatrasos[i] != NULL) {
            struct Valor* sorted = sortLinkedList(medatrasos[i]->values);
            int med = median(sorted);
            char str[4];
            sprintf(str, "%d", med);
            char *modi = strcat(medatrasos[i]->key, ";");
            modi = strcat(modi, str);
            array7[indice] = strdup(modi);
            indice++;
            free(modi);
        }
    }
    qsortStrings7(array7, indice);
    int display=0;
    char input[3]; 
while (1) {
    printf("\n         WELCOME TO OUR APP\n     Queries: 1 2 3 4 5 6 7 8 9\nCHOOSE WHICH QUERY YOU'D LIKE TO CONSULT: ");
    scanf("%3s", input);
    if ((strcmp(input, "1") == 0) || (strcmp(input, "2") == 0) ||  (strcmp(input, "3") == 0) ||  (strcmp(input, "4") == 0) ||  (strcmp(input, "5") == 0) ||  (strcmp(input, "6") == 0) ||  (strcmp(input, "7") == 0) ||  (strcmp(input, "8") == 0) ||  (strcmp(input, "9") == 0)) {
        break;
    }
    else printf("Error: Invalid input\n");
    }
while (1) {
    while(1) {
    printf("CHOOSE \"N\"FOR NORMAL DISPLAY AND \"F\" FOR BATCH DISPLAY: ");
    char input1[10]; 
    scanf("%3s", input1);
    if (strlen(input1)>1) printf("Error: Invalid input\n");
    if (strcasecmp(input1, "F") == 0) {
        display=1;
        break;
    }
    else if (strcasecmp(input1, "N") == 0) {
        display=0;
        break;
    }}
////////////////////////////
//////////////////////////// QUERY 1
if ((strcasecmp(input, "1") == 0) && !display) {
    char id[30]; 
    printf("Please, write your user \"id\" or your reservation/flight matching \"id\": ");
    scanf("%29s", id);
    if (startsWithBook(id)) {
        if (searchReservparse(q1reserv, id) != NULL) {
            struct Reservparse* reserva = searchReservparse(q1reserv, id);
            char *booli = strdup(reserva->includes_breakfast);
            capitalizeFirstLetter(booli);
            printf("%s;%s;%s;%s;%s;%s;%.0f;%.3f\n\n", reserva->hotel_id, reserva->hotel_name, reserva->hotel_stars, reserva->begin_date, reserva->end_date, booli, reserva->numbernights, reserva->totalprice);
            free(booli);
        }
    }

    else if (startsWith0000(id)) {
        if (searchFlightparse(q1flights, id) != NULL) {
            struct Flightparse* teste = searchFlightparse(q1flights, id);
            printf("%s;%s;%s;%s;%s;%s;%.0f;%d\n", teste->airline, teste->plane_model, teste->origin, teste->destination, teste->schedule_departure_date, teste->schedule_arrival_date, searchvalue2(npass, teste->id), teste->delay);
        }
    }
    else {
        if (searchUserparse(q1users, id) != NULL) {
            struct Userparse* current = searchUserparse(q1users, id);
            printf("%s;%s;%.0f;%s;%s;%.0f;%.0f;%.3f\n", current->name, current->sex, calculateAge(current->birthdate), current->countrycode, current->passport, searchvalue2(nvoos, current->id), searchtimes(nreservas, current->id), searchvalue(nreservas, current->id));
        }
        else {
            printf("\nError, not a valid \"id\" from either reservation, flight or user.\nPlease care to try again.\n");
        }
    }
}
////////////////////////////
//////////////////////////// QUERY 1F
else if ((strcmp(input, "1") == 0) && display) {
    char id[30]; 
    printf("\nPlease, write your user \"id\" or your reservation/flight matching \"id\": ");
    scanf("%29s", id);
    if (startsWithBook(id)) {
        if (searchReservparse(q1reserv, id) != NULL) {
            struct Reservparse* freserva = searchReservparse(q1reserv, id);
            char *booli = freserva->includes_breakfast;
            capitalizeFirstLetter(booli);
            printf("--- 1 ---\nhotel_id: %s\nhotel_name: %s\nhotel_stars: %s\nbegin_date: %s\nend_date: %s\nincludes_breakfast: %s\nnights: %.0f\ntotal_price: %.3f\n\n", freserva->hotel_id, freserva->hotel_name, freserva->hotel_stars, freserva->begin_date, freserva->end_date, booli, freserva->numbernights, freserva->totalprice);
        }
    }
    else if (startsWith0000(id)) {
        if (searchFlightparse(q1flights, id) != NULL) {
            struct Flightparse* fteste = searchFlightparse(q1flights, id);
            printf("--- 1 ---\nairline: %s\nplane_model: %s\norigin: %s\ndestination: %s\nschedule_departure_date: %s\nschedule_arrival_date: %s\npassengers: %.0f\ndelay: %d\n", fteste->airline, fteste->plane_model, fteste->origin, fteste->destination, fteste->schedule_departure_date, fteste->schedule_arrival_date, searchvalue2(npass, fteste->id), fteste->delay);
        }
    }
    else {
        if (searchUserparse(q1users, id) != NULL) {
            struct Userparse* currentf = searchUserparse(q1users, id);
            printf("--- 1 ---\nname: %s\nsex: %s\nage: %.0f\ncountry_code: %s\npassport: %s\nnumber_of_flights: %.0f\nnumber_of_reservations: %.0f\ntotal_spent: %.3f\n", currentf->name, currentf->sex, calculateAge(currentf->birthdate), currentf->countrycode, currentf->passport, searchvalue2(nvoos, currentf->id), searchtimes(nreservas, currentf->id), searchvalue(nreservas, currentf->id));
        }
        else {
            printf("\nError, not a valid \"id\" from either reservation, flight or user.\nPlease care to try again.\n");
        }
    }
}

///////////////////////////////
/////////////////////////////// QUERY 3

else if ((strcasecmp(input, "3") == 0) && !display) {
    char hotelid[10]; 
    printf("Please, write the \"id\" from the hotel you wanna consult the rating of: ");
    scanf("%29s", hotelid);
        if (searchp (reservsfromhotel, hotelid) != NULL) {
            struct Value* keytokey=searchp(reservsfromhotel, hotelid);
            double sum=0;
            double times=1;
            while (keytokey != NULL) {
                struct Reservparse* temp = searchReservparse(q1reserv, keytokey->info);
                sum+=temp->rating;
                times++;
                keytokey=keytokey->next;
            }
            printf("%.3f\n", sum/times);
        }
        else {
            printf("\nError, not a valid \"id\" from an hotel.\nPlease care to try again.\n");
        }
    }
////////////////////////////
//////////////////////////// QUERY 3F
else if ((strcasecmp(input, "3") == 0) && display) {
    char hotelid[10]; 
    printf("Please, write the \"id\" from the hotel you wanna consult the rating of: ");
    scanf("%29s", hotelid);
    if (searchp(reservsfromhotel, hotelid) != NULL) {
            struct Value* keytokey=searchp(reservsfromhotel, hotelid);
            double sum=0;
            double times=1;
            while (keytokey != NULL) {
                struct Reservparse* temp = searchReservparse(q1reserv, keytokey->info);
                sum+=temp->rating;
                times++;
                keytokey=keytokey->next;
            }
            printf("--- 1 ---\nrating: %.3f\n", sum/times);
        }
        else {
            printf("\nError, not a valid \"id\" from an hotel.\nPlease care to try again.\n");
        }
}
//////////////////////////////
////////////////////////////// QUERY 7
else if ((strcasecmp(input, "7") == 0) && !display) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char topx[6];
    printf("Please, choose the \"N\" to check the TopN medians of delay of the existent airports: ");
    fgets(topx, sizeof(topx), stdin);

    // Remove the newline character at the end of the input, if present
    if (topx[strlen(topx) - 1] == '\n') {
        topx[strlen(topx) - 1] = '\0';
    }
        int input7 = atoi(topx);
        if (input7 > indice) input7=indice;
        for (int i = 0; i<input7; i++) {
                printf("%s\n", array7[i]);
        }
    }
////////////////////////////
//////////////////////////// QUERY 7F
else if ((strcasecmp(input, "7") == 0) && display) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char topx[6];
    printf("Please, choose the \"N\" to check the TopN medians of delay of the existent airports: ");
    fgets(topx, sizeof(topx), stdin);

    // Remove the newline character at the end of the input, if present
    if (topx[strlen(topx) - 1] == '\n') {
        topx[strlen(topx) - 1] = '\0';
    }
        int input7f = atoi(topx);
        if (input7f > indice) input7f=indice;
        for (int i = 0; i<input7f; i++) {
                char *name;
                char *med;
                splitString(array7[i], &name, &med);
                printf("--- %d ---\nname: %s\nmedian: %s\n", (i+1), name, med);
                if (i != (input7f-1)) {
                    printf("\n");
                }
                free(name);
                free(med);
        }
    }
/////////////////////////////
///////////////////////////// QUERY 6
else if ((strcasecmp(input, "6") == 0) && !display) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char yearnN[12];
    printf("Please, choose the year and the \"N\" to check the TopN airports with most passengers for that year: ");
    fgets(yearnN, sizeof(yearnN), stdin);

    // Remove the newline character at the end of the input, if present
    if (yearnN[strlen(yearnN) - 1] == '\n') {
        yearnN[strlen(yearnN) - 1] = '\0';
    }
    int ano;
    int topN;
    separateString(yearnN, &ano, &topN);
    struct HashTable2* passengersanoP = createHashTable2(1000);
    struct HashTable2* passengersanoC = createHashTable2(1000);
    for (int i = 0; i < q1flights->size; i++) {
        struct Flightparse* current = q1flights->table[i];
        while (current != NULL) {
            char *year = strdup(current->schedule_departure_date);
            year = extractYear(year);
            int year1 =  atoi(year);
            free(year);
            if (year1 == ano) {
                 if (searchvalue2(passengersanoP, current->origin) == 0) {
                        insertin2(passengersanoP, current->origin, searchvalue2(npass, current->id));
                    }
                else {
                    int somatorio = searchvalue2(passengersanoP, current->origin) + searchvalue2(npass, current->id);
                    insertin2(passengersanoP, current->origin, somatorio);
                }
                if (searchvalue2(passengersanoC, current->destination) == 0) {
                        insertin2(passengersanoC, current->destination, searchvalue2(npass, current->id));
                    }
                else {
                    int somatorio = searchvalue2(passengersanoC, current->destination) + searchvalue2(npass, current->id);
                    insertin2(passengersanoC, current->destination, somatorio);
                }
            }
            current = current->next;
        }
    }

    for (int i = 0; i < passengersanoC->size; i++) {
        struct SlotofHash2* current = passengersanoC->table[i];
        while (current != NULL) { 
            if (searchvalue2(passengersanoP, current->key) == 0) {
                insertin2(passengersanoP, current->key, current->value);
            }
            else {
                insertin2(passengersanoP, current->key, current->value+searchvalue2(passengersanoP, current->key));
            }
            current = current->next;
        }
    }

    struct Slot** respostaano = createTablep();
    for (int i = 0; i < passengersanoP->size; i++) {
        struct SlotofHash2* current = passengersanoP->table[i];
        while (current != NULL) { 
            char ntotal[14];
            sprintf(ntotal, "%.0f", current->value);
            char *answer = strcat(current->key, ";");
            answer = strcat(answer, ntotal);
            insertp(respostaano, "password", answer);
            free(answer);
            current = current->next;
        }
    }
    struct Value* listaano = searchp(respostaano, "password");
    bubbleSort2(listaano);
    ordernatelist(&listaano);
    int max = getLength(listaano);
    if (topN > max) topN=max;
        struct Value* antiseg2 = listaano;
        for (int i = 0; i<topN; i++) {
            if (antiseg2->info != NULL) {
                    printf("%s\n", antiseg2->info);
            }
            antiseg2 = antiseg2->next;
        }
            freeTable(respostaano);
        freeHashTable2(passengersanoC);
}
////////////////////////////
//////////////////////////// QUERY 6F
else if ((strcasecmp(input, "6") == 0) && display) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char yearnN[12];
    printf("Please, choose the year and the \"N\" to check the TopN airports with most passengers for that year: ");
    fgets(yearnN, sizeof(yearnN), stdin);

    // Remove the newline character at the end of the input, if present
    if (yearnN[strlen(yearnN) - 1] == '\n') {
        yearnN[strlen(yearnN) - 1] = '\0';
    }
    int ano;
    int topN;
    separateString(yearnN, &ano, &topN);
    struct HashTable2* passengersanoP = createHashTable2(1000);
    struct HashTable2* passengersanoC = createHashTable2(1000);
    for (int i = 0; i < q1flights->size; i++) {
        struct Flightparse* current = q1flights->table[i];
        while (current != NULL) {
            char *year = strdup(current->schedule_departure_date);
            year = extractYear(year);
            int year1 =  atoi(year);
            free(year);
            if (year1 == ano) {
                 if (searchvalue2(passengersanoP, current->origin) == 0) {
                        insertin2(passengersanoP, current->origin, searchvalue2(npass, current->id));
                    }
                else {
                    int somatorio = searchvalue2(passengersanoP, current->origin) + searchvalue2(npass, current->id);
                    insertin2(passengersanoP, current->origin, somatorio);
                }
                if (searchvalue2(passengersanoC, current->destination) == 0) {
                        insertin2(passengersanoC, current->destination, searchvalue2(npass, current->id));
                    }
                else {
                    int somatorio = searchvalue2(passengersanoC, current->destination) + searchvalue2(npass, current->id);
                    insertin2(passengersanoC, current->destination, somatorio);
                }
            }
            current = current->next;
        }
    }

    for (int i = 0; i < passengersanoC->size; i++) {
        struct SlotofHash2* current = passengersanoC->table[i];
        while (current != NULL) { 
            if (searchvalue2(passengersanoP, current->key) == 0) {
                insertin2(passengersanoP, current->key, current->value);
            }
            else {
                insertin2(passengersanoP, current->key, current->value+searchvalue2(passengersanoP, current->key));
            }
            current = current->next;
        }
    }

    struct Slot** respostaano = createTablep();
    for (int i = 0; i < passengersanoP->size; i++) {
        struct SlotofHash2* current = passengersanoP->table[i];
        while (current != NULL) { 
            char ntotal[14];
            sprintf(ntotal, "%.0f", current->value);
            char *answer = strcat(current->key, ";");
            answer = strcat(answer, ntotal);
            insertp(respostaano, "password", answer);
            free(answer);
            current = current->next;
        }
    }
    struct Value* listaano = searchp(respostaano, "password");
    bubbleSort2(listaano);
    ordernatelist(&listaano);
    int max = getLength(listaano);
    if (topN > max) topN=max;
        struct Value* antiseg2 = listaano;
        for (int i = 0; i<topN; i++) {
            if (antiseg2->info != NULL) {
                char *name;
                char *passengers;
                splitString(antiseg2->info, &name, &passengers);
                printf("--- %d ---\nname: %s\npassengers: %s\n", (i+1), name, passengers);
                free(name);
                free(passengers);
                if (i != (topN-1)) {
                    printf("\n");
                }
                }
                antiseg2 = antiseg2->next;
            }
                freeTable(respostaano);
        freeHashTable2(passengersanoC);
    }
////////////////////////////
//////////////////////////// QUERY 2
else if ((strcasecmp(input, "2") == 0) && !display) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char userntype[40];
    printf("Please, choose the user \"id\" from which you'll be presented with its list of reservations and/or flights: ");
    fgets(userntype, sizeof(userntype), stdin);

    // Remove the newline character at the end of the input, if present
    if (userntype[strlen(userntype) - 1] == '\n') {
        userntype[strlen(userntype) - 1] = '\0';
    }
    if (isSeparated(userntype)) {
    char *iduser;
    char *type;
    separateString2(userntype, &iduser, &type);
    if (strcmp(type, "reservations") == 0) {
    if (searchUserid(q1users, iduser) != NULL) {
    struct Value* lista = searchp(reservids, iduser);
    struct Slot** datas = createTablep();
    while (lista != NULL) {
        if (searchReservparse(q1reserv, lista->info) != NULL) {
        struct Reservparse* reservita = searchReservparse(q1reserv, lista->info);
        char temp[30];
        strcpy(temp, lista->info);
        strcat(temp, ";");
        strcat(temp, reservita->begin_date);
        insertp(datas, iduser, temp);
        }
        lista = lista->next;
    }
    struct Value* listadatas = searchp(datas, iduser);
    bubbleSort(listadatas);
    while (listadatas != NULL) {
        printf("%s\n", listadatas->info);
        listadatas = listadatas->next;
    }
    freeTable(datas);
    }
    }
    else {
    if (searchUserid(q1users, iduser) != NULL) {
    struct Value* lista = searchp(flightsid, iduser);
    struct Slot** datas = createTablep();
    while (lista != NULL) {
        if (searchFlightparse(q1flights, lista->info) != NULL) {
        struct Flightparse* voozito = searchFlightparse(q1flights, lista->info);
        char *copia = strdup(voozito->schedule_departure_date);
        updateDateString(copia);
        char temp2[30];
        strcpy(temp2, lista->info);
        strcat(temp2, ";");
        strcat(temp2, copia);
        insertp(datas, userntype, temp2);
        }
        lista = lista->next;
    }
    struct Value* listadatas = searchp(datas, userntype);
    bubbleSort(listadatas);
    while (listadatas != NULL) {
        printf("%s\n", listadatas->info);
        listadatas = listadatas->next;
    }
    freeTable(datas);
    } 
    }
}
else {
    if (searchUserid(q1users, userntype) != NULL) {
    struct Value* lista = searchp(reservids, userntype);
    struct Slot** datas = createTablep();
    while (lista != NULL) {
        if (searchReservparse(q1reserv, lista->info) != NULL) {
        struct Reservparse* reservita = searchReservparse(q1reserv, lista->info);
        char temp[30];
        strcpy(temp, lista->info);
        strcat(temp, ";");
        strcat(temp, reservita->begin_date);
        insertp(datas, userntype, temp);
        }
        lista = lista->next;
    }
    struct Value* lista1 = searchp(flightsid, userntype);
    while (lista1 != NULL) {
        if (searchFlightparse(q1flights, lista1->info) != NULL) {
        struct Flightparse* voozito = searchFlightparse(q1flights, lista1->info);
        char *copia = strdup(voozito->schedule_departure_date);
        updateDateString(copia);
        char temp2[30];
        strcpy(temp2, lista1->info);
        strcat(temp2, ";");
        strcat(temp2, copia);
        insertp(datas, userntype, temp2);
        }
        lista1 = lista1->next;
    }
    struct Value* listadatas = searchp(datas, userntype);
    bubbleSort(listadatas);
    while (listadatas != NULL) {
        if (startsWithBook(listadatas->info)) {
            addreservations(&listadatas->info);
        }
        else {
            addflights(&listadatas->info);
        }
        printf("%s\n", listadatas->info);
        listadatas = listadatas->next;
    }
    freeTable(datas);
    }
}
}
////////////////////////////
//////////////////////////// QUERY 2F
else if ((strcasecmp(input, "2") == 0) && display) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char userntype[40];
    printf("Please, choose the user \"id\" from which you'll be presented with its list of reservations and/or flights: ");
    fgets(userntype, sizeof(userntype), stdin);

    // Remove the newline character at the end of the input, if present
    if (userntype[strlen(userntype) - 1] == '\n') {
        userntype[strlen(userntype) - 1] = '\0';
    }
    if (isSeparated(userntype)) {
    char *iduser;
    char *type;
    separateString2(userntype, &iduser, &type);
    if (strcmp(type, "reservations") == 0) {
    if (searchUserid(q1users, iduser) != NULL) {
    struct Value* lista = searchp(reservids, iduser);
    struct Slot** datas = createTablep();
    while (lista != NULL) {
        if (searchReservparse(q1reserv, lista->info) != NULL) {
        struct Reservparse* reservita = searchReservparse(q1reserv, lista->info);
        char temp[30];
        strcpy(temp, lista->info);
        strcat(temp, ";");
        strcat(temp, reservita->begin_date);
        insertp(datas, iduser, temp);
        }
        lista = lista->next;
    }
    struct Value* listadatas = searchp(datas, iduser);
    bubbleSort(listadatas);
    int i = 1;
    while (listadatas != NULL) {
        char *id;
        char *date;
        separateString3(listadatas->info, &id, &date);
        printf("--- %d ---\nid: %s\ndate: %s\n", i, id, date);
        if (listadatas->next != NULL) printf("\n");
        i++;
        listadatas = listadatas->next;
        free(id);
        free(date);
    }
    freeTable(datas);
    }
    }
    else {
    if (searchUserid(q1users, iduser) != NULL) {
    struct Value* lista = searchp(flightsid, iduser);
    struct Slot** datas = createTablep();
    while (lista != NULL) {
        if (searchFlightparse(q1flights, lista->info) != NULL) {
        struct Flightparse* voozito = searchFlightparse(q1flights, lista->info);
        char *copia = strdup(voozito->schedule_departure_date);
        updateDateString(copia);
        char temp2[30];
        strcpy(temp2, lista->info);
        strcat(temp2, ";");
        strcat(temp2, copia);
        insertp(datas, userntype, temp2);
        }
        lista = lista->next;
    }
    struct Value* listadatas = searchp(datas, userntype);
    bubbleSort(listadatas);
    int i = 1;
    while (listadatas != NULL) {
        char *id;
        char *date;
        separateString3(listadatas->info, &id, &date);
        printf("--- %d ---\nid: %s\ndate: %s\n", i, id, date);
        if (listadatas->next != NULL) printf("\n");
        i++;
        listadatas = listadatas->next;
        free(id);
        free(date);
    }
    freeTable(datas);
    }
    }
}
else {
    if (searchUserid(q1users, userntype) != NULL) {
    struct Value* lista = searchp(reservids, userntype);
    struct Slot** datas = createTablep();
    while (lista != NULL) {
        if (searchReservparse(q1reserv, lista->info) != NULL) {
        struct Reservparse* reservita = searchReservparse(q1reserv, lista->info);
        char temp[30];
        strcpy(temp, lista->info);
        strcat(temp, ";");
        strcat(temp, reservita->begin_date);
        insertp(datas, userntype, temp);
        }
        lista = lista->next;
    }
    struct Value* lista1 = searchp(flightsid, userntype);
    while (lista1 != NULL) {
        if (searchFlightparse(q1flights, lista1->info) != NULL) {
        struct Flightparse* voozito = searchFlightparse(q1flights, lista1->info);
        char *copia = strdup(voozito->schedule_departure_date);
        updateDateString(copia);
        char temp2[30];
        strcpy(temp2, lista1->info);
        strcat(temp2, ";");
        strcat(temp2, copia);
        insertp(datas, userntype, temp2);
        }
        lista1 = lista1->next;
    }
    struct Value* listadatas = searchp(datas, userntype);
    bubbleSort(listadatas);
    int i = 1;
    while (listadatas != NULL) {
        if (startsWithBook(listadatas->info)) {
            addreservations(&listadatas->info);
        }
        else {
            addflights(&listadatas->info);
        }
        char *id;
        char *date;
        char *type;
        separateString4(listadatas->info, &id, &date, &type);
        printf("--- %d ---\nid: %s\ndate: %s\ntype: %s\n", i, id, date, type);
        if (listadatas->next != NULL) printf("\n");
        i++;
        listadatas = listadatas->next;
        free(id);
        free(date);
        free(type);
    }
    freeTable(datas);
    }
}
}
////////////////////////////
//////////////////////////// QUERY 4

else if ((strcasecmp(input, "4") == 0) && !display) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char hotelid[40];
    printf("Please, choose the hotel \"id\" from which you'll be presented with its list of reservations: ");
    fgets(hotelid, sizeof(hotelid), stdin);

    // Remove the newline character at the end of the input, if present
    if (hotelid[strlen(hotelid) - 1] == '\n') {
        hotelid[strlen(hotelid) - 1] = '\0';
    }
    char *array4[70000];
    if (searchp(reservsfromhotel, hotelid) != NULL) {
        struct Value* keytokey=searchp(reservsfromhotel, hotelid);
        int aloca = 0;
        while (keytokey != NULL) {
            struct Reservparse* reservinha = searchReservparse(q1reserv, keytokey->info);
            char line[150];
            sprintf(line, "%s;%s;%s;%s;%d;%.3f", reservinha->id, reservinha->begin_date, reservinha->end_date, reservinha->user_id,reservinha->rating,reservinha->totalprice);
            array4[aloca] = strdup(line);
            keytokey = keytokey->next;
            aloca++;
        }
        qsortStrings(array4, aloca);
        for (int y=0; y<aloca; y++) {
            printf("%s\n", array4[y]);
            free(array4[y]);
        }
    }
}
////////////////////////////
//////////////////////////// QUERY 4F
else if ((strcasecmp(input, "4") == 0) && display) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char hotelid[40];
    printf("Please, choose the hotel \"id\" from which you'll be presented with its list of reservations: ");
    fgets(hotelid, sizeof(hotelid), stdin);

    // Remove the newline character at the end of the input, if present
    if (hotelid[strlen(hotelid) - 1] == '\n') {
        hotelid[strlen(hotelid) - 1] = '\0';
    }
    char *array4[70000];
    if (searchp(reservsfromhotel, hotelid)) {
        struct Value* keytokey=searchp(reservsfromhotel, hotelid);
        int aloca = 0;
        while (keytokey != NULL) {
            struct Reservparse* reservinha = searchReservparse(q1reserv, keytokey->info);
            char line[150];
            sprintf(line, "%s;%s;%s;%s;%d;%.3f", reservinha->id, reservinha->begin_date, reservinha->end_date, reservinha->user_id,reservinha->rating,reservinha->totalprice);
            array4[aloca] = strdup(line);
            keytokey = keytokey->next;
            aloca++;
        }
        qsortStrings(array4, aloca);
        for (int y=0; y<aloca; y++) {
            char *answer[6];
            splitString6(array4[y], answer);
            printf("--- %d ---\nid: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %s\ntotal_price: %s\n", y+1, answer[0], answer[1], answer[2], answer[3], answer[4], answer[5]);
            free(array4[y]);
            if (y!=aloca-1) printf("\n");
        }
    }
}
////////////////////////////
//////////////////////////// QUERY 5
else if ((strcasecmp(input, "5") == 0) && !display) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char airportbetweendates[65];
    printf("Please, choose the airport of origin and an interval of dates from which you'll be presented with a list of its flights between those dates: ");
    fgets(airportbetweendates, sizeof(airportbetweendates), stdin);

    // Remove the newline character at the end of the input, if present
    if (airportbetweendates[strlen(airportbetweendates) - 1] == '\n') {
        airportbetweendates[strlen(airportbetweendates) - 1] = '\0';
    }
    char *array5[3000];
    char origin[4];
    char grounddate[21];
    char ceilingdate[21];
    sscanf(airportbetweendates, "%s \"%[^\"]\" \"%[^\"]\"", origin, grounddate, ceilingdate);
    if (searchp(flightsoforigin, origin) != NULL) {
        struct Value* flightsid=searchp(flightsoforigin, origin);
        int index=0;
        while (flightsid != NULL) {
            struct Flightparse* voo = searchFlightparse(q1flights, flightsid->info);
            if (isDateInInterval(ceilingdate, voo->schedule_departure_date,grounddate)) {
                char lineanswer[100];
                sprintf(lineanswer, "%s;%s;%s;%s;%s", voo->id,voo->schedule_departure_date,voo->destination,voo->airline,voo->plane_model);
                array5[index] = strdup(lineanswer);
                index++;
            }
            flightsid=flightsid->next;
        }
            qsortStrings5(array5, index);
            for (int h=0;h<index;h++) {
                printf("%s\n", array5[h]);
                free(array5[h]);
            }
    }
}
////////////////////////////
//////////////////////////// QUERY 5F
else if ((strcasecmp(input, "5") == 0) && display) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char airportbetweendates[65];
    printf("Please, choose the airport of origin and an interval of dates from which you'll be presented with a list of its flights between those dates: ");
    fgets(airportbetweendates, sizeof(airportbetweendates), stdin);

    // Remove the newline character at the end of the input, if present
    if (airportbetweendates[strlen(airportbetweendates) - 1] == '\n') {
        airportbetweendates[strlen(airportbetweendates) - 1] = '\0';
    }
    char *array5[3000];
    char origin[4];
    char grounddate[21];
    char ceilingdate[21];
    sscanf(airportbetweendates, "%s \"%[^\"]\" \"%[^\"]\"", origin, grounddate, ceilingdate);
    if (searchp(flightsoforigin, origin) != NULL) {
        struct Value* flightsid=searchp(flightsoforigin, origin);
        int index=0;
        while (flightsid != NULL) {
            struct Flightparse* voo = searchFlightparse(q1flights, flightsid->info);
            if (isDateInInterval(ceilingdate, voo->schedule_departure_date,grounddate)) {
                char lineanswer[100];
                sprintf(lineanswer, "%s;%s;%s;%s;%s", voo->id,voo->schedule_departure_date,voo->destination,voo->airline,voo->plane_model);
                array5[index] = strdup(lineanswer);
                index++;
            }
            flightsid=flightsid->next;
        }
            qsortStrings5(array5, index);
            for (int h=0;h<index;h++) {
                char resultStrings[5][30];
                splitin5(array5[h], resultStrings);
                free(array5[h]);
                printf("--- %d ---\nid: %s\nschedule_departure_date: %s\ndestination: %s\nairline: %s\nplane_model: %s\n",h+1, resultStrings[0], resultStrings[1], resultStrings[2], resultStrings[3], resultStrings[4]);
                if (h!=index-1) printf("\n");
            }
    }
}
////////////////////////////
//////////////////////////// QUERY 8

else if ((strcasecmp(input, "8") == 0) && !display) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char hotelbetweendates[65];
    printf("Please, choose the hotel \"id\" and an interval of dates to consult the revenue of that hotel between those dates: ");
    fgets(hotelbetweendates, sizeof(hotelbetweendates), stdin);

    // Remove the newline character at the end of the input, if present
    if (hotelbetweendates[strlen(hotelbetweendates) - 1] == '\n') {
        hotelbetweendates[strlen(hotelbetweendates) - 1] = '\0';
    }
    char hotelid[9];
    char grounddate[11];
    char ceilingdate[11];
    sscanf(hotelbetweendates, "%s %s %s", hotelid, grounddate, ceilingdate);
    struct Value* keytokey=searchp(reservsfromhotel, hotelid);
    int soma=0;
    while (keytokey!=NULL) {
        struct Reservparse* reserva = searchReservparse(q1reserv, keytokey->info);
        int numofnights1 = countCommonNights(reserva->begin_date, reserva->end_date, grounddate, ceilingdate);
        soma+=(numofnights1*reserva->price_per_night);
        keytokey= keytokey->next;
    }
    printf("%d\n", soma);
}
////////////////////////////
//////////////////////////// QUERY 8F
else if ((strcasecmp(input, "8") == 0) && display) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char hotelbetweendates[65];
    printf("Please, choose the hotel \"id\" and an interval of dates to consult the revenue of that hotel between those dates: ");
    fgets(hotelbetweendates, sizeof(hotelbetweendates), stdin);

    // Remove the newline character at the end of the input, if present
    if (hotelbetweendates[strlen(hotelbetweendates) - 1] == '\n') {
        hotelbetweendates[strlen(hotelbetweendates) - 1] = '\0';
    }
    char hotelid[9];
    char grounddate[11];
    char ceilingdate[11];
    sscanf(hotelbetweendates, "%s %s %s", hotelid, grounddate, ceilingdate);
    struct Value* keytokey=searchp(reservsfromhotel, hotelid);
    int soma=0;
    while (keytokey!=NULL) {
        struct Reservparse* reserva = searchReservparse(q1reserv, keytokey->info);
        int numofnights1 = countCommonNights(reserva->begin_date, reserva->end_date, grounddate, ceilingdate);
        soma+=(numofnights1*reserva->price_per_night);
        keytokey= keytokey->next;
    }
    printf("--- 1 ---\nrevenue: %d\n", soma);
}
////////////////////////////
//////////////////////////// QUERY 9
else if ((strcasecmp(input, "9") == 0) && !display) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char potencialprefix[65];
    printf("Please, choose a potencial prefix in order to list all the users from which that is a prefix of: ");
    fgets(potencialprefix, sizeof(potencialprefix), stdin);

    // Remove the newline character at the end of the input, if present
    if (potencialprefix[strlen(potencialprefix) - 1] == '\n') {
        potencialprefix[strlen(potencialprefix) - 1] = '\0';
    }
    char *array9[10000];
    int index=0;
    if (hasDoubleQuotes(potencialprefix)) removeDoubleQuotes(potencialprefix);
    for (int l=0; l<170000; l++) {
        struct Userparse* user = q1users->table[l];
        while (user!=NULL) {
            if (isPrefix(potencialprefix, user->name)) {
                char holy[100];
                sprintf(holy, "%s;%s", user->id,user->name);
                array9[index] = strdup(holy);
                index++;
            }
            user=user->next;
        }
    }
    qsortStrings9(array9, index);
    for (int er=0; er<index; er++) {
        printf("%s\n", array9[er]);
        free(array9[er]);
    }
}
////////////////////////////
//////////////////////////// QUERY 9F
else if ((strcasecmp(input, "9") == 0) && display) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char potencialprefix[65];
    printf("Please, choose a potencial prefix in order to list all the users from which that is a prefix of: ");
    fgets(potencialprefix, sizeof(potencialprefix), stdin);

    // Remove the newline character at the end of the input, if present
    if (potencialprefix[strlen(potencialprefix) - 1] == '\n') {
        potencialprefix[strlen(potencialprefix) - 1] = '\0';
    }
    char *array9[10000];
    int index=0;
    if (hasDoubleQuotes(potencialprefix)) removeDoubleQuotes(potencialprefix);
    for (int l=0; l<170000; l++) {
        struct Userparse* user = q1users->table[l];
        while (user!=NULL) {
            if (isPrefix(potencialprefix, user->name)) {
                char holy[100];
                sprintf(holy, "%s;%s", user->id,user->name);
                array9[index] = strdup(holy);
                index++;
            }
            user=user->next;
        }
    }
     qsortStrings9(array9, index);
    for (int er=0; er<index; er++) {
        char id[30];
        char nome[40];
        splitStringin2(array9[er], id, nome);
        free(array9[er]);
        printf("--- %d ---\nid: %s\nname: %s\n",er+1, id, nome);
        if (er!=index-1) printf("\n");
    }
}
    while(1) {
    printf("\n     Queries: 1 2 3 4 5 6 7 8 9\nCHOOSE WHICH QUERY YOU'D LIKE TO CONSULT: ");
        scanf("%3s", input);
    if ((strcmp(input, "1") == 0) || (strcmp(input, "2") == 0) ||  (strcmp(input, "3") == 0) ||  (strcmp(input, "4") == 0) ||  (strcmp(input, "5") == 0) ||  (strcmp(input, "6") == 0) ||  (strcmp(input, "7") == 0) ||  (strcmp(input, "8") == 0) ||  (strcmp(input, "9") == 0)) {
        break;
    }
    else printf("Error: Invalid input\n");
    }
    }
destroyHashTable(nreservas);
freeHashReserv(q1reserv);
freeTable(reservids);
freeTable(reservsfromhotel);
freeHashUser(q1users);
freeHashTable2(npass);
freeHashTable2(nvoos);
freeTable(flightsid);
freeHashFlight(q1flights);
freeIntTable(medatrasos);
freeTable(flightsoforigin);
freeHashTable2(invalidflights);
freeHashTable2(invalidusers);
///////////////////////////////  
}
