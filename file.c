//
// Created by Justin Cardas on 2025-04-03.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define PATIENTS_FILE "patients.txt"
#define REPORT_FILE "report.txt"

#include "file.h"
#include "patient.h"
#include "patientsList.h"

FILE *dataFile = NULL;
FILE *reportFile = NULL;

void initializeFiles()
{
        dataFile = fopen(PATIENTS_FILE, "r+");
        if (dataFile != NULL)
                populatePatients();
        reportFile = fopen(REPORT_FILE, "w");
}

extern PatientNodePtr patientsList;
extern PatientNodePtr patientsAdmittedToday;
extern PatientNodePtr patientsDischargedToday;

void populatePatients()
{
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), dataFile) !=
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
}

void savePatient(Patient patient)
{
        fprintf(dataFile, "%d|%s|%d|%s|%d\n", patient.patientId, patient.name,
                patient.age, patient.diagnosis, patient.roomNumber);
}

void savePatients()
{
        dataFile = fopen(PATIENTS_FILE, "w"); // Open in write mode to overwrite
        if (dataFile == NULL) {
                printf("Error opening file for overwriting\n");
                return;
        }
        forEach(patientsList, savePatient);
        fclose(dataFile); // Close file
}

void generateReportHeader()
{
        fprintf(reportFile, "%-5s\t %-10s\t %-3s\t %-20s\t %-5s\n", "ID",
                "Full Name", "Age", "Diagnosis", "Room Num");
}

void reportPatient(Patient p)
{
        fprintf(reportFile, "%-5d\t %-10.10s\t %-3d\t %-20.20s\t %-5d\n",
                p.patientId, p.name, p.age, p.diagnosis, p.roomNumber);
}

void generateSummaryReport()
{
        if (patientsAdmittedToday != NULL) {
                fprintf(reportFile, "Patients admitted today:\n");
                generateReportHeader();
                forEach(patientsAdmittedToday, reportPatient);
                fprintf(reportFile, "\n");
        }

        if (patientsDischargedToday != NULL) {
                fprintf(reportFile, "\n");
                fprintf(reportFile, "Patients discharged today:\n");
                generateReportHeader();
                forEach(patientsDischargedToday, reportPatient);
        }
}
