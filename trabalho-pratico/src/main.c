#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Q.h"
#include "Interative.h"
#include "testprogram.h"

int main (int argc, char **argv) {
    if (argc == 1) {
        IterativeMode();
    }
    else if (argc == 3) {
        BatchMode(argv[1], argv[2]);
    }
    else if (argc == 4) {
        TestProgram(argv[1], argv[2], argv[3]);
    }
    else {
        printf("Incorrect number of arguments.\n");
        return 1;
    }
}