//
// Created by justi on 2025-02-17.
//

#ifndef PATIENT_H
#define PATIENT_H

#define MAX_PATIENTS 50

#include "hospital.h"

typedef struct
{
    int patient_id;
    char full_name[CHAR_BUFFER];
    int age;
    char diagnosis[CHAR_BUFFER];
    int room_number;
} Patient;

/**
 * Gets a patient by id.
 * @param patientId patient's id
 * @return pointer to a Patient, NULL if not found
 */
Patient* getPatientByID(int patientId);

/**
 * @brief Adds a new patient record to the system.
 *
 * Prompts the user for patient details, id, full name, age, diagnosis,
 * and room number, and stores the information in the patient records array.
 */
void addPatient();

/**
 * @brief Prints a patient record.
 *
 * This function prints the patient's details in a formatted output.
 *
 * @param p pointer to patient
 */
void printPatient(Patient* p);

/**
 * @brief Deletes a patient record at the specified index in the patients array.
 *
 * This function removes the patient at the given index and shifts the subsequent records
 * to fill the gap, reducing the total patient count.
 *
 * @param i The index of the patient to delete.
 */
void deletePatient(int i);

/**
 * @brief Displays all patient records.
 *
 * Iterates through the list of stored patients and prints their details,
 * including ID, name, age, diagnosis, and room number.
 */
void viewAllPatientRecords();

/**
 * @brief Prompts the user to search for a patient.
 *
 * This function presents the user with an option to search for a patient by either their ID
 * or full name. It calls the appropriate search function based on the user's choice.
 */
void searchPatient();

/**
 * @brief Searches for a patient by their unique ID.
 *
 * @param patient_id The unique identifier of the patient.
 *
 * If a patient with the given ID exists, their details are displayed.
 * Otherwise, a message is printed indicating that no such patient was found.
 */
void searchPatientByID(int patient_id);

/**
 * @brief Searches for a patient by their name.
 *
 * @param patient_name The full name of the patient to search for.
 *
 * If a patient with the given name exists, their details are displayed.
 * If multiple patients have the same name, all matching records are shown.
 * If no match is found, an appropriate message is displayed.
 */
void searchPatientByName(const char patient_name[CHAR_BUFFER]);


/**
 * @brief Prompts the user to discharge a patient by either their ID or Name.
 *
 * This function presents the user with an option to discharge a patient by either their unique ID
 * or their full name. It calls the appropriate discharge function based on the user's choice.
 */
void dischargePatient();

/**
 * @brief Discharges a patient by their unique ID.
 *
 * @param patient_id The unique identifier of the patient to be discharged.
 *
 * Removes the patient record from the system if found. If no patient
 * with the given ID exists, an error message is displayed.
 */
void dischargePatientByID(int patient_id);

/**
 * @brief Discharges a patient by their name.
 *
 * @param patient_name The name of the patient to be discharged.
 *
 * If multiple patients share the same name, the user may be prompted
 * to confirm which patient to remove. If no patient
 * with the given Name exists, an error message is displayed.
 */
void dischargePatientByName(const char* patient_name);

/**
 * @brief Checks if there are any patients in the system.
 *
 * This function verifies if there are any patients stored in the system by checking the patient count.
 * It returns `true` if there are patients, and `false` if there are none.
 *
 * @return bool True if there are patients, false if there aren't.
 */
bool checkForPatients();

/**
 * @breif Menu function for managing the doctor weekly schedule.
 *
 */
void manageDoctorSchedule();

#endif //PATIENT_H
