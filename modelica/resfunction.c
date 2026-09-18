#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define BUFFER_SIZE 1000

void resfunction(const char* input_file_path, const char* output_file_path) {
    // Step 1: Rename the input file to 'mod_res.csv'
    const char* s3_file_path = "mod_res.csv";

    if (rename(input_file_path, s3_file_path) != 0) {
        perror("Error renaming input file to mod_res.csv");
        exit(EXIT_FAILURE);
    }

    // Open the renamed 'mod_res.csv' for reading
    FILE* input_file = fopen(s3_file_path, "r");
    if (input_file == NULL) {
        perror("Error opening renamed input file");
        exit(EXIT_FAILURE);
    }

    char line[BUFFER_SIZE];
    double sum_values[BUFFER_SIZE];
    double first_column_values[BUFFER_SIZE];
    int count = 0;
    double min_value = DBL_MAX;
    int column_count = 0;
    int row_count = 0;

    // Initialize sum_values and first_column_values
    for (int i = 0; i < BUFFER_SIZE; i++) {
        sum_values[i] = 0;
        first_column_values[i] = DBL_MAX;
    }

    // Process each line in the file
    while (fgets(line, sizeof(line), input_file)) {
        char* token = strtok(line, ",");
        int column = 0;
        double current_value = 0;
        double first_column_value = 0;
        int duplicate_found = 0;

        double temp_row_values[BUFFER_SIZE];

        while (token != NULL) {
            sscanf(token, "%lf", &current_value);
            temp_row_values[column] = current_value;

            if (column == 0) {
                first_column_value = current_value;

                if (current_value < min_value) {
                    min_value = current_value;
                }

                // Check for duplicate first column value
                for (int i = 0; i < row_count; i++) {
                    if (first_column_values[i] == current_value) {
                        duplicate_found = 1;
                        break;
                    }
                }

                if (!duplicate_found) {
                    first_column_values[row_count] = current_value;
                }
            }

            column++;
            token = strtok(NULL, ",");
        }

        // If the row is not a duplicate, add it to the sum
        if (!duplicate_found) {
            for (int i = 1; i < column; i++) {
                sum_values[i - 1] += temp_row_values[i];
            }

            row_count++;
        }

        if (column_count == 0) {
            column_count = column;
        }

        count++;
    }

    fclose(input_file);

    // Step 2: Write the results to the output file
    FILE* output_file = fopen(output_file_path, "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    // Write the minimum value of the first column
    fprintf(output_file, "%lf", min_value - 3600);

    // Write the average of the other columns
    for (int i = 0; i < column_count - 1; i++) {
        double average = sum_values[i] / row_count;
        fprintf(output_file, ",%lf", average);
    }

    fprintf(output_file, "\n");
    fclose(output_file);

    // Step 3: Delete the original input file
    if (remove(input_file_path) != 0) {
        perror("Error deleting original input file");
    }
}
