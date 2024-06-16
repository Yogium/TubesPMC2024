//Nama : Nicholas Darren
//Nama file : deletePatient.c
//Deskripsi : Fungsi ini untuk menghapus pasien (dengan input ID)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "parsingDate.h"
#include "LinkedList.h"

int deletePatient(DataPasien** head, char* patientID) {
    if (*head == NULL) { // Bila linkedlist kosong
        printf("Linked list kosong.\n");
        return 0;
    }

    DataPasien* temp = *head;
    DataPasien* prev = NULL;

    // Cari node yang ingin didelete
    while (temp != NULL && strcmp(temp->patientID, patientID) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // Bila id tidak ditemukan
    if (temp == NULL) {
        printf("Pasien dengan ID '%s' tidak ditemukan.\n", patientID);
        return 0;
    }

    DataPasien* current = *head;
    int newIndex = 1;

    while (current != NULL) {
        if (current == temp) {
            // Skip node
            current = current->next;
            continue;
        }

        current->index = newIndex;
        newIndex++;
        current = current->next;
    }

    // Bila didelete head nodenya
    if (temp == *head) {
        *head = temp->next; //Jadi next node
    } else {
        prev->next = temp->next; // Link node sebelumnya ke temp
    }

    free(temp);
    printf("Pasien dengan ID '%s' sudah dihapus.\n", patientID);
    return 1;
}

// int main(){
//     DataPasien* patientHead = NULL;
//     deletePatient(&patientHead);
// }

