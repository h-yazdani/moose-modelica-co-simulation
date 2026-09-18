#ifndef MODELICASWITCH_C_
#define MODELICASWITCH_C_

#include <stdio.h>
#include <stdlib.h>
#include "ModelicaUtilities.h"
#include "ModelicaSwitch.h"

/*
 * Objective: Wait for MOOSE to finish simulating and exporting results of a given time step
 *
 * Description: This function opens and reads a text file containing a boolean value.
 * The function initializes the switch value to zero. If the value is zero,
 * the function repeatedly checks the file. If the value is one, it means that MOOSE
 * has finished the simulation, and Modelica can proceed with its simulation.
 *
 * Input: Switch.txt
 * Output: None
 */

void ModelicaSwitchFunction()
{
    int value;
    FILE *file;

    // Open the file for writing
    file = fopen("Switch.txt", "w");

    if (file == NULL)
    {
        perror("Error opening 'Switch.txt'");
        exit(EXIT_FAILURE);
    }

    // Write zero to the file
    fprintf(file, "0");
    fclose(file);

    // Repeatedly check the file
    while (1)
    {
        file = fopen("Switch.txt", "r");

        if (file == NULL)
        {
            perror("Error opening 'Switch.txt'");
            continue;
        }

        // Read the value from the file
        if (fscanf(file, "%d", &value) != 1)
        {
            fclose(file);
            continue;
        }

        fclose(file);

        if (value == 0)
        {
            // Continue checking the file
            continue;
        }
        else if (value == 1)
        {
            // MOOSE has finished; Modelica can proceed
            break;
        }
        else
        {
            printf("Invalid value in 'Switch.txt'. Ending the function.\n");
            break;
        }
    }
}

#endif
