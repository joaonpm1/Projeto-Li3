#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashq2.h"

// Simple hash function
unsigned int hashp(char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 7) + *key;
        key++;
    }
    return hash % TABLE_SIZE;
}
struct Slot** createTablep() {
    struct Slot** table = (struct Slot**)malloc(TABLE_SIZE * sizeof(struct Slot*));
    
    // Initialize each slot to NULL
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = NULL;
    }

    return table;
}


// Function to create a new slot
struct Slot* createNodep(char* key) {
    struct Slot* newNode = (struct Slot*)malloc(sizeof(struct Slot));
    newNode->key = strdup(key);
    newNode->next = NULL;
    newNode->values = NULL;
    return newNode;
}

// Function to insert a key-value pair into the hash table
void insertp(struct Slot* table[], char* key, char* info) {
    unsigned int index = hashp(key);

    if (table[index] == NULL) {
        table[index] = createNodep(key);
    }

    struct Slot* currentKey = table[index];
    while (currentKey != NULL) {
        if (strcmp(currentKey->key, key) == 0) {
            // Key already exists, add the new value to the list
            struct Value* newValueNode = (struct Value*)malloc(sizeof(struct Value));
            newValueNode->info = strdup(info);
            newValueNode->next = currentKey->values;
            currentKey->values = newValueNode;
            return;
        }
        if (currentKey->next == NULL) {
            currentKey->next = createNodep(key);
            break;
        }
        currentKey = currentKey->next;
    }
}


// Function to search for values in the hash table based on the key
struct Value* searchp(struct Slot* table[], char* key) {
    unsigned int index = hashp(key);
    struct Slot* currentKey = table[index];
    
    while (currentKey != NULL) {
        if (strcmp(currentKey->key, key) == 0) {
            // Key found, return the list of values
            return currentKey->values;
        }
        currentKey = currentKey->next;
    }

    return NULL; // Key not found, return NULL
}

void printValuesp(struct Value* values) {
    struct Value* current = values;

    while (current != NULL) {
        printf("%s\n", current->info);
        current = current->next;
    }
}

// Parse date string "YYYY/MM/DD" into year, month, and day
void parseDate(char *date, int *year, int *month, int *day) {
    sscanf(date, "%d/%d/%d", year, month, day);
}

// Compare two dates in "YYYY/MM/DD" format, ignoring the book information

int compareDates(char *date1, char *date2) {
    // Find the position of the ';' character
    char *ptr1 = strchr(date1, ';');
    char *ptr2 = strchr(date2, ';');
    // Move past the ';' character if found, otherwise use the original strings
    char *datePart1 = (ptr1 != NULL) ? ptr1 + 1 : date1;
    char *datePart2 = (ptr2 != NULL) ? ptr2 + 1 : date2;
    // Parse dates into year, month, and day
    int year1, month1, day1;
    int year2, month2, day2;
    parseDate(datePart1, &year1, &month1, &day1);
    parseDate(datePart2, &year2, &month2, &day2);
    // Compare year, month, and day in the correct order
    if (year1 != year2) {
        return year1 - year2; // Compare years in forward order
    } else if (month1 != month2) {
        return month1 - month2; // Compare months in forward order
    } else {
        return day1 - day2; // Compare days in forward order
    }
}

// Function to swap two values in the linked list
void swapValues(struct Value *a, struct Value *b) {
    char *temp = a->info;
    a->info = b->info;
    b->info = temp;
}

// Function to perform bubble sort on the linked list
void bubbleSort(struct Value *start) {
    int swapped;
    struct Value *ptr1;
    struct Value *lptr = NULL;

    if (start == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (compareDates(ptr1->info, ptr1->next->info) < 0) {
                swapValues(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Bubble sort function to sort the linked list
void bubbleSort2(struct Value* start) {
    int swapped;
    struct Value* ptr1;
    struct Value* lptr = NULL;

    // Checking for empty list
    if (start == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            // Extract numeric part after the ";"
            int num1 = atoi(strchr(ptr1->info, ';') + 1);
            int num2 = atoi(strchr(ptr1->next->info, ';') + 1);

            if (num1 < num2) {
                swapValues(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Compare function for qsort
int compare(const void *a, const void *b) {
    struct Value *va = *(struct Value **)a;
    struct Value *vb = *(struct Value **)b;

    // Extract numeric values from strings
    int numa = atoi(strchr(va->info, ';') + 1);
    int numb = atoi(strchr(vb->info, ';') + 1);

    // Compare numeric values
    if (numa != numb) {
        return numb - numa; // Reversing the order for descending numeric order
    } else {
        // If numeric values are equal, compare alphabetically
        return strcmp(va->info, vb->info);
    }
}

// Function to reorder the linked list
void ordernatelist(struct Value **list) {
    // Count the number of elements in the list
    int count = 0;
    struct Value *current = *list;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // Create an array of pointers to struct Value
    struct Value **array = malloc(count * sizeof(struct Value *));
    if (array == NULL) {
        // Handle memory allocation error
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Fill the array with pointers to struct Value
    current = *list;
    for (int i = 0; i < count; i++) {
        array[i] = current;
        current = current->next;
    }

    // Sort the array using the compare function
    qsort(array, count, sizeof(struct Value *), compare);

    // Reorder the linked list using the sorted array
    *list = array[0];
    current = *list;
    for (int i = 1; i < count; i++) {
        current->next = array[i];
        current = current->next;
    }
    current->next = NULL;

    // Free the temporary array
    free(array);
}

int getLength(struct Value* head) {
    int length = 0;
    struct Value* current = head; // Start from the head of the linked list

    // Traverse the linked list and count the nodes
    while (current != NULL) {
        length++;
        current = current->next;
    }

    return length;
}

void splitString(char *input, char **name, char **med) {
    // Find the position of the semicolon
    char *semicolonPos = strchr(input, ';');

    if (semicolonPos != NULL) {
        // Calculate the length of the name and medicine strings
        size_t nameLength = semicolonPos - input;
        size_t medLength = strlen(semicolonPos + 1);

        // Allocate memory for the name and medicine strings
        *name = (char *)malloc(nameLength + 1);
        *med = (char *)malloc(medLength + 1);

        // Copy the name and medicine strings
        strncpy(*name, input, nameLength);
        strncpy(*med, semicolonPos + 1, medLength);

        // Null-terminate the strings
        (*name)[nameLength] = '\0';
        (*med)[medLength] = '\0';
    } else {
        // If no semicolon is found, set both strings to NULL
        *name = NULL;
        *med = NULL;
    }
}
void freeValues(struct Value* values) {
    while (values != NULL) {
        struct Value* temp = values;
        values = values->next;
        free(temp->info);
        free(temp);
    }
}

// Function to free a hash table
void freeTable(struct Slot** table) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        struct Slot* currentSlot = table[i];
        while (currentSlot != NULL) {
            struct Slot* tempSlot = currentSlot;
            currentSlot = currentSlot->next;
            
            // Free the linked list of values for the current slot
            freeValues(tempSlot->values);

            // Free the key for the current slot
            free(tempSlot->key);

            // Free the current slot
            free(tempSlot);
        }
    }

    // Free the table itself
    free(table);
}