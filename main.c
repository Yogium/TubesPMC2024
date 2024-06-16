#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct.h"
#include "LinkedList.h"

#include "modifyPatient.c"
#include "addPatient.c"
#include "deletePatient.c"

#include "parsingDate.h"
#include "searchPatient.c"
#include "visit_manipulate.c"
#include "cashflow.c"
#include "controlPatient.c"

int main() {
    DataPasien* pasienHead = NULL;
    DataKunjungan* kunjunganHead = NULL;

    // Membaca data pasien dari file
    parseDataPasienFromFile("Data_Pasien.csv", &pasienHead);
    printf("Data Pasien List:\n");
    

    // Membaca data kunjungan dari file
    parseDataKunjunganFromFile("Riwayat_Datang.csv", &kunjunganHead);
    printf("Data Kunjungan List:\n");

    // Selector

    int choice;
    do {
        printf("Pilih menu:\n");
        printf("1. Tambah Pasien\n");
        printf("2. Hapus Pasien\n");
        printf("3. Modifikasi Pasien\n");
        printf("4. Cari Pasien\n");
        printf("5. Cashflow\n");
        printf("6. Tambah Kunjungan\n");
        printf("7. Hapus Kunjungan\n");
        printf("8. Modifikasi Kunjungan\n");
        printf("9. Cari Kunjungan\n");
        printf("0. Keluar\n");
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
                cashflow(kunjunganHead);
                break;
            case 6:
                addVisitProcess(&kunjunganHead);
                break;  
            case 7:
                deleteVisit(&kunjunganHead);
                break;
            case 8:
                changeVisit(&kunjunganHead);
                break;
            case 9:
                searchVisitProcess(kunjunganHead);
                break;
            case 10:
                findPatientsByControlDate(pasienHead, kunjunganHead, inputControlDate());
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 0);




    // Membebaskan memori dari linked list
    freeDataPasienList(pasienHead);
    freeDataKunjunganList(kunjunganHead);

    return 0;
}