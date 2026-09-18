#include "csvWriter.h"
#include <stdio.h>

// Function to append the current row of values to the CSV file
void csvwriter(const char *filename, double col1, double col2, double col3, double col4, double col5) {
    FILE *file = fopen(filename, "a"); // Open in append mode
    if (file == NULL) {
        perror("Error opening the file");
        return;
    }

    // Write the current row with the provided values 
    fprintf(file, "%lf,%lf,%lf,%lf,%lf\n", col1, col2, col3, col4, col5);

    fclose(file);
}

