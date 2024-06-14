/*  Nama      : Nusaiba El Qonitat
    Nama file : controlPatient.c
    Deskripsi : Fungsi untuk mencari pasien-pasien yang akan kontrol pada tanggal yang diinput
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "LinkedList.c"

// Fungsi untuk mencari pasien berdasarkan tanggal kontrol
void findPatientsByControlDate(DataPasien* pasienHead, DataKunjungan* kunjunganHead, date controlDate, char* original) {
    DataKunjungan* kunjunganTemp = kunjunganHead;
    int found = 0;

    printf("\nPasien yang kontrol pada tanggal %s:\n", original);

    while (kunjunganTemp != NULL) {
        if (kunjunganTemp->control.date == controlDate.date &&
            kunjunganTemp->control.month == controlDate.month &&
            kunjunganTemp->control.year == controlDate.year) {

            DataPasien* pasienTemp = pasienHead;
            while (pasienTemp != NULL) {
                if (strcmp(pasienTemp->patientID, kunjunganTemp->patientID) == 0) {
                    printf("Nama: %s\n", pasienTemp->nama);
                    printf("Patient ID: %s\n\n", pasienTemp->patientID);
                    found = 1;
                    break;
                }
                pasienTemp = pasienTemp->next;
            }
        }
        kunjunganTemp = kunjunganTemp->next;
    }

    if (!found) {
        printf("Tidak ada pasien yang kontrol pada tanggal tersebut.\n");
    }
}

// Fungsi untuk input tanggal dari pengguna
date inputControlDate(char* original) {
    char inputDate[20];
    printf("Masukkan tanggal kontrol (dd mm yyyy): ");
    fgets(inputDate, sizeof(inputDate), stdin);
    inputDate[strcspn(inputDate, "\n")] = '\0';

    date controlDate;

    // Mem-parsing tanggal dari string inputDate
    if (sscanf(inputDate, "%d %d %d", &controlDate.date, &controlDate.month, &controlDate.year) != 3) {
        fprintf(stderr, "Format tanggal tidak valid. Gunakan format dd mm yyyy.\n");
        exit(EXIT_FAILURE);
    }

    // Melakukan validasi tanggal yang diinput
    if (controlDate.date < 1 || controlDate.date > 31 || controlDate.month < 1 || controlDate.month > 12 || controlDate.year < 1900) {
        fprintf(stderr, "Tanggal tidak valid.\n");
        exit(EXIT_FAILURE);
    }

    sprintf(original, "%02d-%02d-%04d", controlDate.date, controlDate.month, controlDate.year);

    return controlDate;
}

// Fungsi utama program
int main() {
    DataPasien* pasienHead = NULL;
    DataKunjungan* kunjunganHead = NULL;

    // Input tanggal dari pengguna
    char original[20];
    date controlDate = inputControlDate(original);

    // Cari pasien yang kontrol pada tanggal yang diinput
    findPatientsByControlDate(pasienHead, kunjunganHead, controlDate, original);
}