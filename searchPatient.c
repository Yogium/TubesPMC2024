//Nama: Nicholas Darren
//Nama file: searchPatient.c
//Deskripsi: Fungsi ini search pasien berdasarkan nama nya (partial, case sensitive) atau ID nya

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "parsingDate.h"
#include "LinkedList.h"

DataPasien* createNodePasien(int index, char* nama, char* alamat, char* kota, char* tempatLahir, date tgllahir, int umur, char* BPJS, char* patientID) {
    DataPasien* newNode = (DataPasien*)malloc(sizeof(DataPasien));
    newNode->index = index;
    strcpy(newNode->nama, nama);
    strcpy(newNode->alamat, alamat);
    strcpy(newNode->kota, kota);
    strcpy(newNode->tempatLahir, tempatLahir);
    newNode->tgllahir = tgllahir;
    newNode->umur = umur;
    strcpy(newNode->BPJS, BPJS);
    strcpy(newNode->patientID, patientID);
    newNode->next = NULL;
    return newNode;
}

void addToLL(DataPasien** head, DataPasien* newNode) {
    DataPasien* temp = *head;
    if(temp == NULL) {
        *head = newNode;
        return;
    }
    else{
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    } 
}

DataPasien* searchPatient(DataPasien* head, char* input) {
    DataPasien* temp = head;
    int found = 0;
    DataPasien* foundPatientHead = NULL;

    // Cek apakah input dianggap sebagai ID
    if (strlen(input) >= 3 && input[0] == 'K' && input[1] == 'X' && input[2] == ' ') {
        while (temp != NULL) {
            if (strcmp(temp->patientID, input) == 0) {
                DataPasien* foundPatient = createNodePasien(temp->index, temp->nama, temp->alamat, temp->kota, temp->tempatLahir, temp->tgllahir, temp->umur, temp->BPJS, temp->patientID);
                addToLL(&foundPatientHead, foundPatient);
                found = 1;
            }
            temp = temp->next;
        }

        if (!found) {
            printf("Pasien dengan ID '%s' tidak ditemukan.\n", input);
        }
    } else {
        // Input dianggap sebagai nama
        char searchName[30];
        strcpy(searchName, input); // Salin input sebagai nama

        while (temp != NULL) {
            if (strstr(temp->nama, searchName) != NULL) {
                DataPasien* foundPatient = createNodePasien(temp->index, temp->nama, temp->alamat, temp->kota, temp->tempatLahir, temp->tgllahir, temp->umur, temp->BPJS, temp->patientID);
                addToLL(&foundPatientHead, foundPatient);
                found = 1;
            }
            temp = temp->next;
        }

        if (!found) {
            printf("Pasien dengan nama '%s' tidak ditemukan.\n", searchName);
        }
    }
    return foundPatientHead;
}

// int main() {
//     DataPasien* pasienHead = NULL;
//     DataPasien *foundPatientHead = NULL;
//     parseDataPasienFromFile("Data_Pasien.csv", &pasienHead);
//     printf("%s\n", pasienHead->patientID);
//     char entry[20];
//     scanf("%s", entry);
//     foundPatientHead = searchPatient(pasienHead, entry);
//     DataPasien* temp = foundPatientHead;
//     printf("%d\n", strlen(entry));
//     while (temp != NULL) {
//         printf("%s\n", temp->patientID);
//         temp = temp->next;
//     }
//     return 0;
// }
