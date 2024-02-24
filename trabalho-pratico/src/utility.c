#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "utility.h"

#define ToTestYear 2023
#define ToTestMonth 10
#define ToTestDay 1

char* convertToUpperCase(char *word) {
    char *result = word;
    while (*word) {
        *word = toupper(*word);
        word++;
    }
    return result;
}

double calculateAge(char *birthdate) {
    // Parse birthdate string
    int birthYear, birthMonth, birthDay;
    sscanf(birthdate, "%d/%d/%d", &birthYear, &birthMonth, &birthDay);

    // Calculate age
    double age = 2023 - birthYear;

    // Adjust age based on the current month and day
    if (ToTestMonth < birthMonth || (ToTestMonth == birthMonth && ToTestDay < birthDay)) {
        age--;
    }

    return age;
}

// Function to calculate the number of nights between two dates
int calculateNights(const char *begin_date, const char *end_date) {
    // Parse the year, month, and day from the input strings
    int begin_year, begin_month, begin_day;
    int end_year, end_month, end_day;

    sscanf(begin_date, "%d/%d/%d", &begin_year, &begin_month, &begin_day);
    sscanf(end_date, "%d/%d/%d", &end_year, &end_month, &end_day);

    // Convert the dates to a numerical representation (e.g., days since a reference date)
    int begin_numerical = begin_year * 365 + begin_month * 30 + begin_day;
    int end_numerical = end_year * 365 + end_month * 30 + end_day;

    // Calculate the difference in days
    int night_difference = end_numerical - begin_numerical;

    return night_difference;
}

int calculateDelayInSeconds(const char *schedule_departure_date, const char *real_departure_date) {
    struct tm scheduled_tm = {0};
    struct tm real_tm = {0};
    time_t scheduled_time, real_time;

    // Convert schedule_departure_date to struct tm
    sscanf(schedule_departure_date, "%d/%d/%d %d:%d:%d",
           &scheduled_tm.tm_year, &scheduled_tm.tm_mon, &scheduled_tm.tm_mday,
           &scheduled_tm.tm_hour, &scheduled_tm.tm_min, &scheduled_tm.tm_sec);

    scheduled_tm.tm_year -= 1900; // Adjust year to start from 1900
    scheduled_tm.tm_mon -= 1;     // Adjust month to start from January

    // Convert real_departure_date to struct tm
    sscanf(real_departure_date, "%d/%d/%d %d:%d:%d",
           &real_tm.tm_year, &real_tm.tm_mon, &real_tm.tm_mday,
           &real_tm.tm_hour, &real_tm.tm_min, &real_tm.tm_sec);

    real_tm.tm_year -= 1900; // Adjust year to start from 1900
    real_tm.tm_mon -= 1;     // Adjust month to start from January

    // Convert struct tm representations to time_t
    scheduled_time = mktime(&scheduled_tm);
    real_time = mktime(&real_tm);

    // Calculate the delay in seconds (ensure non-negative)
    int delay_seconds = difftime(real_time, scheduled_time);

    return (delay_seconds >= 0) ? delay_seconds : 0;
}

// Function to check if the first 4 characters of a string are "Book"
int startsWithBook(char *str) {
    // Check if the string is not NULL and has at least 4 characters
    if (str != NULL && strlen(str) >= 4) {
        // Compare the first 4 characters with "Book"
        if (strncmp(str, "Book", 4) == 0) return 1;
    }
    // If the string is NULL or has less than 4 characters, it can't start with "Book"
    return 0;
}
void updatePath(int line, char* line2) {
    // Assuming MAX_STRING_LENGTH is enough to store the string representation of an integer
    snprintf(line2, 50, "%d", line);
}

// Function to check if the first 4 characters of a string are "0000"
int startsWith0000(char *str) {
    // Check if the string is not NULL and has at least 4 characters
    if (str != NULL && strlen(str) >= 4) {
        // Compare the first 4 characters with "Book"
        if (strncmp(str, "0000", 4) == 0) return 1;
    }
    // If the string is NULL or has less than 4 characters, it can't start with "Book"
    return 0;
}

char* extractYear(char* input) {
    // Allocate memory for the year string
    char* year = (char*)malloc(5);  // Assuming the year is always 4 digits

    // Check if memory allocation is successful
    if (year != NULL) {
        // Copy the first 4 characters from the input string to the year string
        strncpy(year, input, 4);

        // Null-terminate the year string
        year[4] = '\0';
    }

    return year;
}

