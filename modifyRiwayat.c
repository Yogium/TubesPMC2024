//Nama: Nicholas Darren
//Nama file: modifyRiwayat.c
//Deskripsi: mengubah Riwayat kedatangan dengan input ID
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

date parseDate(char* dateString, char* original);

void modifyRiwayat(DataKunjungan* head) { // Loop menu sampai user press exit
    char idToModify[20];
    printf("Masukkan ID pasien yang ingin dimodif: ");
    fgets(idToModify, sizeof(idToModify), stdin);
    idToModify[strcspn(idToModify, "\n")] = 0;
    DataKunjungan* current = head;

    while (current != NULL) {
        if (strcmp(current->patientID, idToModify) == 0) { //Bila ID input sesuai
            int choice;
            do {
                printf("\nModifikasi riwayat dengan ID: %s\n", idToModify);
                printf("1. Ubah Tanggal\n");
                printf("2. Ubah Diagnosis\n");
                printf("3. Ubah Tindakan\n");
                printf("4. Ubah Tanggal kontrol \n");
                printf("5. Exit\n");
                printf("Masukkan angka: ");
                scanf("%d", &choice);
                getchar();

                switch (choice) { // Ini menu switch casenya
                    case 1: {
                        char newDate[50];
                        printf("Masukkan tanggal (dd mmm yyyy or dd-mmm-yy): ");
                        fgets(newDate, sizeof(newDate), stdin);
                        newDate[strcspn(newDate, "\n")] = 0;
                        char original[20];
                        current->tanggal = parseDate(newDate, original);
                        printf("Tanggal berhasil diganti");
                        break;
                    }
                    case 2: {
                        int newDiagnosis;
                        printf("Masukkan diagnosis (0: Dehidrasi, 1: Keseleo, 2: Masuk Angin, 3: Pusing): ");
                        scanf("%d", &newDiagnosis);
                        current->diagnosis = newDiagnosis;
                        printf("Diagnosis berhasil diganti");
                        break;
                    }
                    case 3: {
                        int newTindakan;
                        printf("Masukkan tindakan (0: Pendaftaran, 1: Pemeriksaan, 2: Vaksinasi, 3: Cek gula darah, 4: Pemasangan infus, 5: Pengobatan): ");
                        scanf("%d", &newTindakan);
                        current->tindakan = newTindakan;
                        printf("Tindakan berhasil diganti");
                        break;
                    }
                    case 4: {
                        char newControlDate[50];
                        printf("Masukkan tanggal kontrol (dd mmm yyyy or dd-mmm-yy): ");
                        fgets(newControlDate, sizeof(newControlDate), stdin);
                        newControlDate[strcspn(newControlDate, "\n")] = 0;
                        char original[20];
                        current->control = parseDate(newControlDate, original);
                        printf("Tanggal kontrol berhasil diganti");
                        break;
                    }
                    case 5: {
                        printf("Keluar.\n");
                        break;
                    }
                    default: {
                        printf("Invalid.\n");
                        break;
                    }
                }
            } while (choice != 5);
            return;
        }
        current = current->next;
    }

    printf("Pasien dengan ID %s tidak ditemukan.\n", idToModify);
}

int main() {
    DataKunjungan* kunjunganHead = NULL;
    modifyRiwayat(kunjunganHead);
    return 0;
}
