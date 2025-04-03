//
// Created by Justin Cardas on 2025-04-03.
//

#ifndef PATIENTSLIST_H
#define PATIENTSLIST_H

#include "patient.h"

// Definition for a node in the linked list
typedef struct PatientNode {
        Patient data; // Patient data stored in the node
        struct PatientNode *next; // Pointer to the next node in the list
} PatientNode;

typedef PatientNode *PatientNodePtr;

/**
 * @brief Adds a patient to the linked list.
 *
 * This function adds a new patient to the end of the list. It dynamically allocates memory for the new node
 * and appends it to the list. If the list is empty, the new node becomes the head of the list.
 *
 * @param patientList a pointer to the linked list
 * @param patient The patient to be added.
 */
void add(PatientNodePtr *patientList, Patient patient);

/**
 * @brief Deletes a patient from the linked list.
 *
 * This function deletes a patient node from the linked list based on the patient's ID. If the node is found,
 * it is removed and its memory is freed. If the patient is the head node, the head pointer is updated.
 *
 * @param patientList pointer to the linked list
 * @param patient The patient to be deleted.
 */
void delete(PatientNodePtr *patientList, const int patientId);

/**
 * @brief Searches for a patient in the linked list.
 *
 * This function searches for a patient node in the list based on the patient's ID. It returns true if the
 * patient is found and false if the patient is not present in the list.
 *
 * @param patientList the linked list
 * @param patientId id of the patient ot search for
 * @return pointer to a patient node
 */
PatientNodePtr search(PatientNodePtr patientList, const int patientId);

/**
 * @brief Traverses the linked list and calls a callback function
 *
 * @param patientList the list
 * @param then a (Patient) -> () function
 */
void forEach(PatientNodePtr patientList, void (*then)(Patient));

#endif // PATIENTSLIST_H