void separateString(const char* input, int* year, int* size) {
    // Use sscanf to extract two integers from the input string
    sscanf(input, "%d %d", year, size);
}

void capitalizeFirstLetter(char *word) {
    // Check if the string is not empty
    if (word != NULL && *word != '\0') {
        // Convert the first character to uppercase
        *word = toupper(*word);
    }
}

void updateDateString(char *date) {
    // Find the index of the first space character (' ') in the date string
    char *spaceIndex = strchr(date, ' ');

    // If a space is found, truncate the string at that position
    if (spaceIndex != NULL) {
        *spaceIndex = '\0';
    }
}

void separateString2(char *input, char **word1, char **word2) {
    // Find the index where the second word begins
    char *separator = input;
    while (*separator != '\0' && !isspace(*separator)) {
        separator++;
    }

    // Allocate memory for the first word
    *word1 = (char *)malloc(separator - input + 1);
    if (*word1 == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Copy the first word into the new buffer
    strncpy(*word1, input, separator - input);
    (*word1)[separator - input] = '\0';  // Null-terminate the first word

    // Allocate memory for the second word
    *word2 = strdup(separator + 1);
    if (*word2 == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        free(*word1);  // Free the memory allocated for the first word
        exit(EXIT_FAILURE);
    }
}

int isSeparated (char *str) {
    while (*str != '\0') {
        if (*str == ' ') {
            return 1;  // Found a space character
        }
        str++;
    }
    return 0;  // No space character found
}

void addreservations(char **inputString) {
    // Check if the inputString is not null
    if (inputString != NULL && *inputString != NULL) {
        // Calculate the new length of the string
        size_t originalLength = strlen(*inputString);
        size_t newLength = originalLength + strlen(";reservation");

        // Reallocate memory for the updated string
        *inputString = (char *)realloc(*inputString, newLength + 1); // +1 for the null terminator

        // Check if memory reallocation was successful
        if (*inputString != NULL) {
            // Concatenate ";reservations" to the end of the inputString
            strcat(*inputString, ";reservation");
        } else {
            // Handle memory reallocation failure
            fprintf(stderr, "Memory reallocation failed\n");
        }
    }
}

void addflights (char **inputString) {
    // Check if the inputString is not null
    if (inputString != NULL && *inputString != NULL) {
        // Calculate the new length of the string
        size_t originalLength = strlen(*inputString);
        size_t newLength = originalLength + strlen(";flight");

        // Reallocate memory for the updated string
        *inputString = (char *)realloc(*inputString, newLength + 1); // +1 for the null terminator

        // Check if memory reallocation was successful
        if (*inputString != NULL) {
            // Concatenate ";reservations" to the end of the inputString
            strcat(*inputString, ";flight");
        } else {
            // Handle memory reallocation failure
            fprintf(stderr, "Memory reallocation failed\n");
        }
    }
}

void separateString3(char *input, char **id, char **date) {
    // Find the position of the semicolon
    char *semicolonPos = strchr(input, ';');

    if (semicolonPos == NULL) {
        // Semicolon not found, handle error or return as needed
        *id = NULL;
        *date = NULL;
        return;
    }

    // Calculate the length of the id and date strings
    size_t idLength = semicolonPos - input;
    size_t dateLength = strlen(input) - idLength - 1;

    // Allocate memory for id and date strings
    *id = (char *)malloc((idLength + 1) * sizeof(char));
    *date = (char *)malloc((dateLength + 1) * sizeof(char));

    // Copy the id and date strings
    strncpy(*id, input, idLength);
    strncpy(*date, semicolonPos + 1, dateLength);

    // Null-terminate the strings
    (*id)[idLength] = '\0';
    (*date)[dateLength] = '\0';
}

void separateString4(char *input, char **id, char **date, char **type) {
    // Find the positions of the semicolons
    char *firstSemicolonPos = strchr(input, ';');
    char *secondSemicolonPos = strchr(firstSemicolonPos + 1, ';');

    if (firstSemicolonPos == NULL || secondSemicolonPos == NULL) {
        // Semicolons not found, handle error or return as needed
        *id = NULL;
        *date = NULL;
        *type = NULL;
        return;
    }

    // Calculate the lengths of the id, date, and type strings
    size_t idLength = firstSemicolonPos - input;
    size_t dateLength = secondSemicolonPos - firstSemicolonPos - 1;
    size_t typeLength = strlen(input) - (secondSemicolonPos - input) - 1;

    // Allocate memory for id, date, and type strings
    *id = (char *)malloc((idLength + 1) * sizeof(char));
    *date = (char *)malloc((dateLength + 1) * sizeof(char));
    *type = (char *)malloc((typeLength + 1) * sizeof(char));

    // Copy the id, date, and type strings
    strncpy(*id, input, idLength);
    strncpy(*date, firstSemicolonPos + 1, dateLength);
    strncpy(*type, secondSemicolonPos + 1, typeLength);

    // Null-terminate the strings
    (*id)[idLength] = '\0';
    (*date)[dateLength] = '\0';
    (*type)[typeLength] = '\0';
}

int extractNumber(char *str) {
    // Skip the characters until the first digit is encountered
    while (*str && !isdigit(*str)) {
        str++;
    }

    // Convert the remaining characters to an integer
    return atoi(str);
}
// Custom comparison function for sorting dates
int compareDates1(const char *dateStrA, const char *dateStrB) {
    struct Date dateA, dateB;

    // Extract date components from strings
    sscanf(dateStrA, "%*[^;];%d/%d/%d", &dateA.year, &dateA.month, &dateA.day);
    sscanf(dateStrB, "%*[^;];%d/%d/%d", &dateB.year, &dateB.month, &dateB.day);

    // Compare years
    if (dateA.year != dateB.year) {
        return dateB.year - dateA.year;
    }

    // Compare months
    if (dateA.month != dateB.month) {
        return dateB.month - dateA.month;
    }

    // Compare days
    return dateB.day - dateA.day;
}
// Custom comparison function for comparing two records based on "Booknumber"
int compareRecords(const void *a, const void *b) {
    // Extract "Booknumber" from each line
    char bookNumber1[20];
    char bookNumber2[20];

    sscanf(*(const char **)a, "Book%19[^;];", bookNumber1);
    sscanf(*(const char **)b, "Book%19[^;];", bookNumber2);

    // Convert "Booknumber" to integers and compare
    int number1 = atoi(bookNumber1 + 3); // Skip "00000" prefix
    int number2 = atoi(bookNumber2 + 3); // Skip "00000" prefix

    return number1 - number2;
}

int compareDates1q(const void *a, const void *b) {
    struct Date dateA, dateB;

    sscanf(*(const char **)a, "%*[^;];%d/%d/%d", &dateA.year, &dateA.month, &dateA.day);
    sscanf(*(const char **)b, "%*[^;];%d/%d/%d", &dateB.year, &dateB.month, &dateB.day);
  

    if (dateA.year != dateB.year) {
        return dateB.year - dateA.year;
    }

    if (dateA.month != dateB.month) {
        return dateB.month - dateA.month;
    }
    if (dateB.day == dateA.day) return compareRecords(a, b);
    return dateB.day - dateA.day;
}


// Custom bubble sort function
void bubbleSortdates(char *arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compareDates1(arr[j], arr[j + 1]) > 0) {
                // Swap elements if they are in the wrong order
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            else if (compareDates1(arr[j], arr[j+1])==0) {
                if (compareRecords(arr[j], arr[j+1]) > 0) {
                   // Swap elements if they are in the wrong order
                    char *temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp; 
                }
            }
        }
    }
}

