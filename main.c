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

FILE *patientFile;

int main()
{
        initializeFiles();

        while (1) {
                clrscr();
                if (!mainMenu())
                        break;
                print("\nPress enter to return to menu...");
                getchar(); // Stops from progressing
        }

        generateSummaryReport();
        return 0;
}

bool mainMenu()
{
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
                        savePatients();
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
                                savePatients();
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
