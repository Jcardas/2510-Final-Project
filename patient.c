#include "patient.h"

bool checkForPatients()
{
        if (patientCount <= 0) {
                println("ERROR: No patients in system.");
                return false;
        }
        return true;
}

Patient *getPatientById(int patientId)
{
        for (int i = 0; i < patientCount; ++i) {
                if (patients[i].patientId == patientId) {
                        return &patients[i];
                }
        }
        return NULL;
}

void addPatient()
{
        if (patientCount >= MAX_PATIENTS) {
                println("ERROR: Too many patients in system.");
                return;
        }

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

        // Finally, store the patient's record in the patients array
        // and update the patient count.
        patients[patientCount++] = newPatient;
        println("\nThe following patient has been added:");
        printPatientHeader();
        printPatient(&newPatient);
}

void printPatient(Patient *p)
{
        println("%-5d\t %-10.10s\t %-3d\t %-20.20s\t %-5d", p->patientId,
                p->name, p->age, p->diagnosis, p->roomNumber);
}

void printPatientHeader()
{
        println("%-5s\t %-10s\t %-3s\t %-20s\t %-5s", "ID", "Full Name", "Age",
                "Diagnosis", "Room Num");
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

searchResults *searchPatientByName()
{
        char name[CHAR_BUFFER];
        while (1) {
                print("Full name: ");
                if (scansNonEmpty(name))
                        break;
        }

        searchResults *results = malloc(sizeof(searchResults));
        for (int i = 0; i < patientCount; ++i) {
                if (strcmp(patients[i].name, name) == 0)
                        results->matches[results->size++] = &patients[i];
        }

        if (results->size) {
                println("\n%d match%s:", results->size,
                        results->size > 1 ? "es" : "");
                printPatientHeader();
                for (int i = 0; i < results->size; ++i)
                        printPatient(results->matches[i]);
        } else {
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
        if (p == NULL)
                return;

        println("Patient discharged successfully.");
        // Shift remaining elements to the left
        for (int i = p - patients; i < patientCount - 1; ++i) {
                patients[i] = patients[i + 1];
        }
        --patientCount; // Reduce total patient count
}

void dischargePatientByName()
{
        searchResults *results = searchPatientByName();

        if (results->size == 0) {
                free(results);
                return;
        }
        if (results->size > 1) {
                free(results);
                println("\nWhich one to discharge?");
                dischargePatientById();
                return;
        }

        Patient *p = results->matches[0];
        // Shift remaining elements to the left
        for (int i = p - patients; i < patientCount - 1; ++i) {
                patients[i] = patients[i + 1];
        }
        --patientCount; // Reduce total patient count
        println("Patient discharged successfully.");
        free(results);
}
