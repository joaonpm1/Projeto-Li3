#include "../include/validation.h"

int data_valida(char *data) // verificado
{
    int ano, mes, dia;
    if (sscanf(data, "%4d/%2d/%2d", &ano, &mes, &dia) == 3)
    {
        if (ano >= 1900 && ano <= 9999 && dia <= 31 && dia >= 1 && mes >= 1 && mes <= 12)
            return 1;
    }
    return 0;
}

int data_hora_valida(char *data) // verificado
{
    int ano, mes, dia, horas, minutos, segundos;
    if (sscanf(data, "%4d/%2d/%2d %2d:%2d:%2d", &ano, &mes, &dia, &horas, &minutos, &segundos) == 6)
    {
        int cont = 0;
        if (dia <= 31 && dia >= 1 && mes >= 1 && mes <= 12)
            cont++;
        if (horas <= 23 && horas >= 0 && minutos >= 0 && minutos <= 59 && segundos >= 0 && segundos <= 59)
            cont++;
        if (cont == 2)
            return 1;
    }
    return 0;
}

// Para Horas de inicio e Horas de chegada,etc... ----------
int ordem_datas_horas(char *data1, char *data2) // verificado
{
    int ano, mes, dia, horas, minutos, segundos;
    int ano1, mes1, dia1, horas1, minutos1, segundos1;
    if ((sscanf(data1, "%4d/%2d/%2d %2d:%2d:%2d", &ano, &mes, &dia, &horas, &minutos, &segundos) == 6) && (sscanf(data2, "%4d/%2d/%2d %2d:%2d:%2d", &ano1, &mes1, &dia1, &horas1, &minutos1, &segundos1) == 6))
    {
        if (ano < ano1)
            return 1;
        else if ((ano == ano1) && mes < mes1)
            return 1;
        else if ((ano == ano1) && (mes == mes1) && dia < dia1)
            return 1;
        else if (ano == ano1 && mes == mes1 && dia == dia1 && horas < horas1)
            return 1;
        else if (ano == ano1 && mes == mes1 && dia == dia1 && horas == horas1 && minutos < minutos1)
            return 1;
        else if (ano == ano1 && mes == mes1 && dia == dia1 && horas == horas1 && minutos == minutos1 && segundos < segundos1)
            return 1;
    }
    return 0;
}

int ordem_datas_horas_2(char *data1, char *data2) // verificado
{
    int ano, mes, dia;
    int ano1, mes1, dia1;
    if ((sscanf(data1, "%4d/%2d/%2d", &ano, &mes, &dia) == 3) && (sscanf(data2, "%4d/%2d/%2d", &ano1, &mes1, &dia1) == 3))
    {
        if (ano < ano1)
            return 1;
        else if ((ano == ano1) && mes < mes1)
            return 1;
        else if ((ano == ano1) && (mes == mes1) && dia < dia1)
            return 1;
    }
    return 0;
}

int ordem_datas_horas_3(char *data1, char *data2) // verificado
{
    int ano, mes, dia;
    int ano1, mes1, dia1, horas1, minutos1, segundos1;
    if ((sscanf(data1, "%4d/%2d/%2d", &ano, &mes, &dia) == 3) && (sscanf(data2, "%4d/%2d/%2d %2d:%2d:%2d", &ano1, &mes1, &dia1, &horas1, &minutos1, &segundos1) == 6))
    {
        if (ano < ano1)
            return 1;
        else if ((ano == ano1) && mes < mes1)
            return 1;
        else if ((ano == ano1) && (mes == mes1) && dia < dia1)
            return 1;
        else if (ano == ano1 && mes == mes1 && dia == dia1)
            return 1;
    }
    return 0;
}

int verifica_email(char *email) // verificado
{
    char username[100], domain[50], tld[20];
    if ((sscanf(email, "%99[^@]@%49[^.].%19s", username, domain, tld) == 3))
    {
        if (strlen(username) >= 1)
            return 1;
        if (strlen(domain) >= 1)
            return 1;
        if (strlen(tld) >= 2)
            return 1;
    }
    return 0;
}

int verifa_countrycode(char *country_code) // verificado
{
    if (strlen(country_code) == 2)
        return 1;
    return 0;
}

