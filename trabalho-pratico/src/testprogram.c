#include "../include/testprogram.h"
#include <sys/resource.h>

void TestProgram (char *datasetspath, char *inputspath, char *outputspath) {
    // Start time for the whole Program CPU usage
    clock_t start1, end1;
    double cpu_time_used = 0;

    // Start time for the whole Program elapsed
    start1 = clock();
    struct timeval start, end;
    double elapsed = 0;

    // Parsing time (with parsing of the inputs)
    double parsing_cpu_time = 0;

    // Queries execute time and number of calls
    double query1_cpu_time = 0;
    int q1calledtimes = 0;
    double query2_cpu_time = 0;
    int q2calledtimes = 0;
    double query3_cpu_time = 0;
    int q3calledtimes = 0;
    double query4_cpu_time = 0;
    int q4calledtimes = 0;
    double query5_cpu_time = 0;
    int q5calledtimes = 0;
    double query6_cpu_time = 0;
    int q6calledtimes = 0;
    double query7_cpu_time = 0;
    int q7calledtimes = 0;
    double query8_cpu_time = 0;
    int q8calledtimes = 0;
    double query9_cpu_time = 0;
    int q9calledtimes = 0;

    // Start time Whole program elapsed
    gettimeofday(&start, NULL);

    // Execute work BatchMode(datasetspath, inputspath);
    clock_t startp, endp;
    startp = clock();
    struct HashUser* q1users = createHashUser(170000);
    struct HashTable2* invalidusers = createHashTable2(600);
    parserusers(q1users, invalidusers, datasetspath);
    printf("user parsing done\n");
    
    struct HashReserv* q1reserv = createHashReserv(1048576);
    struct HashTable* nreservas = createHashTable(1048576);
    struct Slot** reservids = createTablep();
    struct Slot** reservsfromhotel = createTablep();
    parserreserv(nreservas, q1reserv, reservids, reservsfromhotel, invalidusers, datasetspath);
    printf("reservation parsing done\n");

    struct HashFlight* q1flights = createHashFlight(10000);
    struct Tabelints** medatrasos = createTablint();
    struct Slot** flightsoforigin = createTablep(); 
    struct HashTable2* invalidflights = createHashTable2(600);
    parserflight(q1flights, medatrasos,flightsoforigin,invalidflights, datasetspath);
    printf("flight parsing done\n");

    struct HashTable2* nvoos = createHashTable2(170000);
    struct HashTable2* npass = createHashTable2(170000);
    struct Slot** flightsid = createTablep();
    parsepassengers(nvoos, npass, flightsid, invalidflights, invalidusers, datasetspath);
    printf("passenger parsing done\n");

    ParsedData inputs = parseFile(inputspath);
    printf("inputs parsing done\n");
    endp = clock();
    parsing_cpu_time += ((double) (endp - startp)) / CLOCKS_PER_SEC;
    

    clock_t startq7, endq7;
    startq7 = clock();
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

    endq7 = clock();
    query7_cpu_time += ((double) (endq7 - startq7)) / CLOCKS_PER_SEC;
    ////////

    for (int j=0; j<inputs.numQueries; j++) {
///////////////////////////// QUERY 1
if (strcmp(inputs.queries[j].indicator, "1") == 0) {
    q1calledtimes++;
    clock_t startq, endq;
    startq = clock();
    if (startsWithBook(inputs.queries[j].input)) {
        if (searchReservparse(q1reserv, inputs.queries[j].input) != NULL) {
            struct Reservparse* reserva = (searchReservparse(q1reserv, inputs.queries[j].input));
            char linha1[5];
            updatePath(j+1, linha1);
            char path[MAX_STRING_LENGTH];
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            char path1[MAX_STRING_LENGTH];
            sprintf(path1, "%s/command%s_output.txt", outputspath, linha1);
            FILE* reservas = fopen(path, "w");
            char *booli = strdup(reserva->includes_breakfast);
            capitalizeFirstLetter(booli);
            fprintf(reservas, "%s;%s;%s;%s;%s;%s;%.0f;%.3f\n", reserva->hotel_id, reserva->hotel_name, reserva->hotel_stars, reserva->begin_date, reserva->end_date, booli, reserva->numbernights, reserva->totalprice);
            free(booli);
            fclose(reservas);
            if (compareFiles(path, path)) printf("O input nº%s é igual.\n", linha1);
        }
        else {
            char linha1[5];
            updatePath(j+1, linha1);
            char path[MAX_STRING_LENGTH];
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            char path1[MAX_STRING_LENGTH];
            sprintf(path1, "%s/command%s_output.txt", outputspath, linha1);
            FILE *reservas = fopen(path, "w");
            fclose(reservas);
            if (compareFiles(path1, path)) printf("O input nº%s é igual.\n", linha1);
        }
    }

    else if (startsWith0000(inputs.queries[j].input)) {
        if (searchFlightparse(q1flights, inputs.queries[j].input) != NULL) {
            struct Flightparse* teste = searchFlightparse(q1flights, inputs.queries[j].input);
            char linha1[5];
            updatePath(j+1, linha1);
            char path[MAX_STRING_LENGTH];
            char path1[MAX_STRING_LENGTH];
            sprintf(path1, "%s/command%s_output.txt", outputspath, linha1);
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            FILE *voosq1 = fopen(path, "w");
            fprintf(voosq1, "%s;%s;%s;%s;%s;%s;%.0f;%d\n", teste->airline, teste->plane_model, teste->origin, teste->destination, teste->schedule_departure_date, teste->schedule_arrival_date, searchvalue2(npass, teste->id), teste->delay);
            fclose(voosq1);

            if (compareFiles(path1, path)) printf("O input nº%s é igual.\n", linha1);
        }
        else {
            char linha1[5];
            updatePath(j+1, linha1);
            char path[MAX_STRING_LENGTH];
            char path1[MAX_STRING_LENGTH];
            sprintf(path1, "%s/command%s_output.txt", outputspath, linha1);
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            FILE *voosq1 = fopen(path, "w");
            fclose(voosq1);
            if (compareFiles(path1, path)) printf("O input nº%s é igual.\n", linha1);
        }
    }
    else {
        if (searchUserparse(q1users, inputs.queries[j].input) != NULL) {
            struct Userparse* current = searchUserparse(q1users, inputs.queries[j].input);
            char linha1[5];
            updatePath(j+1, linha1);
            char path[MAX_STRING_LENGTH];
            char path1[MAX_STRING_LENGTH];
            sprintf(path1, "%s/command%s_output.txt", outputspath, linha1);
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            FILE* users = fopen(path, "w");
            fprintf(users, "%s;%s;%.0f;%s;%s;%.0f;%.0f;%.3f\n", current->name, current->sex, calculateAge(current->birthdate), current->countrycode, current->passport, searchvalue2(nvoos, current->id), searchtimes(nreservas, current->id), searchvalue(nreservas, current->id));
            fclose(users);
            if (compareFiles(path1, path)) printf("O input nº%s é igual.\n", linha1);
        }
        else {
            char linha1[5];
            updatePath(j+1, linha1);
            char path[MAX_STRING_LENGTH];
            char path1[MAX_STRING_LENGTH];
            sprintf(path1, "%s/command%s_output.txt", outputspath, linha1);
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            FILE *users = fopen(path, "w");
            fclose(users);
            if (compareFiles(path1, path)) printf("O input nº%s é igual.\n", linha1);
        }
    }
    endq = clock();
    query1_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
}
else if (strcmp(inputs.queries[j].indicator, "1F") == 0) {
    q1calledtimes++;
    clock_t startq, endq;
    startq = clock();
    if (startsWithBook(inputs.queries[j].input)) {
        if (searchReservparse(q1reserv, inputs.queries[j].input) != NULL) {
            struct Reservparse* reserva = (searchReservparse(q1reserv, inputs.queries[j].input));
            char linha1[5];
            updatePath(j+1, linha1);
            char path[MAX_STRING_LENGTH];
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            FILE* freservas = fopen(path, "w");
            char *booli = reserva->includes_breakfast;
            capitalizeFirstLetter(booli);
            fprintf(freservas,"--- 1 ---\nhotel_id: %s\nhotel_name: %s\nhotel_stars: %s\nbegin_date: %s\nend_date: %s\nincludes_breakfast: %s\nnights: %.0f\ntotal_price: %.3f\n", reserva->hotel_id, reserva->hotel_name, reserva->hotel_stars, reserva->begin_date, reserva->end_date, booli, reserva->numbernights, reserva->totalprice);
            free(booli);
            fclose(freservas);
        }
        else {
            char linha1[5];
            updatePath(j+1, linha1);
            char path[MAX_STRING_LENGTH];
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            FILE* freservas = fopen(path, "w"); 
            fclose(freservas);   
        } 
    }
    else if (startsWith0000(inputs.queries[j].input)) {
        if (searchFlightparse(q1flights, inputs.queries[j].input) != NULL) {
            struct Flightparse* fteste = searchFlightparse(q1flights, inputs.queries[j].input);
            char linha1[5];
            updatePath(j+1, linha1);
            char path[MAX_STRING_LENGTH];
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            FILE *fvoosq1 = fopen(path, "w");
            fprintf(fvoosq1, "--- 1 ---\nairline: %s\nplane_model: %s\norigin: %s\ndestination: %s\nschedule_departure_date: %s\nschedule_arrival_date: %s\npassengers: %.0f\ndelay: %d\n", fteste->airline, fteste->plane_model, fteste->origin, fteste->destination, fteste->schedule_departure_date, fteste->schedule_arrival_date, searchvalue2(npass, fteste->id), fteste->delay);
            fclose(fvoosq1);
        }
        else {
            char linha1[5];
            updatePath(j+1, linha1);
            char path[MAX_STRING_LENGTH];
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            FILE *fvoosq1 = fopen(path, "w"); 
            fclose(fvoosq1);
        }
    }
    else {
        if (searchUserparse(q1users, inputs.queries[j].input) != NULL) {
            struct Userparse* currentf = searchUserparse(q1users, inputs.queries[j].input);
            char linha1[5];
            updatePath(j+1, linha1);
            char path[MAX_STRING_LENGTH];
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            FILE* fusers = fopen(path, "w");
            fprintf(fusers,"--- 1 ---\nname: %s\nsex: %s\nage: %.0f\ncountry_code: %s\npassport: %s\nnumber_of_flights: %.0f\nnumber_of_reservations: %.0f\ntotal_spent: %.3f\n", currentf->name, currentf->sex, calculateAge(currentf->birthdate), currentf->countrycode, currentf->passport, searchvalue2(nvoos, currentf->id), searchtimes(nreservas, currentf->id), searchvalue(nreservas, currentf->id));
            fclose(fusers);
        }
        else {
            char linha1[5];
            updatePath(j+1, linha1);
            char path[MAX_STRING_LENGTH];
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            FILE *fusers = fopen(path, "w");
            fclose(fusers);
        }
    }
    endq = clock();
    query1_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
}

///////////////////////////////
/////////////////////////////// QUERY 3

else if (strcmp(inputs.queries[j].indicator, "3") == 0) {
    q3calledtimes++;
    clock_t startq, endq;
    startq = clock();
    if (searchp(reservsfromhotel, inputs.queries[j].input) != NULL) {
            struct Value* keytokey=searchp(reservsfromhotel, inputs.queries[j].input);
            char linha1[4];
            updatePath(j+1, linha1);
            char path[36];
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            FILE* medias = fopen(path, "w");
            double sum=0;
            double times=1;
            while (keytokey != NULL) {
                struct Reservparse* temp = searchReservparse(q1reserv, keytokey->info);
                sum+=temp->rating;
                times++;
                keytokey=keytokey->next;
            }
            fprintf(medias, "%.3f\n", sum/times);
            fclose(medias);
        }
        else {
            char linha1[4];
            updatePath(j+1, linha1);
            char path[36];
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            FILE* medias = fopen(path, "w");
            fclose(medias);
        }
    endq = clock();
    query3_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
    }

else if (strcmp(inputs.queries[j].indicator, "3F") == 0) {
    q3calledtimes++;
    clock_t startq, endq;
    startq = clock();
    if (searchp(reservsfromhotel, inputs.queries[j].input) != NULL) {
            struct Value* keytokey=searchp(reservsfromhotel, inputs.queries[j].input);
            char linha1[4];
            updatePath(j+1, linha1);
            char path[36];
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            FILE* fmedias = fopen(path, "w");
            double sum=0;
            double times=1;
            while (keytokey != NULL) {
                struct Reservparse* temp = searchReservparse(q1reserv, keytokey->info);
                sum+=temp->rating;
                times++;
                keytokey=keytokey->next;
            }
            fprintf(fmedias, "--- 1 ---\nrating: %.3f\n", sum/times);
            fclose(fmedias);
            
        }
        else {
            char linha1[4];
            updatePath(j+1, linha1);
            char path[36];
            sprintf(path, "Resultados/command%s_output.txt", linha1);
            FILE* fmedias = fopen(path, "w");
            fclose(fmedias);
        }
    endq = clock();
    query3_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
}
//////////////////////////////
////////////////////////////// QUERY 7
else  if (strcmp(inputs.queries[j].indicator, "7") == 0) {
    q7calledtimes++;
    clock_t startq, endq;
    startq = clock();
        int input7 = atoi(inputs.queries[j].input);
        char linha1[5];
        updatePath(j+1, linha1);
        char path[MAX_STRING_LENGTH];
        sprintf(path, "Resultados/command%s_output.txt", linha1);
        FILE* medianas = fopen(path, "w");
        if (input7 > indice) input7=indice;
        for (int i = 0; i<input7; i++) {
            fprintf(medianas, "%s\n", array7[i]);
        }
        fclose(medianas);
    endq = clock();
    query7_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
    }
    else if (strcmp(inputs.queries[j].indicator, "7F") == 0) {
    q7calledtimes++;
    clock_t startq, endq;
    startq = clock();
        int input7f = atoi(inputs.queries[j].input);
        char linha1[5];
        updatePath(j+1, linha1);
        char path[MAX_STRING_LENGTH];
        sprintf(path, "Resultados/command%s_output.txt", linha1);
        FILE* medianas = fopen(path, "w");
        if (input7f > indice) input7f=indice;
        for (int i = 0; i<input7f; i++) {
                char *name;
                char *med;
                splitString(array7[i], &name, &med);
                fprintf(medianas, "--- %d ---\nname: %s\nmedian: %s\n", (i+1), name, med);
                if (i != (input7f-1)) {
                    fprintf(medianas, "\n");
                }
                free(name);
                free(med);
        }
        fclose(medianas);
    endq = clock();
    query7_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
    }
/////////////////////////////
///////////////////////////// QUERY 6
else if (strcmp(inputs.queries[j].indicator, "6") == 0) {
    q6calledtimes++;
    clock_t startq, endq;
    startq = clock();

    int ano;
    int topN;
    separateString(inputs.queries[j].input, &ano, &topN);
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
    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* q6 = fopen(path, "w");
    int max = getLength(listaano);
    if (topN > max) topN=max;
        struct Value* antiseg2 = listaano;
        for (int i = 0; i<topN; i++) {
            if (antiseg2->info != NULL) {
                    fprintf(q6, "%s\n", antiseg2->info);
            }
            antiseg2 = antiseg2->next;
        }
    freeTable(respostaano);
    freeHashTable2(passengersanoC); 
    endq = clock();
    query6_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
}
else if (strcmp(inputs.queries[j].indicator, "6F") == 0) {
    q6calledtimes++;
    clock_t startq, endq;
    startq = clock();

    int ano;
    int topN;
    separateString(inputs.queries[j].input, &ano, &topN);
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
    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* q6 = fopen(path, "w");
    int max = getLength(listaano);
    if (topN > max) topN=max;
        struct Value* antiseg2 = listaano;
        for (int i = 0; i<topN; i++) {
            if (antiseg2->info != NULL) {
                char *name;
                char *passengers;
                splitString(antiseg2->info, &name, &passengers);
                fprintf(q6, "--- %d ---\nname: %s\npassengers: %s\n", (i+1), name, passengers);
                free(name);
                free(passengers);
                if (i != (topN-1)) {
                    fprintf(q6, "\n");
                }
                }
                antiseg2 = antiseg2->next;
            }
    freeTable(respostaano);
    freeHashTable2(passengersanoC); 
    endq = clock();
    query6_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
    }
////////////////////////////
//////////////////////////// QUERY 2
else if (strcmp(inputs.queries[j].indicator, "2") == 0) {
    q2calledtimes++;
    clock_t startq, endq;
    startq = clock();

    if (isSeparated(inputs.queries[j].input)) {
    char *iduser;
    char *type;
    separateString2(inputs.queries[j].input, &iduser, &type);
    if (strcmp(type, "reservations") == 0) {
    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* ordem = fopen(path, "w");
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
        fprintf(ordem, "%s\n", listadatas->info);
        listadatas = listadatas->next;
    }
    freeTable(datas);
    char path1[MAX_STRING_LENGTH];
    sprintf(path1, "%s/command%s_output.txt", outputspath, linha1);
    if (compareFiles(path, path)) printf("O input nº%s é igual.\n", linha1);
    }
    fclose(ordem);
    }
    else {
    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* ordem = fopen(path, "w");
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
        insertp(datas, inputs.queries[j].input, temp2);
        free(copia);
        }
        lista = lista->next;
    }
    struct Value* listadatas = searchp(datas, inputs.queries[j].input);
    bubbleSort(listadatas);
    while (listadatas != NULL) {
        fprintf(ordem, "%s\n", listadatas->info);
        listadatas = listadatas->next;
    }
    freeTable(datas);
    }
    fclose(ordem); 
    char path1[MAX_STRING_LENGTH];
    sprintf(path1, "%s/command%s_output.txt", outputspath, linha1);
    if (compareFiles(path, path)) printf("O input nº%s é igual.\n", linha1);    
    }
    free(iduser);
    free(type);
}
else {
    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* ordem = fopen(path, "w");
    if (searchUserid(q1users, inputs.queries[j].input) != NULL) {
    struct Value* lista = searchp(reservids, inputs.queries[j].input);
    struct Slot** datas = createTablep();
    while (lista != NULL) {
        if (searchReservparse(q1reserv, lista->info) != NULL) {
        struct Reservparse* reservita = searchReservparse(q1reserv, lista->info);
        char temp[30];
        strcpy(temp, lista->info);
        strcat(temp, ";");
        strcat(temp, reservita->begin_date);
        insertp(datas, inputs.queries[j].input, temp);
        }
        lista = lista->next;
    }
    struct Value* lista1 = searchp(flightsid, inputs.queries[j].input);
    while (lista1 != NULL) {
        if (searchFlightparse(q1flights, lista1->info) != NULL) {
        struct Flightparse* voozito = searchFlightparse(q1flights, lista1->info);
        char *copia = strdup(voozito->schedule_departure_date);
        updateDateString(copia);
        char temp2[30];
        strcpy(temp2, lista1->info);
        strcat(temp2, ";");
        strcat(temp2, copia);
        insertp(datas, inputs.queries[j].input, temp2);
        free(copia);
        }
        lista1 = lista1->next;
    }
    struct Value* listadatas = searchp(datas, inputs.queries[j].input);
    bubbleSort(listadatas);
    while (listadatas != NULL) {
        if (startsWithBook(listadatas->info)) {
            addreservations(&listadatas->info);
        }
        else {
            addflights(&listadatas->info);
        }
        fprintf(ordem, "%s\n", listadatas->info);
        listadatas = listadatas->next;
    }
    freeTable(datas);
    char path1[MAX_STRING_LENGTH];
    sprintf(path1, "%s/command%s_output.txt", outputspath, linha1);
    if (compareFiles(path, path)) printf("O input nº%s é igual.\n", linha1);
    }
    fclose(ordem);
}
    endq = clock();
    query2_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
}
else if (strcmp(inputs.queries[j].indicator, "2F") == 0) {
    q2calledtimes++;
    clock_t startq, endq;
    startq = clock();

    if (isSeparated(inputs.queries[j].input)) {
    char *iduser;
    char *type;
    separateString2(inputs.queries[j].input, &iduser, &type);
    if (strcmp(type, "reservations") == 0) {
    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* ordem = fopen(path, "w");
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
        fprintf(ordem, "--- %d ---\nid: %s\ndate: %s\n", i, id, date);
        if (listadatas->next != NULL) fprintf(ordem, "\n");
        i++;
        listadatas = listadatas->next;
        free(id);
        free(date);
    }
    freeTable(datas);
    }
    fclose(ordem);
    }
    else {
    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* ordem = fopen(path, "w");
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
        insertp(datas, inputs.queries[j].input, temp2);
        free(copia);
        }
        lista = lista->next;
    }
    struct Value* listadatas = searchp(datas, inputs.queries[j].input);
    bubbleSort(listadatas);
    int i = 1;
    while (listadatas != NULL) {
        char *id;
        char *date;
        separateString3(listadatas->info, &id, &date);
        fprintf(ordem, "--- %d ---\nid: %s\ndate: %s\n", i, id, date);
        if (listadatas->next != NULL) fprintf(ordem, "\n");
        i++;
        listadatas = listadatas->next;
        free(id);
        free(date);
    }
    freeTable(datas);
    }
    fclose(ordem); 
    }
    free(iduser);
    free(type);
}
else {
    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* ordem11 = fopen(path, "w");
    if (searchUserid(q1users, inputs.queries[j].input) != NULL) {
    struct Value* lista = searchp(reservids, inputs.queries[j].input);
    struct Slot** datas = createTablep();
    while (lista != NULL) {
        if (searchReservparse(q1reserv, lista->info) != NULL) {
        struct Reservparse* reservita = searchReservparse(q1reserv, lista->info);
        char temp[30];
        strcpy(temp, lista->info);
        strcat(temp, ";");
        strcat(temp, reservita->begin_date);
        insertp(datas, inputs.queries[j].input, temp);
        }
        lista = lista->next;
    }
    struct Value* lista1 = searchp(flightsid, inputs.queries[j].input);
    while (lista1 != NULL) {
        if (searchFlightparse(q1flights, lista1->info) != NULL) {
        struct Flightparse* voozito = searchFlightparse(q1flights, lista1->info);
        char *copia = strdup(voozito->schedule_departure_date);
        updateDateString(copia);
        char temp2[30];
        strcpy(temp2, lista1->info);
        strcat(temp2, ";");
        strcat(temp2, copia);
        insertp(datas, inputs.queries[j].input, temp2);
        }
        lista1 = lista1->next;
    }
    struct Value* listadatas = searchp(datas, inputs.queries[j].input);
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
        fprintf(ordem11, "--- %d ---\nid: %s\ndate: %s\ntype: %s\n", i, id, date, type);
        if (listadatas->next != NULL) fprintf(ordem11, "\n");
        i++;
        listadatas = listadatas->next;
        free(id);
        free(date);
        free(type);
    }
    freeTable(datas);
    }
    fclose(ordem11);
}
    endq = clock();
    query2_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
}
else if (strcmp(inputs.queries[j].indicator, "4") == 0) {
    q4calledtimes++;
    clock_t startq, endq;
    startq = clock();

    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* bookings = fopen(path, "w");
    char *array4[70000];
    if (searchp(reservsfromhotel, inputs.queries[j].input) != NULL) {
        struct Value* keytokey=searchp(reservsfromhotel, inputs.queries[j].input);
        int aloca = 0;
        while (keytokey != NULL) {
            if (searchReservparse(q1reserv, keytokey->info)!= NULL) {
            struct Reservparse* reservinha = searchReservparse(q1reserv, keytokey->info);
            char line[150];
            sprintf(line, "%s;%s;%s;%s;%d;%.3f", reservinha->id, reservinha->begin_date, reservinha->end_date, reservinha->user_id,reservinha->rating,reservinha->totalprice);
            array4[aloca] = strdup(line);
            keytokey = keytokey->next;
            aloca++;
            }
        }
        qsortStrings(array4, aloca);
        for (int y=0; y<aloca; y++) {
            fprintf(bookings,"%s\n", array4[y]);
            free(array4[y]);
            }
        fclose(bookings);
    }
    endq = clock();
    query4_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
}
else if (strcmp(inputs.queries[j].indicator, "4F") == 0) {
    q4calledtimes++;
    clock_t startq, endq;
    startq = clock();

    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* bookings = fopen(path, "w");
    char *array4[65000];
    if (searchp(reservsfromhotel, inputs.queries[j].input) != NULL) {
        struct Value* keytokey=searchp(reservsfromhotel, inputs.queries[j].input);
        int aloca = 0;
        while (keytokey != NULL) {
            if (searchReservparse(q1reserv, keytokey->info)!= NULL) {
            struct Reservparse* reservinha = searchReservparse(q1reserv, keytokey->info);
            char line[150];
            sprintf(line, "%s;%s;%s;%s;%d;%.3f", reservinha->id, reservinha->begin_date, reservinha->end_date, reservinha->user_id,reservinha->rating,reservinha->totalprice);
            array4[aloca] = strdup(line);
            keytokey = keytokey->next;
            aloca++;
            }
        }
        qsortStrings(array4, aloca);
        for (int y=0; y<aloca; y++) {
            char *answer[6];
            splitString6(array4[y], answer);
            fprintf(bookings,"--- %d ---\nid: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %s\ntotal_price: %s\n", y+1, answer[0], answer[1], answer[2], answer[3], answer[4], answer[5]);
            free(array4[y]);
            if (y!=aloca-1) fprintf(bookings, "\n");
        }
        fclose(bookings);
    }
    endq = clock();
    query4_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
}
else if (strcmp(inputs.queries[j].indicator, "5") == 0) {
    q5calledtimes++;
    clock_t startq, endq;
    startq = clock();
    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* q5 = fopen(path, "w");
    char *array5[3000];
    char origin[4];
    char grounddate[21];
    char ceilingdate[21];
    sscanf(inputs.queries[j].input, "%s \"%[^\"]\" \"%[^\"]\"", origin, grounddate, ceilingdate);
    if (searchp(flightsoforigin, origin) != NULL) {
        struct Value* flightsid=searchp(flightsoforigin, origin);
        int index=0;
        while (flightsid!= NULL) {
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
                fprintf(q5, "%s\n", array5[h]);
                free(array5[h]);
            }
    endq = clock();
    query5_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
    }
}
else if (strcmp(inputs.queries[j].indicator, "5F") == 0) {
    q5calledtimes++;
    clock_t startq, endq;
    startq = clock();

    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* q5 = fopen(path, "w");
    char *array5[3000];
    char origin[4];
    char grounddate[21];
    char ceilingdate[21];
    sscanf(inputs.queries[j].input, "%s \"%[^\"]\" \"%[^\"]\"", origin, grounddate, ceilingdate);
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
                fprintf(q5, "--- %d ---\nid: %s\nschedule_departure_date: %s\ndestination: %s\nairline: %s\nplane_model: %s\n",h+1, resultStrings[0], resultStrings[1], resultStrings[2], resultStrings[3], resultStrings[4]);
                if (h!=index-1) fprintf(q5,"\n");
            }
    endq = clock();
    query5_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
    }
}
else if (strcmp(inputs.queries[j].indicator, "8") == 0) {
    q8calledtimes++;
    clock_t startq, endq;
    startq = clock();

    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* q8 = fopen(path, "w");
    char hotelid[9];
    char grounddate[11];
    char ceilingdate[11];
    sscanf(inputs.queries[j].input, "%s %s %s", hotelid, grounddate, ceilingdate);
    struct Value* keytokey=searchp(reservsfromhotel, hotelid);
    int soma=0;
    while (keytokey!=NULL) {
        struct Reservparse* reserva = searchReservparse(q1reserv, keytokey->info);
        int numofnights1 = countCommonNights(reserva->begin_date, reserva->end_date, grounddate, ceilingdate);
        soma+=(numofnights1*reserva->price_per_night);
        keytokey= keytokey->next;
    }
    fprintf(q8, "%d\n", soma);
    endq = clock();
    query8_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
}
else if (strcmp(inputs.queries[j].indicator, "8F") == 0) {
    q8calledtimes++;
    clock_t startq, endq;
    startq = clock();

    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* q8 = fopen(path, "w");
    char hotelid[9];
    char grounddate[11];
    char ceilingdate[11];
    sscanf(inputs.queries[j].input, "%s %s %s", hotelid, grounddate, ceilingdate);
    struct Value* keytokey=searchp(reservsfromhotel, hotelid);
    int soma=0;
    while (keytokey!=NULL) {
        struct Reservparse* reserva = searchReservparse(q1reserv, keytokey->info);
        int numofnights1 = countCommonNights(reserva->begin_date, reserva->end_date, grounddate, ceilingdate);
        soma+=(numofnights1*reserva->price_per_night);
        keytokey= keytokey->next;
    }
    fprintf(q8, "--- 1 ---\nrevenue: %d\n", soma);
    endq = clock();
    query8_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
}
else if (strcmp(inputs.queries[j].indicator, "9") == 0) {
    q9calledtimes++;
    clock_t startq, endq;
    startq = clock();
    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* q9 = fopen(path, "w");
    char *array9[10000];
    int index=0;
    if (hasDoubleQuotes(inputs.queries[j].input)) removeDoubleQuotes(inputs.queries[j].input);
    for (int l=0; l<170000; l++) {
        struct Userparse* user = q1users->table[l];
        while (user!=NULL) {
            if (isPrefix(inputs.queries[j].input, user->name)) {
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
        fprintf(q9, "%s\n", array9[er]);
        free(array9[er]);
    }
    endq = clock();
    query9_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
}
else if (strcmp(inputs.queries[j].indicator, "9F") == 0) {
    clock_t startq, endq;
    startq = clock();
    char linha1[5];
    updatePath(j+1, linha1);
    char path[MAX_STRING_LENGTH];
    sprintf(path, "Resultados/command%s_output.txt", linha1);
    FILE* q9 = fopen(path, "w");
    char *array9[10000];
    int index=0;
    if (hasDoubleQuotes(inputs.queries[j].input)) removeDoubleQuotes(inputs.queries[j].input);
    for (int l=0; l<170000; l++) {
        struct Userparse* user = q1users->table[l];
        while (user!=NULL) {
            if (isPrefix(inputs.queries[j].input, user->name)) {
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
        fprintf(q9, "--- %d ---\nid: %s\nname: %s\n",er+1, id, nome);
        free(array9[er]);
        if (er!=index-1) fprintf(q9,"\n");
    }
    endq = clock();
    query9_cpu_time += ((double) (endq - startq)) / CLOCKS_PER_SEC;
}
}
freeParsedData(&inputs);
destroyHashTable(nreservas);
freeHashReserv(q1reserv);
freeTable(reservids);
freeTable(reservsfromhotel);
freeHashTable2(invalidusers);
freeHashTable2(invalidflights);
freeHashUser(q1users);
freeHashTable2(npass);
freeHashTable2(nvoos);
freeTable(flightsid);
freeHashFlight(q1flights);
freeIntTable(medatrasos);
freeTable(flightsoforigin);
///////////////////////////////
        // Memory used by the whole program
        struct rusage r_usage;
        getrusage(RUSAGE_SELF, &r_usage);
        printf("\n                     Memory usage of the program: %ld KB\n", r_usage.ru_maxrss);

    // End time
    gettimeofday(&end, NULL);

    // Elapsed time
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    int result = 9;

    printf("\n              Elapsed time of the whole program: %.3f seconds\n                            Executed: %d queries.\n\n", elapsed, result);
        // End time
    end1 = clock();

    // Elapsed CPU time
    cpu_time_used = ((double) (end1 - start1)) / CLOCKS_PER_SEC;

    // Print the CPU time and the variable value
    printf("             CPU time used threw the whole program: %.3f seconds\n\n", cpu_time_used);
    printf("CPU time used parsing all the information into the data structures : %.4f seconds\n", parsing_cpu_time);
    printf("CPU time used executing Query 1 multiple times : %.4f seconds. Called %d times.\n", query1_cpu_time, q1calledtimes);
    printf("CPU time used executing Query 2 multiple times : %.4f seconds.Called %d times.\n", query2_cpu_time, q2calledtimes);
    printf("CPU time used executing Query 3 multiple times : %.4f seconds. Called %d times.\n", query3_cpu_time, q3calledtimes);
    printf("CPU time used executing Query 4 multiple times : %.4f seconds. Called %d times.\n", query4_cpu_time, q4calledtimes);
    printf("CPU time used executing Query 5 multiple times : %.4f seconds. Called %d times.\n", query5_cpu_time, q5calledtimes);
    printf("CPU time used executing Query 6 multiple times : %.4f seconds. Called %d times.\n", query6_cpu_time, q6calledtimes);
    printf("CPU time used executing Query 7 multiple times : %.4f seconds. Called %d times.\n", query7_cpu_time, q7calledtimes);
    printf("CPU time used executing Query 8 multiple times : %.4f seconds. Called %d times.\n", query8_cpu_time, q8calledtimes);
    printf("CPU time used executing Query 9 multiple times : %.4f seconds. Called %d times.\n", query9_cpu_time, q9calledtimes);

}