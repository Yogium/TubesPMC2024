//Nama: Nicholas Darren
//Nama file: searchPatientDetails.c
//Deskripsi: mencari pasien dengan input ID dan mengeluarkan riwayat pasien
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

void searchPatientDetails(DataPasien* pasienHead, DataKunjungan* kunjunganHead) {
    char patientID[11];
    DataPasien* tempPasien = pasienHead;
    DataKunjungan* tempKunjungan = kunjunganHead;
    int foundPasien = 0;
    int foundKunjungan = 0;

    printf("Masukkan ID pasien untuk mencari: ");
    fgets(patientID, sizeof(patientID), stdin);
    patientID[strcspn(patientID, "\n")] = '\0';

    // Search for patient details in the DataPasien list
    while (tempPasien != NULL) {
        if (strcmp(tempPasien->patientID, patientID) == 0) {
            foundPasien = 1;
            printf("Nama: %s\n", tempPasien->nama);
            printf("ID Pasien: %s\n", tempPasien->patientID);
            break;
        }
        tempPasien = tempPasien->next;
    }

    // Search for patient details in the DataKunjungan list
    while (tempKunjungan != NULL) {
        if (strcmp(tempKunjungan->patientID, patientID) == 0) {
            if (!foundKunjungan) {
                printf("Terdeteksi kunjungan dengan data dibawah:\n");
            }
            foundKunjungan = 1;
            printf("Diagnosis: %s\n", penyakit[tempKunjungan->diagnosis]);
            printf("Tindakan: %s (Rp %d)\n", tindakan[tempKunjungan->tindakan].tindakan, tindakan[tempKunjungan->tindakan].biaya);
            printf("Tanggal kontrol: %02d-%02d-%04d\n", tempKunjungan->control.date, tempKunjungan->control.month, tempKunjungan->control.year);
            printf("\n");
        }
        tempKunjungan = tempKunjungan->next;
    }

    if (!foundPasien) {
        printf("Pasien dengan ID '%s' tidak ditemukan.\n", patientID);
    } else if (!foundKunjungan) {
        printf("Tidak ada data kunjungan untuk pasien dengan ID '%s'.\n", patientID);
    }
}

int main(){
    DataPasien* pasienHead = NULL;
    DataKunjungan* kunjunganHead = NULL;
    searchPatientDetails(pasienHead, kunjunganHead);
    return 0;
}