int account_status(char *account_status) // verificado
{
    if (strcasecmp(account_status, "active\n") == 0)
        return 1;
    else if (strcasecmp(account_status, "inactive\n") == 0)
        return 1;
    else if (strcasecmp(account_status, "inactive") == 0)
        return 1;
    else if (strcasecmp(account_status, "active") == 0)
        return 1;
    return 0;
}

int bancos_suficientes(char *total_seats, int passengers) // verificado
{
    int bancos = atoi(total_seats);
    if (bancos >= passengers)
        return 1;
    return 0;
}

int aeroportos(char *aeroportosaida, char *aeroportochegada) // verificado
{
    if (strlen(aeroportosaida) == 3 && strlen(aeroportochegada) == 3)
    {
        if (strcasecmp(aeroportosaida, aeroportochegada) == 0)
            return 0;
        else
            return 1;
    }
    return 0;
}

int estrelas_hotel(char *hotel_stars) // verificado
{
    float estrelas = strtof(hotel_stars, NULL);
    if (estrelas - 5 == 0 || estrelas - 4 == 0 || estrelas - 3 == 0 || estrelas - 2 == 0 || estrelas - 1 == 0)
        return 1;
    return 0;
}

int rating_reserva(char *rating) // verificado
{
    if (strcmp(rating, "") == 0)
        return 1; // confirmar aqui
    float ratingres = strtof(rating, NULL);
    if (ratingres - 5 == 0 || ratingres - 4 == 0 || ratingres - 3 == 0 || ratingres - 2 == 0 || ratingres - 1 == 0)
        return 1;
    return 0;
}

int city_tax(char *city_tax) // verificado
{
    double taxa = strtod(city_tax, NULL);
    if (taxa >= 0)
    {
        double intPart;
        double fracPart = modf(taxa, &intPart);
        if (fracPart == 0)
            return 1;
        else
            return 0;
    }
    return 0;
}

int preco_noite(char *price_per_night) // verificado
{
    double preco = strtod(price_per_night, NULL);
    if (preco > 0)
    {
        double intPart;
        double fracPart = modf(preco, &intPart);
        if (fracPart == 0)
            return 1;
        else
            return 0;
    }
    return 0;
}

int pequeno_almoco(char *includes_breakfast) // verificado
{
    if ((strcasecmp(includes_breakfast, "f") == 0) || (strcasecmp(includes_breakfast, "false") == 0) || (strcmp(includes_breakfast, "0") == 0) || (strcmp(includes_breakfast, "") == 0))
        return 1;
    if ((strcasecmp(includes_breakfast, "t") == 0) || (strcasecmp(includes_breakfast, "true") == 0) || (strcmp(includes_breakfast, "1") == 0))
        return 1;
    return 0;
}

int isNumeric(char *str)
{
    while (*str)
    {
        if (!isdigit(*str))
        {
            return 0; // Caractere não é um número
        }
        str++;
    }
    return 1; // A string é composta apenas por números
}

/*
• Os seguintes restantes campos têm que ter tamanho superior a zero:
– Utilizador: id, name, phone_number, sex, passport, address, pay_method;
– Voo: id, airline, plane_model, pilot, copilot;
– Reserva: id, user_id, hotel_id, hotel_name, address.
*/

