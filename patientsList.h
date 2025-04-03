//
// Created by Justin Cardas on 2025-04-03.
//

#ifndef PATIENTSLIST_H
#define PATIENTSLIST_H

#include <stdbool.h>
#include "patient.h"

// Definition for a node in the linked list
typedef struct PatientNode {
        Patient data;              // Patient data stored in the node
        struct PatientNode *next;  // Pointer to the next node in the list
} PatientNode;


typedef PatientNode *PatientNodePtr;


/**
 * @brief Adds a patient to the linked list.
 *
 * This function adds a new patient to the end of the list. It dynamically allocates memory for the new node
 * and appends it to the list. If the list is empty, the new node becomes the head of the list.
 *
 * @param head A pointer to the head of the linked list.
 * @param patient The patient to be added.
 */
void add(PatientNode **head, Patient patient);

/**
 * @brief Deletes a patient from the linked list.
 *
 * This function deletes a patient node from the linked list based on the patient's ID. If the node is found,
 * it is removed and its memory is freed. If the patient is the head node, the head pointer is updated.
 *
 * @param head The head of the linked list.
 * @param patient The patient to be deleted.
 */
void delete(PatientNode *head, Patient patient);

/**
 * @brief Searches for a patient in the linked list.
 *
 * This function searches for a patient node in the list based on the patient's ID. It returns true if the
 * patient is found and false if the patient is not present in the list.
 *
 * @param head The head of the linked list.
 * @param patient The patient to search for.
 * @return bool True if the patient is found, false otherwise.
 */
bool search(PatientNode *head, Patient patient);

/**
 * @brief Prints all the patients in the linked list.
 *
 * This function iterates through the entire list and prints the name of each patient node.
 *
 * @param node The current node to print.
 */
void printList(PatientNode *node);

#endif // PATIENTSLIST_H
