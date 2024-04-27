#include <stdio.h>
#include "condorcet_paires.h"
#include "condorcet.h"
#include "matrice.h"
#include "graph.h"
#include "condorcet_paires.c"

#include "utils_sd.h"
#include "graph.h"



int main() {
    // Replace these with actual file paths and options
    char* filename = "VoteCondorcet.csv";
    FILE* log = fopen("outpout.log", "w");
    int option = 1; // Assuming this is an option that your program uses

    // Ensure the log file opened successfully
    if (log == NULL) {
        perror("Error opening log file");
        return -1;
    }

    // Call your main processing function
    // Make sure the function 'prog' is defined and accessible
    prog(filename, log, option);

    // Close the log file
    fclose(log);

    return 0;
}


