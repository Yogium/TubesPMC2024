//Nama : Nicholas Darren
//Nama file : modifyPatient.c
// Deskripsi : Fungsi ini untuk mengubah data pasien dengan input ID dari user
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "parsingDate.h"

int modifyPatient(DataPasien** head, char* idToModify, char* newNama, char* newAlamat, char* newKota, char* newTempatLahir, char* newTglLahir, int newUmur, char* newBPJS) {
    DataPasien* temp = *head;

    while (temp != NULL && strcmp(temp->patientID, idToModify) != 0) {
        temp = temp->next;
    }

    if (temp != NULL) {
        if (strlen(newNama) > 0) {
            strcpy(temp->nama, newNama);
        }
        if (strlen(newAlamat) > 0) {
            strcpy(temp->alamat, newAlamat);
        }
        if (strlen(newKota) > 0) {
            strcpy(temp->kota, newKota);
        }
        if (strlen(newTempatLahir) > 0) {
            strcpy(temp->tempatLahir, newTempatLahir);
        }
        if (strlen(newTglLahir) > 0) {
            char originalDate[20];
            temp->tgllahir = parseDate(newTglLahir, originalDate);
            if (temp->tgllahir.date == 0 || temp->tgllahir.month == 0 || temp->tgllahir.year == 0) {
                printf("Invalid date format.\n");
                return 0;
            }
        }
        if (newUmur > 0) {
            temp->umur = newUmur;
        }
        if (strlen(newBPJS) > 0) {
            strcpy(temp->BPJS, newBPJS);
        }

        return 1;
    } else {
        return 0;
    }
}

// int main(){
//     DataPasien* pasienHead = NULL;
//     modifyPatient(&pasienHead);
//     return 0;
// }

