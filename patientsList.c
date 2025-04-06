#include <stdio.h>
#include <stdlib.h>

#include "patientsList.h"
#include "patient.h"

extern bool roomsOccupied[];

void add(PatientNodePtr *patientList, Patient patient)
{
        roomsOccupied[patient.roomNumber - 1] = true;

        // Allocate memory for the new node
        PatientNodePtr newNodePtr = malloc(sizeof(PatientNode));

        // Assign data to the new node and set 'next' to NULL
        newNodePtr->data = patient;
        newNodePtr->next = NULL;

        // If the list is empty, the new node becomes the head
        if (*patientList == NULL) {
                *patientList = newNodePtr;
                return;
        }

        // Traverse to the last node
        PatientNodePtr last = *patientList;
        while (last->next != NULL) {
                last = last->next;
        }

        // Point the 'next' of the last node to the new node
        last->next = newNodePtr;
}

void delete(PatientNodePtr *patientList, const int patientId)
{
        // temp initialized as pointer to the head node,
        // it will be traversed
        PatientNodePtr temp = *patientList;

        // If the head node itself is to be deleted
        if (temp != NULL && temp->data.patientId == patientId) {
                *patientList = temp->next;
                free(temp);
                return;
        }

        // Search for the patient to be deleted by ID
        PatientNodePtr prev = NULL;
        while (temp != NULL && temp->data.patientId != patientId) {
                prev = temp;
                temp = temp->next;
        }

        // If key was not present in list
        if (temp == NULL)
                return;

        // Unlink the node from linked list
        prev->next = temp->next;
        free(temp);
}

void forEach(PatientNodePtr patientList, void (*then)(Patient))
{
        PatientNodePtr head = patientList;
        while (head != NULL) {
                (*then)(head->data);
                head = head->next;
        }
}

PatientNodePtr search(PatientNodePtr patientList, const int patientId)
{
        PatientNodePtr current = patientList; // Initialize current
        while (current != NULL) {
                if (current->data.patientId == patientId)
                        return current;
                current = current->next;
        }
        return NULL;
}