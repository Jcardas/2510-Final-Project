//
// Created by felix on 2/17/25.
//

#ifndef HOSPITAL_H
#define HOSPITAL_H

#define DAYS_PER_WEEK 7
#define SHIFTS_PER_DAY 3
#define CHAR_BUFFER 50

/**
 * scanf("%d"), but also clears the input stream,
 * display an error message if input is invalid,
 * and returns success status.
 *
 * @return whether input is valid
 */
bool scand(int* num);

/**
 * scand, but the number must be positive.
 */
bool scandPositive(int* num);

/**
 * scanf("%s"), but also accepts multiple words,
 * and clears the input stream if there's buffer overflow.
 */
void scans(char* str);

/**
 * scans, plus but the input must be non-empty.
 *
 * @return whether input is non-empty
 */
bool scansNonEmpty(char* str);

/**
 * Displays an error message that the user input was invalid.
 */
void invalidInput(char message[]);

/**
 * Initializes the array with empty strings.
 */
void initializeDoctorsSchedule();

/**
 * Prints the
 */
void printDoctorsSchedule(char values[DAYS_PER_WEEK][SHIFTS_PER_DAY][CHAR_BUFFER]);

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
#endif //HOSPITAL_H
