//Nama: Nicholas Darren
//Nama file: searchPatientDetails.c
//Deskripsi: mencari pasien dengan input ID dan mengeluarkan riwayat pasien
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

typedef struct DataPenyakit {
    char diagnosis[20];
    char tindakan[20];
    char tanggalControl[11];
    struct DataPenyakit* next;
} DataPenyakit;

typedef struct DataDiag {
    DataPenyakit* dataPenyakit;
    char nama[100];
    char patientID[11];    
} DataDiag;

//  Mencari detail pasien (parameter pasienHead kunjunganHead dan ID)
DataDiag* searchPatientDetails(DataPasien* pasienHead, DataKunjungan* kunjunganHead, char* patientID) {
    DataDiag* result = (DataDiag*)malloc(sizeof(DataDiag));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return NULL;
    }
    result->dataPenyakit = NULL;
    result->nama[0] = '\0';
    strcpy(result->patientID, patientID);

    DataPasien* tempPasien = pasienHead;
    DataKunjungan* tempKunjungan = kunjunganHead;

    // Cari data pasien di DataPasien
    while (tempPasien != NULL) {
        if (strcmp(tempPasien->patientID, patientID) == 0) {
            strcpy(result->nama, tempPasien->nama);
            break;
        }
        tempPasien = tempPasien->next;
    }

    if (strlen(result->nama) == 0) { //Bila pasien tidak ditemukan
        return result;
    }

    //Cari visit pasien di DataKunjungan
    DataPenyakit* lastVisit = NULL;
    while (tempKunjungan != NULL) {
        if (strcmp(tempKunjungan->patientID, patientID) == 0) {
            // Bikin node DataPenyakit setiap visitnya found
            DataPenyakit* newDataPenyakit = (DataPenyakit*)malloc(sizeof(DataPenyakit));
            if (newDataPenyakit == NULL) {
                fprintf(stderr, "Memory allocation failed!\n");
                exit(EXIT_FAILURE);
            }
            strcpy(newDataPenyakit->diagnosis, penyakit[tempKunjungan->diagnosis]);
            strcpy(newDataPenyakit->tindakan, tindakan[tempKunjungan->tindakan].nama);
            sprintf(newDataPenyakit->tanggalControl, "%02d-%02d-%04d", tempKunjungan->control.date, tempKunjungan->control.month, tempKunjungan->control.year);
            newDataPenyakit->next = NULL;

            if (lastVisit == NULL) {
                result->dataPenyakit = newDataPenyakit;
            } else {
                lastVisit->next = newDataPenyakit;
            }
            lastVisit = newDataPenyakit;
        }
        tempKunjungan = tempKunjungan->next;
    }

    return result;
}

void freeResult(DataDiag* result) {
    DataPenyakit* current = result->dataPenyakit;
    while (current != NULL) {
        DataPenyakit* next = current->next;
        free(current);
        current = next;
    }
    free(result);
}

// int main() {
//     DataPasien* pasienHead = NULL;
//     DataKunjungan* kunjunganHead = NULL;
//     char pasienID[11];
//     printf("Masukkan ID pasien untuk mencari: ");
//     fgets(pasienID, sizeof(pasienID), stdin);
//     pasienID[strcspn(pasienID, "\n")] = '\0';

//     DataDiag* result = searchPatientDetails(pasienHead, kunjunganHead, pasienID);

//     if (strlen(result->nama) == 0) {
//         printf("Pasien dengan ID '%s' tidak ditemukan.\n", pasienID);
//     } else {
//         printf("Nama: %s\n", result->nama);
//         printf("ID Pasien: %s\n", result->patientID);
//         DataPenyakit* temp = result->dataPenyakit;
//         if (temp == NULL) {
//             printf("Tidak ada data kunjungan untuk pasien dengan ID '%s'.\n", pasienID);
//         } else {
//             printf("Terdeteksi kunjungan dengan data dibawah:\n");
//             while (temp != NULL) {
//                 printf("Diagnosis: %s\n", temp->diagnosis);
//                 printf("Tindakan: %s\n", temp->tindakan);
//                 printf("Tanggal kontrol: %s\n", temp->tanggalControl);
//                 printf("\n");
//                 temp = temp->next;
//             }
//         }
//     }
// }
