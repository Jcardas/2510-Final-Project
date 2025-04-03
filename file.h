//
// Created by Justin Cardas on 2025-04-03.
//

#include <stdio.h>
#include "patient.h"
#include "main.h"

#ifndef FILE_H
#define FILE_H

/**
* @brief Initializes a file for reading and writing.
* @return A FILE* of the file to read
*/
FILE* initializeFile();

/**
* @brief Returns a pointer to a patient array after
* reading the file and parsing the data.
*
*/
void populatePatientNodesFromFile(PatientNode patients, FILE * file);

/**
* @brief Updates the file with the current PatientArray.
*/
void updateFile(FILE * file, PatientNode patients);

#endif //FILE_H

