//
// Created by Justin Cardas and Felix Nguyen on 2025-02-08.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "hospital.h"
#include "patient.h"

#define CURSOR_UP "\x1b[A"
#define DAYS_PER_WEEK 7
#define SHIFTS_PER_DAY 3

// Global array of patients
Patient patients[MAX_PATIENTS];
int patientCount = 0;

char doctorsSchedule[DAYS_PER_WEEK][SHIFTS_PER_DAY][CHAR_BUFFER];

int main()
{
    int menu_choice;

    while (1)
    {
        printf("0. Exit\n");
        printf("1. Add new patient\n");
        printf("2. View all patient records\n");
        printf("3. Search for a patient\n");
        printf("4. Discharge a patient\n");
        printf("5. Manage Doctor Schedule\n");
        if (!scand(&menu_choice))
            continue;

        switch (menu_choice)
        {
        case 0:
            printf("Exiting...\n");
            return 0;
        case 1:
            addPatient();
            break;
        case 2:
            if (checkForPatients())
            {
                viewAllPatientRecords();
            }
            break;
        case 3:
            if (checkForPatients())
            {
                searchPatient();
            }
            break;
        case 4:
            if (checkForPatients())
            {
                dischargePatient();
            }
            break;

        case 5:
            {
                manageDoctorSchedule();
            }
            break;

        default:
            invalidInput("Invalid choice");
            break;
        }
        printf("Press enter to return to menu...\n");
        getchar(); // Stops from progressing
    }
}


void invalidInput(char message[])
{
    if (message == NULL)
        message = "Invalid input.";
    printf(CURSOR_UP);
    printf("%s\n", message);
}

bool scand(int* num)
{
    // Best case scenario: just a wrapper for scanf("%d")
    int itemsScanned = scanf("%d", num);

    // Input is not a valid if scanf fails to scan a number,
    // or there's still something in the input stream
    int c = getchar();
    bool valid = itemsScanned > 0 && (c == '\n' || c == EOF);

    // In that case,
    if (!valid)
    {
        // flush the input stream
        while ((c = getchar()) != '\n' && c != EOF);
        invalidInput("Input must be a number.");
    }

    return valid;
}

bool scandPositive(int* num)
{
    bool valid = scand(num);
    if (!valid)
        return false;
    if (*num < 0)
    {
        invalidInput("Number must be non-negative.");
        return false;
    }
    return true;
}

bool scans(char* str)
{
    fgets(str, CHAR_BUFFER, stdin);

    char* EOL = strchr(str, '\n');
    if (!EOL) // no EOL means buffer overflow

    {
        // clear the input stream
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    else
    {
        *EOL = '\0'; // Replace '\n' with '\0'
    }

    bool valid = strlen(str) > 0;
    if (!valid)
        printf(CURSOR_UP);
    return valid;
}

bool checkForPatients()
{
    if (patientCount <= 0)
    {
        printf("ERROR: No patients in system.\n");
        return false;
    }
    return true;
}

Patient* getPatientByID(int patientId)
{
    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].patient_id == patientId)
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
        printf("ERROR: Too many patients in system.\n");
        return;
    }

    Patient newPatient; // Call the new Patient.

    printf("Adding new patient...\n\n");

    while (1)
    {
        printf("Patient ID: ");
        if (scandPositive(&newPatient.patient_id))
            break;
    }

    if (getPatientByID(newPatient.patient_id) != NULL)
    {
        printf("ERROR: Patient ID already exists.\n");
        return;
    }


    while (1)
    {
        printf("Full name: ");
        if (scans(newPatient.full_name))
            break;
    }

    while (1)
    {
        printf("Age: ");
        if (scandPositive(&newPatient.age))
            break;
    }

    while (1)
    {
        printf("Diagnosis: ");
        if (scans(newPatient.diagnosis))
            break;
    }

    while (1)
    {
        printf("Room number: ");
        if (scandPositive(&newPatient.room_number))
            break;
    }

    // Finally, store the patient's record in the patients array, and update the patient count.
    patients[patientCount++] = newPatient;
    printf("Patient has been added successfully.\n");
}

// Function to print all the details of a patient at the passed index.
void printPatient(Patient* p)
{
    printf("%-10d\t %-10.10s\t %-3d\t %-10.10s\t %-10d\t\n",
           p->patient_id, p->full_name, p->age, p->diagnosis, p->room_number);
}

