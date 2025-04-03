//
// Hospital Management System
// Created by Justin Cardas and Felix Nguyen
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

// Global array of patients
Patient patients[MAX_PATIENTS];
int patientCount = 0;

// Doctors schedule as a 2D array
char doctorsSchedule[DAYS_PER_WEEK][SHIFTS_PER_DAY][CHAR_BUFFER];
char daysOfWeek[][CHAR_BUFFER] = { "Monday",   "Tuesday", "Wednesday",
                                   "Thursday", "Friday",  "Saturday",
                                   "Sunday" };
char shiftsOfDay[][CHAR_BUFFER] = { "Morning", "Afternoon", "Evening" };

// ------------- Main menu -------------

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
                        if (checkForPatients())
                                dischargePatient();
                        return true;
                case 5:
                        manageDoctorSchedule();
                        return true;
                default:
                        invalidInput("Invalid choice.");
                }
        }
}
