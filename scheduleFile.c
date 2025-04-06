//
// Created by Justin Cardas on 2025-04-03.
//

#define SCHEDULE_FILE "scheduleFile.txt"
#define DAYS 21

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scheduleFile.h"
#include "doctor.h"

FILE* initializeScheduleFile()
{
        FILE* scheduleFile = fopen(SCHEDULE_FILE, "w+");
        if (scheduleFile == NULL) {
                perror("Error opening schedule file");
                exit(EXIT_FAILURE);
        }
        return scheduleFile;
}

extern char doctorsSchedule[DAYS_PER_WEEK][SHIFTS_PER_DAY][CHAR_BUFFER];

void populateScheduleArrayFromFile(FILE* dataFile)
{
        if (dataFile == NULL) {
                fprintf(stderr, "Error: data file is NULL\n");
                return;
        }

        char line[CHAR_BUFFER];
        int day = 0;
        int shift = 0;

        // Loop through all the lines in the file (21 lines in total)
        while (fgets(line, sizeof(line), dataFile) != NULL) {
                // Strip any leading/trailing whitespace or newlines
                line[strcspn(line, "\n")] = 0;  // Remove the newline character

                // If the line is not empty, assign it to the schedule
                if (strlen(line) > 0) {
                        // Calculate the day and shift based on the line number
                        int index = day * SHIFTS_PER_DAY + shift;
                        int d = index / SHIFTS_PER_DAY;
                        int s = index % SHIFTS_PER_DAY;

                        // Assign the doctor name to the schedule
                        sprintf(doctorsSchedule[d][s], "%s", line);
                }

                // Move to the next shift or day
                shift++;
                if (shift == SHIFTS_PER_DAY) {
                        shift = 0;
                        day++;
                }
        }
}

void updateScheduleFile(FILE* scheduleFile)
{
        for (int i = 0; i < DAYS_PER_WEEK; ++i) {
                for (int j = 0; j < SHIFTS_PER_DAY; ++j) {
                        if (fprintf(scheduleFile, "%s\n", doctorsSchedule[i][j]) < 0) {
                                perror("Error writing to file");
                                return;
                        }
                }
        }
}
