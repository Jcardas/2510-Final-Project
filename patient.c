#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "patient.h"
#include "file.h"
#include "TUI.h"
#include "patientsList.c"

bool checkForPatients()
{
        if (patientsList == NULL) {
                println("ERROR: No patients in system.");
                return false;
        }
        return true;
}

Patient *getPatientById(int patientId)
{
        PatientNodePtr node = search(patientsList, patientId);
        if (node == NULL) {
                return NULL;
        }
        return &node->data;
}

void addPatient()
{
        printf(CLR_SCREEN);
        println("Adding new patient...\n");

        Patient newPatient;
        while (1) {
                print("Patient ID: ");
                if (scandPositive(&newPatient.patientId))
                        break;
        }

        if (getPatientById(newPatient.patientId) != NULL) {
                println("ERROR: Patient already added.");
                return;
        }

        while (1) {
                print("Full name: ");
                if (scansNonEmpty(newPatient.name))
                        break;
        }

        while (1) {
                print("Age: ");
                if (scandPositive(&newPatient.age))
                        break;
        }

        while (1) {
                print("Diagnosis: ");
                if (scansNonEmpty(newPatient.diagnosis))
                        break;
        }

        while (1) {
                print("Room number: ");
                if (scandPositive(&newPatient.roomNumber))
                        break;
        }

        add(&patientsList, newPatient);
}

void printPatient(Patient p)
{
        println("%-5d\t %-10.10s\t %-3d\t %-20.20s\t %-5d", p.patientId, p.name,
                p.age, p.diagnosis, p.roomNumber);
}

void printPatientHeader()
{
        println("%-5s\t %-10s\t %-3s\t %-20s\t %-5s", "ID", "Full Name", "Age",
                "Diagnosis", "Room Num");
}

void viewAllPatientRecords()
{
        clrscr();
        println("All patient records:\n");
        printPatientHeader();
        forEach(patientsList, printPatient);
}

void searchPatient()
{
        clrscr();
        println("Search patient by:");
        println("0. Nevermind; exit.");
        println("1. ID");
        println("2. Full name");

        int searchChoice;
        while (1) {
                print("Choice: ");
                if (!scand(&searchChoice))
                        continue;

                switch (searchChoice) {
                case 0:
                        return;
                case 1:
                        searchPatientById();
                        return;
                case 2:
                        searchPatientByName();
                        return;
                default:
                        invalidInput("Invalid choice.");
                }
        }
}

Patient *searchPatientById()
{
        int patientId;
        while (1) {
                print("ID: ");
                if (scandPositive(&patientId))
                        break;
        }

        Patient *p = getPatientById(patientId);
        if (p == NULL) {
                println("Patient ID not found.");
                return NULL;
        }
        println("");
        printPatientHeader();
        printPatient(p);
        return p;
}

char searchedName[CHAR_BUFFER];
PatientNodePtr searchResults;

void matchName(Patient p)
{
        if (strcmp(p.name, searchedName) == 0) {
                add(&searchResults, p);
        }
}

void searchPatientByName()
{
        char name[CHAR_BUFFER];
        while (1) {
                print("Full name: ");
                if (scansNonEmpty(searchedName))
                        break;
        }

        searchResults = NULL;
        forEach(patientsList, matchName);

        if (searchResults != NULL) {
                printPatientHeader();
                forEach(searchResults, printPatient);
        } else {
                println("Patient name not found.");
        }
}

void dischargePatient()
{
        printf(CLR_SCREEN);
        println("Discharge patient by:");
        println("0. Nevermind; exit.");
        println("1. ID");
        println("2. Full Name");

        int dischargeChoice;
        while (1) {
                print("Choice: ");
                if (!scand(&dischargeChoice))
                        continue;

                switch (dischargeChoice) {
                case 0:
                        return;
                case 1:
                        dischargePatientById();
                        return;
                case 2:
                        dischargePatientByName();
                        return;
                default:
                        invalidInput("Invalid choice.");
                }
        }
}

void dischargePatientById()
{
        Patient *p = searchPatientById();
        if (p == NULL) {
                println("Patient ID not found.");
                return;
        }

        println("Patient discharged successfully.");
        delete (&patientsList, p->patientId);
}

void dischargePatientByName()
{
        searchPatientByName();

        if (searchResults == NULL)
                return;

        if (searchResults->next != NULL) {
                println("\nWhich one to discharge?");
                dischargePatientById();
                return;
        }

        delete(&patientsList, searchResults->data.patientId);
}