void insertAndOrder(char **arr, int *occupancy, char *string) {
    // Find the position to insert the new element
    int i = 0;
    while (i < *occupancy && compareDates1(arr[i], string) <= 0) {
        i++;
    }

    // Shift elements to make room for the new element
    for (int j = *occupancy; j > i; j--) {
        arr[j] = arr[j - 1];
    }

    // Insert the new element at the correct position
    arr[i] = strdup(string);

    // Update occupancy
    (*occupancy)++;
}
// Swap two elements in an array
void swap(void *a, void *b, size_t size) {
    char temp[size];
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

// Partition function for quicksort
int partition(void *arr, int low, int high, size_t size, int (*compare)(const void *, const void *)) {
    void *pivot = (char *)arr + high * size;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        void *current = (char *)arr + j * size;

        if (compare(current, pivot) <= 0) {
            i++;
            swap((char *)arr + i * size, (char *)arr + j * size, size);
        }
    }

    swap((char *)arr + (i + 1) * size, (char *)arr + high * size, size);
    return i + 1;
}

// Quicksort algorithm
void quicksort(void *arr, int low, int high, size_t size, int (*compare)(const void *, const void *)) {
    if (low < high) {
        int partitionIndex = partition(arr, low, high, size, compare);

        quicksort(arr, low, partitionIndex - 1, size, compare);
        quicksort(arr, partitionIndex + 1, high, size, compare);
    }
}

