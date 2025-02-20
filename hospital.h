//
// Created by felix on 2/17/25.
//

#ifndef HOSPITAL_H
#define HOSPITAL_H
#include "patient.h"

#endif //HOSPITAL_H

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
 * scand, plus a requirement that the number is positive.
 */
bool scandPositive(int* num);

/**
 * scanf("%s), but also accepts multiple words,
 * clear the input stream if there's buffer overflow.
 * and returns success status.
 *
 * @return whether input is non-empty
 */
bool scans(char* str);

/**
 * Displays an error message that the user input was invalid.
 */
void invalidInput(char message[]);
