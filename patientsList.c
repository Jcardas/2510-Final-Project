#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "main.h"
#include "patient.h"

typedef struct PatientNode {
        Patient data;
        struct PatientNode *next;
} PatientNode;

typedef PatientNode *PatientNodePtr;

PatientNodePtr patientsList = NULL;

void add(PatientNode **head, Patient patient)
{
        // Allocate memory for the new node
        PatientNode *newNode = (PatientNode *)malloc(sizeof(PatientNode));
        if (newNode == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
        }

        // Assign data to the new node and set 'next' to NULL
        newNode->data = patient;
        newNode->next = NULL;

        // If the list is empty, the new node becomes the head
        if (*head == NULL) {
                *head = newNode;
                return;
        }

        // Traverse to the last node
        PatientNode *last = *head;
        while (last->next != NULL) {
                last = last->next;
        }

        // Point the 'next' of the last node to the new node
        last->next = newNode;
}

// Function to delete a node with a given key from the list
void delete(PatientNode *head, Patient patient)
{
        // Store head node
        PatientNode *temp = head, *prev = NULL;

        // If the head node itself contains the key to be deleted
        if (temp != NULL && temp->data.patientId == patient.patientId) {
                head = temp->next; // Changed head
                free(temp); // free old head
                return;
        }

        // Search for the key to be deleted, keep track of the
        // previous node as we need to change 'prev->next'
        while (temp != NULL && temp->data.patientId != patient.patientId) {
                prev = temp;
                temp = temp->next;
        }

        // If key was not present in list
        if (temp == NULL)
                return;

        // Unlink the node from linked list
        prev->next = temp->next;

        // Free memory
        free(temp);
}

// Function to search for a node with a given key in the list
bool search(PatientNode *head, Patient patient)
{
        PatientNode *current = head; // Initialize current
        while (current != NULL) {
                if (current->data.patientId == patient.patientId)
                        return true; // data found
                current = current->next;
        }
        return false; // data not found
}

// Function to print the linked list
void printList(PatientNode *node)
{
        while (node != NULL) {
                printf(" %s ", node->data.name);
                node = node->next;
        }
        printf("\n");
}
