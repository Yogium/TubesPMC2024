#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct.h"
#include "LinkedList.c"

#include "modifyPatient.c"
#include "addPatient.c"
#include "deletePatient.c"

// #include "parsingDate.c"
#include "searchPatient.c"
#include "visit_manipulate.c"

int main() {
    DataPasien* pasienHead = NULL;
    DataKunjungan* kunjunganHead = NULL;

    // Membaca data pasien dari file
    parseDataPasienFromFile("Data_Pasien.csv", &pasienHead);
    printf("Data Pasien List:\n");
    printDataPasienList(pasienHead);

    // Membaca data kunjungan dari file
    parseDataKunjunganFromFile("Riwayat_Datang.csv", &kunjunganHead);
    printf("Data Kunjungan List:\n");
    printDataKunjunganList(kunjunganHead);

    // Selector

    int choice;
    do {
        printf("Pilih menu:\n");
        printf("1. Tambah Pasien\n");
        printf("2. Hapus Pasien\n");
        printf("3. Modifikasi Pasien\n");
        printf("4. Cari Pasien\n");
        printf("5. Kunjungan Pasien\n");
        printf("6. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addPatient(&pasienHead);
                break;
            case 2:
                deletePatient(&pasienHead);
                break;
            case 3:
                modifyPatient(&pasienHead);
                break;
            case 4:
                searchPatient(pasienHead);
                break;
            case 5:
                //visit_manipulate(&pasienHead, &kunjunganHead); / perlu selector
                break;
            case 6:
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 6);



  



    // Membebaskan memori dari linked list
    freeDataPasienList(pasienHead);
    freeDataKunjunganList(kunjunganHead);

    return 0;
}