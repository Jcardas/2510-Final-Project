//
// Created by Justin Cardas and Felix Nguyen on 2025-02-08.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "hospital.h"
#include "patient.h"

#define CURSOR_UP "\x1b[A"

// Global array of patients
Patient patients[MAX_PATIENTS];
int patientCount = 0;

char doctorsSchedule[DAYS_PER_WEEK][SHIFTS_PER_DAY][CHAR_BUFFER];

char daysOfWeek[][CHAR_BUFFER] = {
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat",
    "Sun"
};

char shiftsOfDay[][CHAR_BUFFER] = {
    "Morning",
    "Afternoon",
    "Evening"
};

int main()
{
    int menuChoice;
    while (1)
    {
        printf("0. Exit\n");
        printf("1. Add new patient\n");
        printf("2. View all patient records\n");
        printf("3. Search for a patient\n");
        printf("4. Discharge a patient\n");
        printf("5. Manage doctors schedule\n");
        if (!scand(&menuChoice))
            continue;

        switch (menuChoice)
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

    // Input is not valid if scanf fails to scan a number,
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


void scans(char* str)
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
}


bool scansNonEmpty(char* str)
{
    scans(str);
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
        printf("ERROR: Too many patients in system.\n");
        return;
    }

    Patient newPatient; // Call the new Patient.

    printf("Adding new patient...\n\n");

    while (1)
    {
        printf("Patient ID: ");
        if (scandPositive(&newPatient.patientId))
            break;
    }

    if (getPatientById(newPatient.patientId) != NULL)
    {
        printf("ERROR: Patient ID already exists.\n");
        return;
    }


    while (1)
    {
        printf("Full name: ");
        if (scansNonEmpty(newPatient.name))
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
        if (scansNonEmpty(newPatient.diagnosis))
            break;
    }

    while (1)
    {
        printf("Room number: ");
        if (scandPositive(&newPatient.roomNumber))
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
           p->patientId, p->name, p->age, p->diagnosis, p->roomNumber);
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
    for (int i = 0; i < patientCount; ++i)
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
                if (scansNonEmpty(searchFullName))
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
    Patient* p = getPatientById(patientID);
    if (p == NULL)
    {
        printf("Patient ID not found.\n");
        return;
    }
    printPatientHeader();
    printPatient(p);
}

void searchPatientByName(const char name[CHAR_BUFFER])
{
    for (int i = 0; i < patientCount; ++i)
    {
        if (strcmp(patients[i].name, name) == 0)
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
            dischargePatientById(dischargeID);
            return;
        case 2:
            while (1)
            {
                printf("Full name: ");
                if (scansNonEmpty(dischargeFullName))
                    break;
            }
            dischargePatientByName(dischargeFullName);
            return;
        default:
            invalidInput("Invalid choice.");
        }
    }
}

void dischargePatientById(int patientID)
{
    for (int i = 0; i < patientCount; ++i)
    {
        if (patients[i].patientId == patientID)
        {
            printf("Discharging patient: %s (ID: %d)\n", patients[i].name, patients[i].patientId);

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

void dischargePatientByName(const char name[CHAR_BUFFER])
{
    for (int i = 0; i < patientCount; ++i)
    {
        if (strcmp(patients[i].name, name) == 0)
        {
            printf("Discharging patient: %s (ID: %d)\n", patients[i].name, patients[i].patientId);

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
    printf("No patient found with name: %s\n", name);
}

void manageDoctorSchedule()
{
    printf("Managing doctors schedule...\n\n");
    int manageChoice;
    while (1)
    {
        printf("0. Nevermind; exit.\n");
        printf("1. View schedule\n");
        printf("2. Change chedule\n");
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
    printf("\t  %s", shiftsOfDay[0]);
    for (int i = 1; i < SHIFTS_PER_DAY; i++)
    {
        printf("\t\t   %s", shiftsOfDay[i]);
    }
    printf("\n");

    for (int i = 0; i < DAYS_PER_WEEK; ++i)
    {
        printf("%s\t", daysOfWeek[i]);
        for (int j = 0; j < SHIFTS_PER_DAY; j++)
        {
            printf("  %-22.20s", values[i][j]);
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
    int choice;
    while (1)
    {
        printScheduleChoices();
        printf("Which shift do you want to change? ");
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

    printf("You have chosen %s %s\n",
           daysOfWeek[day],
           shiftsOfDay[shift]);

    if (strlen(currentDoctor) > 0)
    {
        printf("%s is the current doctor for this shift.\n", currentDoctor);
        printf("Replacement: ");
    }
    else
    {
        printf("This shift is currently empty.\n");
        printf("Doctor to cover this shift: ");
    }
    scans(newDoctor); // can be empty, which would mean no one covers that shift
    sprintf(doctorsSchedule[day][shift], "%s", newDoctor);
}