// Wrapper function for user convenience
void qsort_custom(void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *)) {
    quicksort(base, 0, nmemb - 1, size, compare);
}

int compareairportsname(const void *a, const void *b) {
    char aep1[5], aep2[5];
    sscanf(*(const char **)a, "%4[^;]", aep1);
    sscanf(*(const char **)b, "%4[^;]", aep2);
    return (strcmp(aep1, aep2) > 0);
    }

int compareNumbersInStrings(const void *a, const void *b) {
    int num1, num2;
    sscanf(*(const char **)a, "%*[^;];%d", &num1);
    sscanf(*(const char **)b, "%*[^;];%d", &num2);

    if (num2==num1) return compareairportsname(a, b);
    return (num2-num1);
}


// Quicksort function for array of strings
void qsortStrings(char *array[], int size) {
    qsort(array, size, sizeof(char *), compareDates1q);
}

// Quicksort function for array of strings
void qsortStrings7(char *array[], int size) {
    qsort(array, size, sizeof(char *), compareNumbersInStrings);
}

void splitString6(const char *input, char *output[6]) {
    char *token;
    char copy[100];  // Assuming a maximum input length of 256 characters, adjust as needed
    strcpy(copy, input);

    // Initialize output array
    for (int i = 0; i < 6; ++i) {
        output[i] = NULL;
    }

    // Tokenize the input string using strtok
    token = strtok(copy, ";");
    int i = 0;
    while (token != NULL && i < 6) {
        output[i++] = token;
        token = strtok(NULL, ";");
    }
}
int comparefDates(char *date1,char *date2) {
    if (date1 == NULL || date2 == NULL)fprintf(stderr, "NULL DATES");
    // Compare each date component one by one
    int year1, month1, day1, hour1, minute1, second1;
    int year2, month2, day2, hour2, minute2, second2;

    if (sscanf(date1, "%d/%d/%d %d:%d:%d", &year1, &month1, &day1, &hour1, &minute1, &second1) != 6) {
        fprintf(stderr, "Error parsing date: %s\n", date1);
        return -1;
    }

    if (sscanf(date2, "%d/%d/%d %d:%d:%d", &year2, &month2, &day2, &hour2, &minute2, &second2) != 6) {
        fprintf(stderr, "Error parsing date: %s\n", date2);
        return -1;
    }

    // Compare years
    if (year1 != year2) {
        return year1 > year2 ? -1 : 1;
    }

    // Compare months
    if (month1 != month2) {
        return month1 > month2 ? -1 : 1;
    }

    // Compare days
    if (day1 != day2) {
        return day1 > day2 ? -1 : 1;
    }

    // Compare hours
    if (hour1 != hour2) {
        return hour1 > hour2 ? -1 : 1;
    }

    // Compare minutes
    if (minute1 != minute2) {
        return minute1 > minute2 ? -1 : 1;
    }

    // Compare seconds
    if (second1 != second2) {
        return second1 > second2 ? -1 : 1;
    }

    // Dates are equal
    return 0;
}

int isDateInInterval(char *string1, char *string2, char *string3) {
    // Check if string2 is in the future or equal to string3
    // and string2 is in the past or equal to string1
    if (comparefDates(string1, string2) <= 0 && comparefDates(string3, string2) >= 0) {
        return 1;  // Date is comprehended in the time interval
    }

    return 0;  // Date is outside the time interval
}

