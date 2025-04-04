//
// Created by Justin Cardas on 2025-04-03.
//

#ifndef SCHEDULEFILE_H
#define SCHEDULEFILE_H

#include <stdio.h>
#include "doctor.h"

/**
 * @brief Initializes the schedule file.
 *
 * Opens or creates the schedule file for storing doctor schedules.
 *
 * @return FILE* Pointer to the opened schedule file.
 */
FILE* initializeScheduleFile();

/**
 * @brief Populates the schedule array from the file.
 *
 * Reads the schedule data from the file and loads it into the doctorsSchedule array.
 *
 * @param dataFile Pointer to the schedule file.
 */
void populateScheduleArrayFromFile(FILE* dataFile);

/**
 * @brief Updates the schedule file.
 *
 * Writes the current schedule data back to the file.
 *
 * @param scheduleFile Pointer to the schedule file.
 */
void updateScheduleFile(FILE* scheduleFile);

#endif //SCHEDULEFILE_H
