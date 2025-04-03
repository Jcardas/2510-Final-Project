//
// Created by Justin Cardas on 2025-04-03.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

#include "main.h"
#include "file.h"
#include "patient.h"
#include "patientsList.c" //TODO change to Header file


FILE *initializeFile()
{
        FILE *dataFile = fopen("patients.txt", "r+");
        if (dataFile == NULL) {
                dataFile = fopen("patients.txt", "w+");
        }
        return dataFile;
}

void populatePatientNodesFromFile(FILE *file)
{
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file) != NULL) { // Read through the file line by line.
                {
                      char* token = strtok(line, "|");
                      int patientID = atoi(token); // The first data point is ID

                      token = strtok(NULL, "|"); // Move to next token
                      char* patientName = token;

                      token = strtok(NULL, "|");
                      int patientAge = atoi(token);

                      token = strtok(NULL, "|");
                      char* patientDiagnosis = token;

                      token = strtok(NULL, "|");
                      int patientRoomNum = atoi(token);

                      Patient newPatient;

                      newPatient.patientId = patientID;
                      strcpy(newPatient.name, patientName);
                      newPatient.age = patientAge;
                      newPatient.roomNumber = patientRoomNum;

                      add(&patientsList , newPatient);
                }
        }
}

void updateFile(FILE *file, Patient *p)
{
        //TODO
}