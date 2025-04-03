//
// Hospital Management System
// Created by Justin Cardas and Felix Nguyen
//

#include <stdbool.h>
#include <stdio.h>

#include "main.h"
#include "patient.h"
#include "doctor.h"
#include "TUI.h"
#include "file.h"

int main()
{
        while (1) {
                clrscr();
                if (!mainMenu())
                        return 0;
                print("\nPress enter to return to menu...");
                getchar(); // Stops from progressing
        }
}

PatientNodePtr patientsList = NULL;

bool mainMenu()
{
        FILE *file = initializeFile();
        populatePatientNodesFromFile(file);

        println("Welcome to the hospital management system.");
        println("0. Exit");
        println("1. Add new patient");
        println("2. View all patient records");
        println("3. Search for a patient");
        println("4. Discharge a patient");
        println("5. Manage doctors schedule");

        int menuChoice;
        while (1) {
                print("Choice: ");
                if (!scand(&menuChoice))
                        continue;

                switch (menuChoice) {
                case 0:
                        println(CLR_SCREEN);
                        return false;
                case 1:
                        addPatient();
                        updateFile(file);
                        return true;
                case 2:
                        if (checkForPatients())
                                viewAllPatientRecords();
                        return true;
                case 3:
                        if (checkForPatients())
                                searchPatient();
                        return true;
                case 4:
                        if (checkForPatients()) {
                                dischargePatient();
                                updateFile(file);
                        }
                        return true;
                case 5:
                        manageDoctorSchedule();
                        return true;
                default:
                        invalidInput("Invalid choice.");
                }
        }
}
