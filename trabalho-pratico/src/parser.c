#include "parser.h"

void parserreserv (struct HashTable* nreservas,struct HashReserv* reservas, struct Slot** listaids,struct Slot** reservsfromhotel, struct HashTable2* invalidusers, char *datasetspath) {
    int length = strlen(datasetspath) + strlen("/reservations.csv")+2;
    char *dataset1 = malloc((length)*sizeof(char));
    snprintf(dataset1, length, "%s/%s", datasetspath, "/reservations.csv");
    FILE *file = fopen(dataset1, "r");
    if (file == NULL) {
        perror("Error opening file");
    }
    FILE *reserverrors = fopen("Resultados/reservations_errors.csv", "w"); 
    char line1[1024];  // Assuming a maximum line length of 1024 characters
    while (fgets(line1, sizeof(line1), file)) {
        char *line = strdup(line1);
        if (!reservavalida(line, invalidusers)) {
            fprintf(reserverrors, "%s", line1);
        }
        else {
        char *id = strsep(&line, ";");
        char *user_id = strsep(&line, ";");
        char *hotel_id = strsep(&line, ";");
        char *hotel_name = strsep(&line, ";");
        char *hotel_stars = strsep(&line, ";");
        double city_tax = atof(strsep(&line, ";"));
        strsep(&line, ";");
        char *begin_date = strsep(&line, ";");
        char *end_date = strsep(&line, ";");
        double price_per_night = atof(strsep(&line, ";"));
        char *includes_breakfast = strsep(&line, ";");
        strsep(&line, ";");
        double rating = atoi(strsep(&line, ";"));
        strsep(&line, ";");
        double numbernights = calculateNights(begin_date, end_date);
            if (user_id != NULL) {
            if (searchvalue(nreservas, user_id) == -1) {
                insertin(nreservas, user_id, price_per_night*numbernights+((price_per_night*numbernights)/100)*city_tax, 1);
            }
            else{
                double i = searchtimes(nreservas, user_id) + 1;
                double somatorio = searchvalue(nreservas, user_id) + (price_per_night*numbernights)+(((price_per_night*numbernights)/100)*city_tax);
                insertin(nreservas, user_id, somatorio, i);
            }
            if (id != NULL) {
                insertinHashReserv(reservas, id, user_id, hotel_id, hotel_name, hotel_stars, begin_date, end_date, price_per_night, includes_breakfast, rating, numbernights, price_per_night*numbernights+((price_per_night*numbernights)/100)*city_tax);
                insertp(listaids, user_id, id);
                insertp(reservsfromhotel, hotel_id, id);
            }
        }
        free(line);
        free(id);
    }
    }
    fclose(file);
    free(dataset1);
}



void parserusers (struct HashUser* tabela, struct HashTable2* invalidusers, char *datasetspath) {
    int length = strlen(datasetspath) + strlen("/users.csv") +2;
    char *dataset2 = malloc((length)*sizeof(char));
    snprintf(dataset2, length, "%s/%s", datasetspath, "/users.csv");
    FILE *file = fopen(dataset2, "r");
    if (file == NULL) {
        perror("Error opening file");
    }
    FILE *errorsusers = fopen("Resultados/users_errors.csv", "w"); 
    char line1[2024];  // Assuming a maximum line length of 1024 characters
    while (fgets(line1, sizeof(line1), file)) {
        char *line = strdup(line1);
        if (!uservalido(line, invalidusers)) {
            fprintf(errorsusers, "%s", line1);
        }
        else {
        char *id = strsep(&line, ";");
        char *name = strsep(&line, ";");
        strsep(&line, ";");
        strsep(&line, ";");
        char *birthdate = strsep(&line, ";");
        char *sex = strsep(&line, ";");
        char *passport = strsep(&line, ";");
        char *countrycode = strsep(&line, ";");
        strsep(&line, ";");
        strsep(&line, ";");
        strsep(&line, ";");
        char *account_status = strsep(&line, "\n");
        if (strcasecmp(account_status, "inactive") != 0) {
            insertinHashUser(tabela, id, name, birthdate, sex, passport, countrycode, 0, 0, 0);
        }
        free(id);
    }
    }
    free(dataset2);
    fclose(file);
}