// Function to print the header containing the details of each patient.
void printPatientHeader()
{
    printf("%-10s\t %-10s\t %-3s\t %-10s\t %-10s\t\n",
           "ID", "Full Name", "Age", "Diagnosis", "Room Num");
}

void viewAllPatientRecords()
{
    printPatientHeader();
    for (int i = 0; i < patientCount; i++)
    {
        printPatient(&patients[i]);
    }
}

void searchPatient()
{
    int searchChoice;

    while (1)
    {
        printf("Search by:\n");
        printf("0. Nevermind; exit.\n");
        printf("1. ID\n");
        printf("2. Full Name\n");
        if (!scand(&searchChoice))
            continue;

        int searchID;
        char searchFullName[CHAR_BUFFER];
        switch (searchChoice)
        {
        case 0:
            return;
        case 1:
            while (1)
            {
                printf("Search ID: ");
                if (scandPositive(&searchID))
                    break;
            }
            searchPatientByID(searchID);
            return;
        case 2:
            while (1)
            {
                printf("Search full name: ");
                if (scans(searchFullName))
                    break;
            }
            searchPatientByName(searchFullName);
            return;
        default:
            invalidInput("Invalid choice.");
        }
    }
}

void searchPatientByID(int patientID)
{
    Patient* p = getPatientByID(patientID);
    if (p == NULL)
    {
        printf("Patient ID not found.\n");
        return;
    }
    printPatientHeader();
    printPatient(p);
}

void searchPatientByName(const char patient_name[CHAR_BUFFER])
{
    for (int i = 0; i < patientCount; i++)
    {
        if (strcmp(patients[i].full_name, patient_name) == 0)
        {
            printPatient(&patients[i]);
            return;
        }
    }
    printPatientHeader();
    printf("Patient name not found.\n");
}

void dischargePatient()
{
    int dischargeChoice;

    while (1)
    {
        printf("Discharge by:\n");
        printf("0. Nevermind; exit.\n");
        printf("1. ID\n");
        printf("2. Full Name\n");
        if (!scand(&dischargeChoice))
            continue;

        int dischargeID;
        char dischargeFullName[CHAR_BUFFER];
        switch (dischargeChoice)
        {
        case 0:
            return;
        case 1:
            while (1)
            {
                printf("ID: ");
                if (scandPositive(&dischargeID))
                    break;
            }
            dischargePatientByID(dischargeID);
            return;
        case 2:
            while (1)
            {
                printf("Full name: ");
                if (scans(dischargeFullName))
                    break;
            }
            dischargePatientByName(dischargeFullName);
            return;
        default:
            invalidInput("Invalid choice.");
        }
    }
}

void dischargePatientByID(int patientID)
{
    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].patient_id == patientID)
        {
            printf("Discharging patient: %s (ID: %d)\n", patients[i].full_name, patients[i].patient_id);

            // Shift remaining elements to the left
            for (int j = i; j < patientCount - 1; j++)
            {
                patients[j] = patients[j + 1];
            }

            patientCount--; // Reduce total patient count
            printf("Patient discharged successfully.\n");
            return; // Exit after discharging
        }
    }
    printf("No patient found with ID: %d\n", patientID);
}

void dischargePatientByName(const char patient_name[CHAR_BUFFER])
{
    for (int i = 0; i < patientCount; i++)
    {
        if (strcmp(patients[i].full_name, patient_name) == 0)
        {
            printf("Discharging patient: %s (ID: %d)\n", patients[i].full_name, patients[i].patient_id);

            // Shift remaining elements to the left
            for (int j = i; j < patientCount - 1; j++)
            {
                patients[j] = patients[j + 1];
            }

            patientCount--; // Reduce total patient count
            printf("Patient discharged successfully.\n");
            return; // Exit after discharging
        }
    }
    printf("No patient found with name: %s\n", patient_name);
}

void manageDoctorSchedule()
{
    int manageChoice;

    while (1)
    {
        printf("1. View Current Doctor Schedule\n");
        printf("2. Add to Doctor Schedule\n");
        if (!scand(&manageChoice))
            continue;

        switch (manageChoice)
        {
            case 1:
                printDoctorSchedule(doctorsSchedule);
            break;

            case 2:
                printScheduleChoices();
            break;
        }
    }
}
