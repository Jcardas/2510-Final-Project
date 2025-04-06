#include <stdio.h>
#include <string.h>

#include "main.h"
#include "doctor.h"
#include "TUI.h"
#include "file.h"
#include "scheduleFile.h"


char doctorsSchedule[DAYS_PER_WEEK][SHIFTS_PER_DAY][CHAR_BUFFER];
char daysOfWeek[][CHAR_BUFFER] = { "Monday",   "Tuesday", "Wednesday",
                                   "Thursday", "Friday",  "Saturday",
                                   "Sunday" };
char shiftsOfDay[][CHAR_BUFFER] = { "Morning", "Afternoon", "Evening" };

FILE* scheduleFile;

void manageDoctorSchedule()
{
        if(scheduleFile == NULL) {
                scheduleFile = initializeScheduleFile();
                initializeDoctorsSchedule(scheduleFile);
        }

        printf(CLR_SCREEN);
        println("Manage doctors schedule:");
        println("0. Nevermind; exit.");
        println("1. View schedule");
        println("2. Change chedule");

        int manageChoice;
        while (1) {
                print("Choice: ");
                if (!scand(&manageChoice))
                        continue;
                switch (manageChoice) {
                case 0:
                        return;
                case 1:
                        printDoctorsSchedule(doctorsSchedule);

                        // Update file
                        updateScheduleFile(scheduleFile);
                        return;
                case 2:
                        changeDoctorSchedule();

                        // Update file
                        updateScheduleFile(scheduleFile);
                        return;
                default:
                        invalidInput("Invalid choice.");
                }
        }
}

void initializeDoctorsSchedule(FILE* dataFile)
{
       dataFile = initializeScheduleFile();
        if (dataFile != NULL) {
                populateScheduleArrayFromFile(dataFile);
                fclose(dataFile);
        }
}

void printDoctorsSchedule(
        char values[DAYS_PER_WEEK][SHIFTS_PER_DAY][CHAR_BUFFER])
{
        // column header
        printf(CLR_LINE);
        printf("\t  | %-20s", shiftsOfDay[0]);
        for (int i = 1; i < SHIFTS_PER_DAY; ++i) {
                printf(" | %-20s", shiftsOfDay[i]);
        }
        printf(" |\n");

        // horizontal ruler
        for (int i = 0; i < 10; ++i) {
                printf("-");
        }
        printf("|");
        for (int j = 1; j <= SHIFTS_PER_DAY; ++j) {
                for (int i = 0; i < 22; ++i) {
                        printf("-");
                }
                printf("|");
        }
        printf("\n");

        // rows
        for (int i = 0; i < DAYS_PER_WEEK; ++i) {
                printf("%-9s |", daysOfWeek[i]);
                for (int j = 0; j < SHIFTS_PER_DAY; ++j) {
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
                        sprintf(choices[i][j], "%d",
                                i * SHIFTS_PER_DAY + j + 1);

        printDoctorsSchedule(choices);
}

void changeDoctorSchedule()
{
        printScheduleChoices();
        int choice;
        while (1) {
                print("Which shift do you want to change? ");
                if (scand(&choice)) {
                        if (choice >= 1 &&
                            choice <= DAYS_PER_WEEK * SHIFTS_PER_DAY)
                                break;
                        invalidInput("Invalid choice.");
                }
        }

        int index = choice - 1;
        int day = index / SHIFTS_PER_DAY;
        int shift = index % SHIFTS_PER_DAY;
        char *currentDoctor = doctorsSchedule[day][shift];
        char newDoctor[CHAR_BUFFER];

        println("You have chosen %s %s", daysOfWeek[day], shiftsOfDay[shift]);

        if (strlen(currentDoctor) > 0) {
                println("%s is the current doctor for this shift.",
                        currentDoctor);
                print("Replacement: ");
        } else {
                println("This shift is currently empty.");
                print("Doctor to cover this shift: ");
        }
        // newDoctor can be empty, which would mean no one covers that shift
        scans(newDoctor);
        // Assign doctor (or lack thereof) to the shift
        sprintf(doctorsSchedule[day][shift], "%s", newDoctor);

        // Print confirmation
        println("\nSchedule updated successfully.");
        printDoctorsSchedule(doctorsSchedule);
}
