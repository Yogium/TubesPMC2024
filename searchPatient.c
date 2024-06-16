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

void searchPatient(DataPasien* head, const char* input) {
    DataPasien* temp = head;
    int found = 0;

    // Cek apakah input dianggap sebagai ID
    if (strlen(input) >= 3 && input[0] == 'K' && input[1] == 'X' && input[2] == ' ') {
        char searchID[11];
        sscanf(input, "%s", searchID); // Baca string pertama sebagai ID

        while (temp != NULL) {
            if (strcmp(temp->patientID, searchID) == 0) {
                printf("Index: %d\n", temp->index);
                printf("Nama: %s\n", temp->nama);
                printf("Alamat: %s\n", temp->alamat);
                printf("Kota: %s\n", temp->kota);
                printf("Tempat Lahir: %s\n", temp->tempatLahir);
                printf("Tanggal Lahir: %02d-%02d-%04d\n", temp->tgllahir.date, temp->tgllahir.month, temp->tgllahir.year);
                printf("Umur: %d\n", temp->umur);
                printf("BPJS: %s\n", temp->BPJS);
                printf("Patient ID: %s\n", temp->patientID);
                printf("\n");
                found = 1;
                break;
            }
            temp = temp->next;
        }

        if (!found) {
            printf("Pasien dengan ID '%s' tidak ditemukan.\n", searchID);
        }
    } else {
        // Input dianggap sebagai nama
        char searchName[30];
        strcpy(searchName, input); // Salin input sebagai nama

        while (temp != NULL) {
            if (strstr(temp->nama, searchName) != NULL) {
                printf("Index: %d\n", temp->index);
                printf("Nama: %s\n", temp->nama);
                printf("Alamat: %s\n", temp->alamat);
                printf("Kota: %s\n", temp->kota);
                printf("Tempat Lahir: %s\n", temp->tempatLahir);
                printf("Tanggal Lahir: %02d-%02d-%04d\n", temp->tgllahir.date, temp->tgllahir.month, temp->tgllahir.year);
                printf("Umur: %d\n", temp->umur);
                printf("BPJS: %s\n", temp->BPJS);
                printf("Patient ID: %s\n", temp->patientID);
                printf("\n");
                found = 1;
            }
            temp = temp->next;
        }

        if (!found) {
            printf("Pasien dengan nama '%s' tidak ditemukan.\n", searchName);
        }
    }
}

// int main() {
//     DataPasien* pasienHead = NULL;
//     searchPatient(pasienHead);
//     return 0;
// }
