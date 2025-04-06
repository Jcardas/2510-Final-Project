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
        dataFile = fopen(PATIENTS_FILE, "w+");
        if (dataFile == NULL) {
                perror("Error opening patients file");
                exit(EXIT_FAILURE);
        }

        populatePatients();

        reportFile = fopen(REPORT_FILE, "w");
        if (reportFile == NULL) {
                perror("Error opening report file");
                exit(EXIT_FAILURE);
        }
}

extern PatientNodePtr patientsList;
extern PatientNodePtr patientsAdmittedToday;
extern PatientNodePtr patientsDischargedToday;

extern bool roomsOccupied[];

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
        if (fprintf(dataFile, "%d|%s|%d|%s|%d\n", patient.patientId, patient.name,
                patient.age, patient.diagnosis, patient.roomNumber) < 0) {
            perror("Error writing to patients file");
        }
}

void savePatients()
{
        if (dataFile == NULL) {
                printf("Error opening file for overwriting\n");
                return;
        }
        forEach(patientsList, savePatient);
}

void generateReportHeader()
{
        if (fprintf(reportFile, "%-5s\t %-10s\t %-3s\t %-20s\t %-5s\n", "ID",
                "Full Name", "Age", "Diagnosis", "Room Num") < 0) {
            perror("Error writing report header");
        }
}

void reportPatient(Patient p)
{
        if (fprintf(reportFile, "%-5d\t %-10.10s\t %-3d\t %-20.20s\t %-5d\n",
                p.patientId, p.name, p.age, p.diagnosis, p.roomNumber) < 0) {
            perror("Error writing patient report");
        }
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
                fprintf(reportFile, "Patients discharged today:\n");
                generateReportHeader();
                forEach(patientsDischargedToday, reportPatient);
        }

        int count = 0;
        for (int i = 0; i < ROOMS_COUNT; ++i) {
                if (roomsOccupied[i]) {
                        ++count;
                }
        }
        if (fprintf(reportFile, "\nRooms occupied: %d/%d", count, ROOMS_COUNT) < 0) {
            perror("Error writing room occupancy report");
        }
}
