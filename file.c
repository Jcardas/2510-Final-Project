//
// Created by Justin Cardas on 2025-04-03.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define FILE_NAME "patients.txt"

#include "file.h"
#include "patient.h"
#include "patientsList.h"

FILE *initializeFile()
{
        FILE *dataFile = fopen(FILE_NAME, "r+");
        if (dataFile == NULL)
                dataFile = fopen(FILE_NAME, "w+");
        return dataFile;
}

extern PatientNodePtr patientsList;
;

PatientNodePtr populatePatientNodesFromFile(FILE *file)
{
        PatientNodePtr patientsList = malloc(sizeof(PatientNode));

        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file) !=
               NULL) { // Read through the file line by line.
                {
                        char *token = strtok(line, "|");
                        int patientID =
                                atoi(token); // The first data point is ID

                        token = strtok(NULL, "|"); // Move to next token
                        char *patientName = token;

                        token = strtok(NULL, "|");
                        int patientAge = atoi(token);

                        token = strtok(NULL, "|");
                        char *patientDiagnosis = token;

                        token = strtok(NULL, "|");
                        int patientRoomNum = atoi(token);

                        Patient newPatient;

                        newPatient.patientId = patientID;
                        strcpy(newPatient.name, patientName);
                        newPatient.age = patientAge;
                        newPatient.roomNumber = patientRoomNum;
                        strcpy(newPatient.diagnosis, patientDiagnosis);

                        add(&patientsList, newPatient);
                }
        }

        return patientsList;
}

void updateFile(FILE *file, PatientNode patients)
{
        FILE *dataFile =
                fopen(FILE_NAME, "w"); // Open in write mode to overwrite
        if (dataFile == NULL) {
                printf("Error opening file for overwriting\n");
                return;
        }
        PatientNode *thisPatient = &patients; // Start from the first node

        while (thisPatient != NULL) {
                fprintf(dataFile, "%d|%s|%d|%s|%d\n",
                        thisPatient->data.patientId, thisPatient->data.name,
                        thisPatient->data.age, thisPatient->data.diagnosis,
                        thisPatient->data.roomNumber);
                thisPatient = thisPatient->next; // Move to next node
        }
        fclose(dataFile); // Close file
}
