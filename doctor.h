//
// Created by felix on 2/17/25.
//

#ifndef DOCTOR_H
#define DOCTOR_H

#include "main.h"

#define DAYS_PER_WEEK 7
#define SHIFTS_PER_DAY 3

/**
 * @brief Initializes the schedule with empty strings.
 */
void initializeDoctorsSchedule();

/**
 * @brief Prints the doctors schedule, with filled values
 *
 * @param values Values to fill the schedule
 */
void printDoctorsSchedule(
        char values[DAYS_PER_WEEK][SHIFTS_PER_DAY][CHAR_BUFFER]);

/**
 * @brief Prints the doctors schedule as a menu choice.
 *
 * Cells are filled with numbers so that user can enter
 * a number to specify which timeslot they want to choose.
 */
void printScheduleChoices(void);

/**
 * @brief Menu function for managing the doctor weekly schedule.
 */
void manageDoctorSchedule();

/**
 * @brief Changes the doctors schedule.
 *
 * Prompts the user to enter which time slot they want to change,
 * and the name of the doctor to cover that shift.
 */
void changeDoctorSchedule();

#endif //DOCTOR_H
