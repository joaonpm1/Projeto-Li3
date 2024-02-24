#ifndef UTILITY_H
#define UTILITY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <iconv.h>
#include <locale.h>
// Custom structure to hold the parsed date components
struct Date {
    int year;
    int month;
    int day;
};
// Define a structure to hold the relevant information for each string
struct Record {
    char originalString[100];  // Adjust the size as needed
    char bookID[30];
    char startDate[32];
    char endDate[22];
    char author[50];
    int number;
    float price;
};
void qsortStrings5(char *array[], int size);
void qsortStrings7(char *array[], int size);
void qsortStrings9(char *array[], int size);
void qsortStrings(char *array[], int size);
int compareDates1q(const void *a, const void *b);
void qsort_custom(void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *));
void insertAndOrder(char **arr, int *occupancy, char *string);
int compareFiles(const char *file1, const char *file2);
char* convertToUpperCase(char *word);
double calculateAge(char *birthdate);
int calculateNights(const char *begin_date, const char *end_date);
int calculateDelayInSeconds(const char *schedule_departure_date, const char *real_departure_date);
int startsWithBook(char *str);
void updatePath(int line, char* line2);
int startsWith0000(char *str);
char* extractYear(char* input);
void separateString(const char* input, int* year, int* size);
void capitalizeFirstLetter(char *word);
void updateDateString(char *date);
void separateString2(char *input, char **word1, char **word2);
int isSeparated (char *str);
void addflights (char **inputString);
void addreservations(char **inputString);
void separateString3(char *input, char **id, char **date);
void separateString4(char *input, char **id, char **date, char **type);
int extractNumber(char *str);
int compareDates1(const char *dateStrA, const char *dateStrB);
void bubbleSortdates(char *arr[], int size);
int compareRecords(const void *a, const void *b);
void splitString6(const char *input, char *output[6]);
int isDateInInterval(char *ceiling, char *totest, char *ground);
int comparefDates(char *date1,char *date2);
char* extractSecondSection(const char* inputString);
void splitin5(char originalString[], char resultStrings[][30]);
int countCommonNights(char *date1, char *date2, char *date3, char *date4);
int dateToDays(char *date);
int exception(char *date3, char *date4);
void removeDoubleQuotes(char *str);
int hasDoubleQuotes(char *str);
int isPrefix(char *prefix, char *str);
void replaceHyphenWithSpace(char *input, char *output);
int compareAlphabetically(char *str1, char *str2);
void bubbleSortAlphabeticallyuntie(char *arr[], int size);
void splitStringin2(char *input, char *string1, char *string2);
#endif