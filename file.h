//
// Created by Justin Cardas on 2025-04-03.
//

#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include "patientsList.h"

/**
* @brief Initializes a file for reading and writing.
* @return A FILE* of the file to read
*/
FILE *initializeFile();

/**
* @brief Returns a pointer to a patient array after
* reading the file and parsing the data.
*
*/
PatientNodePtr populatePatientNodesFromFile(FILE *file);

/**
* @brief Updates the file with the current PatientArray.
*/
void updateFile(FILE *file);

void writePatientToFile(Patient patient);

#endif //FILE_H
