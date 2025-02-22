//
// Created by felix on 2/17/25.
//

#ifndef HOSPITAL_H
#define HOSPITAL_H

#define DAYS_PER_WEEK 7
#define SHIFTS_PER_DAY 3
#define CHAR_BUFFER 50

/**
 * @brief Runs the program's main menu.
 *
 * Prompts player to choose from the main menu
 * and takes corresponding action.
 *
 * @return Whether player wants to keep playing
 */
bool mainMenu();

/**
 * @brief Convenient wrapper for scanf("%d"),
 *
 * Clears the input stream,
 * display an error message if input is invalid,
 * and returns success status
 *
 * @return whether input is valid
 */
bool scand(int* num);

/**
 * @brief scand, but the number must be positive.
 */
bool scandPositive(int* num);

/**
 * @brief Convenient wrapper for fgets with error handling
 *
 * Clear the input stream if there is a buffer overflow,
 * and returns the success status.
 *
 * @return Whether there is a buffer overflow
 */
bool scans(char* str);

/**
 * @brief scans, but the input must be non-empty.
 *
 * @return whether input is non-empty
 */
bool scansNonEmpty(char* str);

/**
 * Convenient wrapper for printf.
 *
 * Clears the current line and prints.
 */
void print(const char* format, ...);

/**
 * Convenient wrapper for printf.
 *
 * Clears the current line and prints with an ending \n.
 */
void println(const char* format, ...);

/**
 * @brief Displays an error message that the user input was invalid.
 */
void invalidInput(char message[]);

/**
 * @brief Initializes the schedule with empty strings.
 */
void initializeDoctorsSchedule();

/**
 * @brief Prints the doctors schedule, with filled values
 *
 * @param values Values to fill the schedule
 */
void printDoctorsSchedule(char values[DAYS_PER_WEEK][SHIFTS_PER_DAY][CHAR_BUFFER]);


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
#endif //HOSPITAL_H