void parsepassengers (struct HashTable2* tabela, struct HashTable2* npass, struct Slot** flightsid, struct HashTable2* invalidflights,struct HashTable2* invalidusers, char *datasetspath) {
    int length = strlen(datasetspath) + strlen("/passengers.csv") +2;
    char *dataset3 = malloc((length)*sizeof(char));
    snprintf(dataset3, length, "%s/%s", datasetspath, "/passengers.csv");
    FILE *file = fopen(dataset3, "r");
    if (file == NULL) {
        perror("Error opening file");
    }
    FILE *passengerserrors = fopen("Resultados/passengers_errors.csv", "w"); 
    char line1[2024];  // Assuming a maximum line length of 1024 characters
    while (fgets(line1, sizeof(line1), file)) {
        char *line = strdup(line1);
        if (!passengervalido(line, invalidflights, invalidusers)) {
            fprintf(passengerserrors, "%s", line1);
        }
        else {
        char *flight_id = strsep(&line, ";");
        char *user_id = strsep(&line, "\n");
        if (user_id != NULL) {
            insertp(flightsid, user_id, flight_id);
            if (searchvalue2(tabela, user_id) == 0) {
                insertin2(tabela, user_id, 1);
            }
            else{
                double somatorio = searchvalue2(tabela, user_id) + 1;
                insertin2(tabela, user_id, somatorio);
            }
            }
        if (flight_id != NULL) {
            if (searchvalue2(npass, flight_id) == 0) {
                insertin2(npass, flight_id, 1);
            }
            else{
                int somatorio = searchvalue2(npass, flight_id) + 1;
                insertin2(npass, flight_id, somatorio);
            }
        }
        free(flight_id);
        }
    }
    fclose(file);
    free(dataset3);
}

void parserflight (struct HashFlight* tabela, struct Tabelints** atrasos,struct Slot** flightsoforigin,struct HashTable2* invalidflights, char *datasetspath) {
    int length = strlen(datasetspath) + strlen("/flights.csv") +2;
    char *dataset4 = malloc((length)*sizeof(char));
    snprintf(dataset4, length, "%s/%s", datasetspath, "/flights.csv");
    FILE *file = fopen(dataset4, "r");
    if (file == NULL) {
        perror("Error opening file");
    }
    FILE *flightserrors = fopen("Resultados/flights_errors.csv", "w");
    char line1[2024];  // Assuming a maximum line length of 1024 characters
    while (fgets(line1, sizeof(line1), file)) {
        char *line = strdup(line1);
        if (!voovalido(line, invalidflights)) {
            fprintf(flightserrors, "%s", line1);
        }
        else {
        char *flight_id = strsep(&line, ";");
        char *airline = strsep(&line, ";");
        char *plane_model = strsep(&line, ";");
        strsep(&line, ";");
        char *origin = convertToUpperCase(strsep(&line, ";"));
        char *destination = convertToUpperCase(strsep(&line, ";"));
        char *schedule_departure_date = strsep(&line, ";");
        char *schedule_arrival_date = strsep(&line, ";");
        char *real_departure_date = strsep(&line, ";");
        strsep(&line, ";");
        strsep(&line, ";");
        strsep(&line, ";");
        strsep(&line, ";");
        int delay = calculateDelayInSeconds(schedule_departure_date, real_departure_date);
        if (flight_id != NULL && strcmp(flight_id, "id") != 0) {
            insertinHashFlight(tabela, flight_id, airline, plane_model, origin, destination, schedule_departure_date, schedule_arrival_date, delay);
            insertlint(atrasos, origin, delay);
            insertp(flightsoforigin, origin, flight_id);
        }
        free(line);
        free(flight_id);
    }
    }
    fclose(file);
    free(dataset4);
}