int min_size(char *param) // verificado
{
    if (param == NULL)
        return 0;
    int tamanho = strlen(param);
    if (tamanho > 0)
        return 1;
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
--------------------------------------------------------USER---------------------------------------------------------
id;name;email;phone_number;birth_date;sex;passport;country_code;address;account_creation;pay_method;account_status
---------------------------------------------------------------------------------------------------------------------
AlícSá-Mendes ; Alícia Sá-Mendes ; alícsá-mendes@li3.pt ; (351) 259 545 254 ; 1979/11/27 ; F ; CA279133 ; PT ; Avenida Gabriela Guerreiro,42518-827 Rio Maior ; 2016/09/10 17:34:41 ; debit_card ; active
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

// id0;airline1;plane_model2;total_seats3;origin4;destination5;schedule_departure_date6;schedule_arrival_date7;real_departure_date8;real_arrival_date9;pilot10;copilot11;notes12
int voovalido(char *informacao, struct HashTable2* invalidflights)
{
    char *id;
    char *airline;
    char *plane_model;
    char *total_seats;
    char *origin;
    char *destination;
    char *schedule_departure_date;
    char *schedule_arrival_date;
    char *real_departure_date;
    char *real_arrival_date;
    char *pilot;
    char *copilot;

    char *linhada = strdup(informacao);

    char *token = strsep(&linhada, ";");
    if (token != NULL)
        id = token;
    else
        id = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        airline = strdup(token);
    else
        airline = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        plane_model = strdup(token);
    else
        plane_model = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        total_seats = strdup(token);
    else
        total_seats = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        origin = strdup(token);
    else
        origin = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        destination = strdup(token);
    else
        destination = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        schedule_departure_date = strdup(token);
    else
        schedule_departure_date = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        schedule_arrival_date = strdup(token);
    else
        schedule_arrival_date = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        real_departure_date = strdup(token);
    else
        real_departure_date = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        real_arrival_date = strdup(token);
    else
        real_arrival_date = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        pilot = strdup(token);
    else
        pilot = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        copilot = strdup(token);
    else
        copilot = strdup("");

    int check = 1;
    if (data_hora_valida(schedule_departure_date) == 0)
        check = 0; // verificar as schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date
    if (data_hora_valida(schedule_arrival_date) == 0)
        check = 0;
    if (data_hora_valida(real_departure_date) == 0)
        check = 0;
    if (data_hora_valida(real_arrival_date) == 0)
        check = 0;
    if (ordem_datas_horas(schedule_departure_date, schedule_arrival_date) == 0)
        check = 0; // verificar a ordem das datas schedule_departure_date e schedule_arrival_date
    if (ordem_datas_horas(real_departure_date, real_arrival_date) == 0)
        check = 0; // verificar a ordem das datas real_departure_date e real_arrival_date
    if (aeroportos(origin, destination) == 0)
        check = 0; // verificar aeroportos
    if (min_size(id) == 0)
        check = 0; // verificar tamanho minimo de id, airline, plane_model, pilot, copilot;
    if (min_size(airline) == 0)
        check = 0;
    if (min_size(plane_model) == 0)
        check = 0;
    if (min_size(pilot) == 0)
        check = 0;
    if (min_size(copilot) == 0)
        check = 0;
    if (isNumeric(total_seats) == 0)
        check = 0;
    if (check == 0) {
        insertin2(invalidflights, id, 1);
    }
    free(id);
    free(airline);
    free(plane_model);
    free(total_seats);
    free(origin);
    free(destination);
    free(schedule_departure_date);
    free(schedule_arrival_date);
    free(real_departure_date);
    free(real_arrival_date);
    free(pilot);
    free(copilot);

    return check;
}

int passengervalido(char *informacao, struct HashTable2* invalidflights, struct HashTable2* invalidusers)
{
    char *id;
    char *user_id;

    char *linhada = strdup(informacao);

    char *token = strsep(&linhada, ";");
    if (token != NULL)
        id = token;
    else
        id = strdup("");
    token = strsep(&linhada, "\n");
    if (token != NULL)
        user_id = strdup(token);
    else
        user_id = strdup("");

    int check = 1;
    if (min_size(id) == 0)
        check = 0; // verificar tamanho minimo de id
    if (min_size(user_id) == 0)
        check = 0;   
    if (searchvalue2(invalidflights, id) || searchvalue2(invalidusers, user_id) || strcmp(id, "flight_id") == 0) {
        check = 0;
    }
    free(id);
    free(user_id);

    return check;
}

// id0;name1;email2;phone_number3;birth_date4;sex5;passport6;country_code7;address8;account_creation9;pay_method10;account_status11
int uservalido(char *informacao, struct HashTable2* invalidusers)
{
    char *id;
    char *name;
    char *email;
    char *phone_number;
    char *birth_date;
    char *sex;
    char *passport;
    char *country_code;
    char *address;
    char *account_creation;
    char *pay_method;
    char *account_statutus;

    char *linhada = strdup(informacao);

    char *token = strsep(&linhada, ";");
    if (token != NULL)
        id = strdup(token);
    else
        id = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        name = strdup(token);
    else
        name = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        email = strdup(token);
    else
        email = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        phone_number = strdup(token);
    else
        phone_number = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        birth_date = strdup(token);
    else
        birth_date = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        sex = strdup(token);
    else
        sex = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        passport = strdup(token);
    else
        passport = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        country_code = strdup(token);
    else
        country_code = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        address = strdup(token);
    else
        address = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        account_creation = strdup(token);
    else
        account_creation = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        pay_method = strdup(token);
    else
        pay_method = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        account_statutus = strdup(token);
    else
        account_statutus = strdup("");

    int check = 1;

    if (data_valida(birth_date) == 0)
        check = 0;
    if (data_hora_valida(account_creation) == 0)
        check = 0;
    if (ordem_datas_horas_3(birth_date, account_creation) == 0)
        check = 0;
    if (verifica_email(email) == 0)
        check = 0;
    if (verifa_countrycode(country_code) == 0)
        check = 0;
    if (account_status(account_statutus) == 0)
        check = 0;
    if (min_size(id) == 0)
        check = 0;
    if (min_size(name) == 0)
        check = 0;
    if (min_size(phone_number) == 0)
        check = 0;
    if (min_size(sex) == 0)
        check = 0;
    if (min_size(passport) == 0)
        check = 0;
    if (min_size(address) == 0)
        check = 0;
    if (min_size(pay_method) == 0)
        check = 0;
    if (check == 0) {
        insertin2(invalidusers, id, 1);
    }
    free(id);
    free(name);
    free(email);
    free(phone_number);
    free(birth_date);
    free(sex);
    free(passport);
    free(country_code);
    free(address);
    free(account_creation);
    free(pay_method);
    free(account_statutus);
    free(linhada);

    return check;
}

// id0;user_id1;hotel_id2;hotel_name3;hotel_stars4;city_tax5;address6;begin_date7;end_date8;price_per_night9;includes_breakfast10;room_details11;rating12;comment13
int reservavalida(char *informacao, struct HashTable2* invalidusers)
{

    char *id;
    char *user_id;
    char *hotel_id;
    char *hotel_name;
    char *hotel_stars;
    char *city_taxes;
    char *address;
    char *begin_date;
    char *end_date;
    char *price_per_night;
    char *includes_breakfast;
    char *room_details;
    char *rating;
    char *comment;

    char *linhada = strdup(informacao);

    char *token = strsep(&linhada, ";");
    if (token != NULL)
        id = token;
    else
        id = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        user_id = strdup(token);
    else
        user_id = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        hotel_id = strdup(token);
    else
        hotel_id = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        hotel_name = strdup(token);
    else
        hotel_name = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        hotel_stars = strdup(token);
    else
        hotel_stars = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        city_taxes = strdup(token);
    else
        city_taxes = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        address = strdup(token);
    else
        address = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        begin_date = strdup(token);
    else
        begin_date = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        end_date = strdup(token);
    else
        end_date = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        price_per_night = strdup(token);
    else
        price_per_night = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        includes_breakfast = strdup(token);
    else
        includes_breakfast = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        room_details = strdup(token);
    else
        room_details = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        rating = strdup(token);
    else
        rating = strdup("");
    token = strsep(&linhada, ";");
    if (token != NULL)
        comment = strdup(token);
    else
        comment = strdup("");

    int check = 1;
    if (data_valida(begin_date) == 0)
        check = 0;
    if (data_valida(end_date) == 0)
        check = 0;
    if (ordem_datas_horas_2(begin_date, end_date) == 0)
        check = 0;
    if (estrelas_hotel(hotel_stars) == 0)
        check = 0;
    if (city_tax(city_taxes) == 0)
        check = 0;
    if (preco_noite(price_per_night) == 0)
        check = 0;
    if (pequeno_almoco(includes_breakfast) == 0)
        check = 0;
    if (rating_reserva(rating) == 0)
        check = 0;
    if (min_size(id) == 0)
        check = 0;
    if (min_size(user_id) == 0)
        check = 0;
    if (min_size(hotel_id) == 0)
        check = 0;
    if (min_size(hotel_name) == 0)
        check = 0;
    if (min_size(address) == 0)
        check = 0;
    if (searchvalue2(invalidusers, user_id)) {
        check = 0;
    }

    free(id);
    free(user_id);
    free(hotel_id);
    free(hotel_name);
    free(hotel_stars);
    free(city_taxes);
    free(address);
    free(begin_date);
    free(end_date);
    free(price_per_night);
    free(includes_breakfast);
    free(room_details);
    free(rating);
    free(comment);

    // Free the memory for token
    //free(token);

    // Free the memory allocated for linhada
    free(linhada);

    return check;
}