// Function to extract the second section from the input string
char* extractSecondSection(const char* inputString) {
    // Find the start of the second section
    const char* start = strchr(inputString, ';');
    
    // Check if the first semicolon is found
    if (start != NULL) {
        // Move to the character after the first semicolon
        start++;

        // Find the end of the second section (next semicolon or end of string)
        const char* end = strchr(start, ';');

        // Calculate the length of the second section
        size_t length = (end != NULL) ? (size_t)(end - start) : strlen(start);

        // Allocate memory for the second section
        char* secondSection = (char*)malloc(length + 1);

        // Copy the second section to the allocated memory
        strncpy(secondSection, start, length);

        // Null-terminate the string
        secondSection[length] = '\0';
        return secondSection;
    }
    return NULL;
}

int comparison5(const void *a, const void *b) {
    char date1[40];
    char date2[40];
    char id1[30];
    char id2[30];
    sscanf(*(const char **)a,"%*[^;];%49[^;]", date1);
    sscanf(*(const char **)b,"%*[^;];%49[^;]", date2);
    sscanf(*(const char **)a,"%49[^;];%*[^;]", id1);
    sscanf(*(const char **)b,"%49[^;];%*[^;]", id2);
    int min = atoi(id1);
    int eirada = atoi(id2);
    if (strcmp(date1, date2) ==0) {
        return (min-eirada);
    }
    return comparefDates(date1, date2);
}

void qsortStrings5(char *array[], int size) {
    qsort(array, size, sizeof(char *), comparison5);
}

void splitin5(char originalString[], char resultStrings[][30]) {
    char *token;
    const char delimiter[] = ";";
    
    // Using strtok to split the original string based on the delimiter
    token = strtok(originalString, delimiter);

    // Copy each token into the resultStrings array
    for (int i = 0; i < 5 && token != NULL; i++) {
        strcpy(resultStrings[i], token);
        token = strtok(NULL, delimiter);
    }
}

int dateToDays(char *date) {
    // Convert date string to days since a reference date
    int year, month, day;
    sscanf(date, "%d/%d/%d", &year, &month, &day);
    return year * 365 + month * 30 + day;
}

int exception(char *date3, char *date4) {
    // Convert date string to days since a reference date
    int year3, month3, day3;
    int year4, month4, day4;
    sscanf(date3, "%d/%d/%d", &year3, &month3, &day3);
    sscanf(date4, "%d/%d/%d",&year4, &month4, &day4);
    if (year3==year4 && month3==month4) return 1;
    return 0;
}

int countCommonNights(char *date1, char *date2, char *date3, char *date4) {
    int start1 = dateToDays(date1);
    int end1 = dateToDays(date2);
    int start2 = dateToDays(date3);
    int end2 = dateToDays(date4);

    int overlapStart = (start1 > start2) ? start1 : start2;
    int overlapEnd = (end1 < end2) ? end1 : end2;

    int commonNights = (overlapEnd - overlapStart);

    int isexpection = exception(date3,date4);
    commonNights+=isexpection;

    if (commonNights < 0) {
        commonNights = 0;
    }
    return commonNights;
}

int hasDoubleQuotes(char *str) {
    int length = strlen(str);
    
    // Check if the string is at least 3 characters long
    if (length < 3) {
        return 0;
    }

    // Check if the first and last characters are double quotes
    if (str[0] == '"' && str[length - 1] == '"') {
        return 1;
    } else {
        return 0;
    }
}

void removeDoubleQuotes(char *str) {
    int length = strlen(str);

    // Check if the string is at least 2 characters long
    if (length >= 2 && str[0] == '"' && str[length - 1] == '"') {
        // Shift the characters to remove the double quotes
        for (int i = 0; i < length - 1; i++) {
            str[i] = str[i + 1];
        }

        // Null-terminate the string at the new end
        str[length - 2] = '\0';
    }
}

int isPrefix(char *prefix, char *str) {
    int prefixLength = strlen(prefix);
    int strLength = strlen(str);

    // Check if the prefix is longer than the string
    if (prefixLength > strLength) {
        return 0;
    }

    // Compare the characters of the prefix with the corresponding characters in the string
    for (int i = 0; i < prefixLength; i++) {
        if (prefix[i] != str[i]) {
            return 0; // Characters don't match
        }
    }

    return 1; // All characters match, prefix is a prefix of the string
}

void replaceHyphenWithSpace(char *input, char *output) {
    while (*input) {
        *output = (*input == '-') ? ' ' : *input;
        input++;
        output++;
    }
    *output = '\0';
}

