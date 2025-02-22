//
// Created by Justin Cardas and Felix Nguyen on 2025-02-08.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "hospital.h"
#include "patient.h"

// ANSI escape codes to manipulate the terminal
#define CURSOR_UP "\x1b[A\r"
#define CLR_LINE "\33[2K\r"
#define CLR_SCREEN "\033c"

// Global array of patients
Patient patients[MAX_PATIENTS];
int patientCount = 0;

// Doctors schedule as a 2D array
char doctorsSchedule[DAYS_PER_WEEK][SHIFTS_PER_DAY][CHAR_BUFFER];
char daysOfWeek[][CHAR_BUFFER] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};
char shiftsOfDay[][CHAR_BUFFER] = {
    "Morning",
    "Afternoon",
    "Evening"
};

// ------------- Main menu -------------

int main()
{
    while (1)
    {
        printf(CLR_SCREEN);
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
    while (1)
    {
        print("Choice: ");
        if (!scand(&menuChoice))
            continue;

        switch (menuChoice)
        {
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
            invalidInput("Invalid choice");
        }
    }
}

// ------------- IO & Input validation -------------

bool scans(char* str)
{
    fgets(str, CHAR_BUFFER, stdin);

    // Find the pointer to the newline character
    char* EOL = strchr(str, '\n');
    if (EOL)
    {
        *EOL = '\0'; // Replace '\n' with '\0'
        return true;
    }

    // If not found, it means user entered more characters than allowed
    // Clear the input stream
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    // Print error message
    char errorMessage[CHAR_BUFFER];
    sprintf(errorMessage, "Maximum %d characters allowed.", CHAR_BUFFER);
    invalidInput(errorMessage);
    return false;
}

bool scansNonEmpty(char* str)
{
    if (!scans(str))
        return false;
    if (strlen(str) > 0)
        return true;
    printf(CURSOR_UP);
    return false;
}

bool scand(int* num)
{
    // Use scans and convert it to int instead of scanf("%d),
    // because the former can handle empty input.

    char input[CHAR_BUFFER];
    if (!scansNonEmpty(input))
        return false;

    char* endptr;
    *num = strtol(input, &endptr, 10);
    if (*endptr == '\0')
        return true;
    invalidInput("Input must be a number.");
    return false;
}

bool scandPositive(int* num)
{
    if (!scand(num))
        return false;
    if (*num >= 0)
        return true;
    invalidInput("Number must be non-negative.");
    return false;
}

void print(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    printf(CLR_LINE);
    vprintf(format, args);
    va_end(args);
}

void println(const char* format, ...)
{
    print(format);
    printf("\n");
}

void invalidInput(char message[])
{
    if (message == NULL)
        message = "Invalid input.";
    printf(CLR_LINE);
    printf(message);
    printf(CURSOR_UP);
    printf(CLR_LINE);
}

// ------------- Patients -------------

bool checkForPatients()
{
    if (patientCount <= 0)
    {
        println("ERROR: No patients in system.");
        return false;
    }
    return true;
}

Patient* getPatientById(int patientId)
{
    for (int i = 0; i < patientCount; ++i)
    {
        if (patients[i].patientId == patientId)
        {
            return &patients[i];
        }
    }
    return NULL;
}

void addPatient()
{
    if (patientCount >= MAX_PATIENTS)
    {
        println("ERROR: Too many patients in system.");
        return;
    }

    printf(CLR_SCREEN);
    println("Adding new patient...\n");

    Patient newPatient;
    while (1)
    {
        print("Patient ID: ");
        if (scandPositive(&newPatient.patientId))
            break;
    }

    if (getPatientById(newPatient.patientId) != NULL)
    {
        println("ERROR: Patient already added.");
        return;
    }

    while (1)
    {
        print("Full name: ");
        if (scansNonEmpty(newPatient.name))
            break;
    }

    while (1)
    {
        print("Age: ");
        if (scandPositive(&newPatient.age))
            break;
    }

    while (1)
    {
        print("Diagnosis: ");
        if (scansNonEmpty(newPatient.diagnosis))
            break;
    }

    while (1)
    {
        print("Room number: ");
        if (scandPositive(&newPatient.roomNumber))
            break;
    }

    // Finally, store the patient's record in the patients array, and update the patient count.
    patients[patientCount++] = newPatient;
    println("\nThe following patient has been added:");
    printPatientHeader();
    printPatient(&newPatient);
}

void printPatient(Patient* p)
{
    println("%-5d\t %-10.10s\t %-3d\t %-20.20s\t %-5d",
            p->patientId, p->name, p->age, p->diagnosis, p->roomNumber);
}

void printPatientHeader()
{
    println("%-5s\t %-10s\t %-3s\t %-20s\t %-5s",
            "ID", "Full Name", "Age", "Diagnosis", "Room Num");
}

void viewAllPatientRecords()
{
    printf(CLR_SCREEN);
    println("All patient records:\n");
    printPatientHeader();
    for (int i = 0; i < patientCount; ++i)
        printPatient(&patients[i]);
}

void searchPatient()
{
    printf(CLR_SCREEN);
    println("Search patient by:");
    println("0. Nevermind; exit.");
    println("1. ID");
    println("2. Full name");

    int searchChoice;
    while (1)
    {
        print("Choice: ");
        if (!scand(&searchChoice))
            continue;

        switch (searchChoice)
        {
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

Patient* searchPatientById()
{
    int patientId;
    while (1)
    {
        print("ID: ");
        if (scandPositive(&patientId))
            break;
    }

    Patient* p = getPatientById(patientId);
    if (p == NULL)
    {
        println("Patient ID not found.");
        return NULL;
    }
    println("Search result:");
    printPatientHeader();
    printPatient(p);
    return p;
}

searchResults* searchPatientByName()
{
    char name[CHAR_BUFFER];
    while (1)
    {
        print("Full name: ");
        if (scansNonEmpty(name))
            break;
    }

    searchResults* results = malloc(sizeof(searchResults));
    for (int i = 0; i < patientCount; ++i)
    {
        if (strcmp(patients[i].name, name) == 0)
            results->matchedIndices[results->matches++] = i;
    }

    if (results->matches)
    {
        println("%d match%s:",
                results->matches,
                results->matches > 1 ? "es" : "");
        printPatientHeader();
        for (int i = 0; i < results->matches; ++i)
            printPatient(&patients[results->matchedIndices[i]]);
    }
    else
    {
        println("Patient name not found.");
    }
    return results;
}

void dischargePatient()
{
    printf(CLR_SCREEN);
    println("Discharge patient by:");
    println("0. Nevermind; exit.");
    println("1. ID");
    println("2. Full Name");

    int dischargeChoice;
    while (1)
    {
        print("Choice: ");
        if (!scand(&dischargeChoice))
            continue;

        switch (dischargeChoice)
        {
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
    int patientId;
    while (1)
    {
        print("ID: ");
        if (scandPositive(&patientId))
            break;
    }

    for (int i = 0; i < patientCount; ++i)
    {
        if (patients[i].patientId == patientId)
        {
            println("\nThe following patient has been discharged:");
            printPatientHeader();
            printPatient(&patients[i]);
            // Shift remaining elements to the left
            for (int j = i; j < patientCount - 1; j++)
            {
                patients[j] = patients[j + 1];
            }
            patientCount--; // Reduce total patient count
            return; // Exit after discharging
        }
    }
    println("Patient ID not found.");
}

void dischargePatientByName()
{
    searchResults* results = searchPatientByName();

    if (results->matches == 0)
        return;
    if (results->matches > 1)
    {
        println("Which one to discharge?");
        dischargePatientById();
        return;
    }

    // Shift remaining elements to the left
    for (int i = results->matchedIndices[0]; i < patientCount - 1; i++)
    {
        patients[i] = patients[i + 1];
    }
    --patientCount; // Reduce total patient count
    println("Patient discharged successfully.");
}

// ------------- Doctors stuff -------------

void manageDoctorSchedule()
{
    printf(CLR_SCREEN);
    println("Manage doctors schedule:");
    println("0. Nevermind; exit.");
    println("1. View schedule");
    println("2. Change chedule");

    int manageChoice;
    while (1)
    {
        print("Choice: ");
        if (!scand(&manageChoice))
            continue;
        switch (manageChoice)
        {
        case 0:
            return;
        case 1:
            printDoctorsSchedule(doctorsSchedule);
            return;
        case 2:
            changeDoctorSchedule();
            return;
        default:
            invalidInput("Invalid choice.");
        }
    }
}

void initializeDoctorsSchedule()
{
    for (int i = 0; i < DAYS_PER_WEEK; i++)
    {
        for (int j = 0; j < SHIFTS_PER_DAY; j++)
        {
            sprintf(doctorsSchedule[i][j], "%s", "");
        }
    }
}

void printDoctorsSchedule(char values[DAYS_PER_WEEK][SHIFTS_PER_DAY][CHAR_BUFFER])
{
    // column header
    printf(CLR_LINE);
    printf("\t  | %-20s", shiftsOfDay[0]);
    for (int i = 1; i < SHIFTS_PER_DAY; i++)
    {
        printf(" | %-20s", shiftsOfDay[i]);
    }
    printf(" |\n");

    // horizontal ruler
    for (int i = 0; i < 10; ++i)
    {
        printf("-");
    }
    printf("|");
    for (int j = 1; j <= SHIFTS_PER_DAY; j++)
    {
        for (int i = 0; i < 22; ++i)
        {
            printf("-");
        }
        printf("|");
    }
    printf("\n");

    // rows
    for (int i = 0; i < DAYS_PER_WEEK; ++i)
    {
        printf("%-9s |", daysOfWeek[i]);
        for (int j = 0; j < SHIFTS_PER_DAY; j++)
        {
            printf(" %-20.20s |", values[i][j]);
        }
        printf("\n");
    }
}

void printScheduleChoices(void)
{
    char choices[DAYS_PER_WEEK][SHIFTS_PER_DAY][CHAR_BUFFER];

    for (int i = 0; i < DAYS_PER_WEEK; ++i)
        for (int j = 0; j < SHIFTS_PER_DAY; ++j)
            sprintf(choices[i][j], "%d", i * SHIFTS_PER_DAY + j + 1);

    printDoctorsSchedule(choices);
}

void changeDoctorSchedule()
{
    printScheduleChoices();
    int choice;
    while (1)
    {
        print("Which shift do you want to change? ");
        if (scand(&choice))
        {
            if (choice >= 1 && choice <= DAYS_PER_WEEK * SHIFTS_PER_DAY)
                break;
            invalidInput("Invalid choice.");
        }
    }

    int index = choice - 1;
    int day = index / SHIFTS_PER_DAY;
    int shift = index % SHIFTS_PER_DAY;
    char* currentDoctor = doctorsSchedule[day][shift];
    char newDoctor[CHAR_BUFFER];

    println("You have chosen %s %s",
            daysOfWeek[day],
            shiftsOfDay[shift]);

    if (strlen(currentDoctor) > 0)
    {
        println("%s is the current doctor for this shift.", currentDoctor);
        print("Replacement: ");
    }
    else
    {
        println("This shift is currently empty.");
        print("Doctor to cover this shift: ");
    }
    scans(newDoctor); // can be empty, which would mean no one covers that shift
    // assign doctor (or lack thereof) to the shift
    sprintf(doctorsSchedule[day][shift], "%s", newDoctor);
    // print confirmation
    println("\nSchedule updated successfully.");
    printDoctorsSchedule(doctorsSchedule);
}