// Function to remove accents from a string
void removeAccents(char *input, char *output) {
    // Create an iconv descriptor
    iconv_t cd = iconv_open("ASCII//TRANSLIT", "UTF-8");
    if (cd == (iconv_t)-1) {
        perror("iconv_open");
        exit(EXIT_FAILURE);
    }

    // Set up input and output pointers
    const char *inptr = input;
    size_t inlen = strlen(input);
    char *outptr = output;
    size_t outlen = 50;  // Adjust the size based on your needs

    // Perform the conversion
    if (iconv(cd, (char **)&inptr, &inlen, &outptr, &outlen) == (size_t)-1) {
        perror("iconv");
        exit(EXIT_FAILURE);
    }

    // Close the iconv descriptor
    iconv_close(cd);

    // Null-terminate the output string
    *outptr = '\0';
}

int compareAlphabetically(char *str1, char *str2) {
    char str1Modified[50];
    char str2Modified[50]; 
    char str1Modified2[50];
    char str2Modified2[50]; 
    replaceHyphenWithSpace(str1, str1Modified);
    replaceHyphenWithSpace(str2, str2Modified);
    removeAccents(str1Modified, str1Modified2);
    removeAccents(str2Modified, str2Modified2);

    return strcasecmp(str1Modified2, str2Modified2);
}
int comparison9(const void *a, const void *b) {
    setlocale(LC_COLLATE, "en_US.UTF-8");
    char name1[40];
    char name2[40];
    char id1[30];
    char id2[30];
    sscanf(*(const char **)a,"%*[^;];%49[^;]", name1);
    sscanf(*(const char **)b,"%*[^;];%49[^;]", name2);
    sscanf(*(const char **)a,"%49[^;];%*[^;]", id1);
    sscanf(*(const char **)b,"%49[^;];%*[^;]", id2);
    if (strcmp(name1, name2) == 0) {
        //return compareAlphabetically(id1, id2);
        return strcoll(id1, id2);
    }
        return strcoll(name1, name2);
}
void qsortStrings9(char *array[], int size) {
    qsort(array, size, sizeof(char *), comparison9);
}
// Custom bubble sort function
void bubbleSortAlphabeticallyuntie(char *arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            char name1[40];
            char name2[40];
            char id1[30];
            char id2[30];
            sscanf(arr[j], "%*[^;];%49[^;]", name1);
            sscanf(arr[j+1], "%*[^;];%49[^;]", name2);
            sscanf(arr[j], "%49[^;];%*[^;]", id1);
            sscanf(arr[j+1], "%49[^;];%*[^;]", id2);
                if (!compareAlphabetically(name1, name2) && strcmp(name1, name2)) {
                // Swap elements if they are in the wrong order
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                }
                else if (strcmp(name1, name2) == 0) {
                    if (!compareAlphabetically(id1, id2)) {
                // Swap elements if they are in the wrong order
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                    }
            }
        }
    }
}
void splitStringin2(char *input, char *string1, char *string2) {
    char *token;

    // Use strtok to find the first token (string1)
    token = strtok((char *)input, ";");

    // Check if strtok found a token
    if (token != NULL) {
        strcpy(string1, token);

        // Use strtok again to find the second token (string2)
        token = strtok(NULL, ";");

        // Check if strtok found a second token
        if (token != NULL) {
            strcpy(string2, token);
        } else {
            strcpy(string2, "");  // Set string2 to an empty string if missing
        }
    } else {
        strcpy(string1, "");  // Set string1 to an empty string if missing
        strcpy(string2, "");  // Set string2 to an empty string if missing
    }
}

int compareFiles(const char *file1, const char *file2) {
    FILE *fp1, *fp2;
    char line1[1024], line2[1024];

    // Open the files
    fp1 = fopen(file1, "r");
    if (fp1 == NULL) {
        perror("Error opening file 1");
        exit(EXIT_FAILURE);
    }

    fp2 = fopen(file2, "r");
    if (fp2 == NULL) {
        perror("Error opening file 2");
        fclose(fp1);
        exit(EXIT_FAILURE);
    }

    // Compare the contents line by line
    while (fgets(line1, sizeof(line1), fp1) != NULL && fgets(line2, sizeof(line2), fp2) != NULL) {
        if (strcmp(line1, line2) != 0) {
            // Files are not equal
            fclose(fp1);
            fclose(fp2);
            return 0;
        }
    }

    return 1;
}