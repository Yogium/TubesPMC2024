/*  Nama      : Kennard Benaya Manli
    Nama file : controlPatient.c
    Deskripsi : Fungsi untuk mencari pasien-pasien yang akan kontrol pada tanggal yang diinput
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "LinkedList.h"

typedef struct ctrlist{
    char nama[100];
    char patientID[11];
    struct ctrlist* next;
} ctrlist;

// Fungsi untuk mencari pasien berdasarkan tanggal kontrol
ctrlist* findPatientsByControlDate(DataPasien* pasienHead, DataKunjungan* kunjunganHead, date controlDate) {
    DataKunjungan* kunjunganTemp = kunjunganHead;
    DataPasien* pasienTemp = pasienHead;
    int found = 0;

    printf("\nPasien yang kontrol pada tanggal %d %d %d:\n", controlDate.date, controlDate.month, controlDate.year);

    ctrlist* ctrlistHead = NULL;

    while (kunjunganTemp != NULL) {
        if (kunjunganTemp->control.date == controlDate.date &&
            kunjunganTemp->control.month == controlDate.month &&
            kunjunganTemp->control.year == controlDate.year) {
                found = 1;
                //printf("ID Pasien: %s\n", kunjunganTemp->patientID); 
                if(ctrlistHead == NULL) {
                    ctrlistHead = (ctrlist*)malloc(sizeof(ctrlist));
                    strcpy(ctrlistHead->patientID, kunjunganTemp->patientID);
                    ctrlistHead->next = NULL;
                } else {
                    ctrlist* ctrlistTemp = ctrlistHead;
                    while(ctrlistTemp->next != NULL) {
                        ctrlistTemp = ctrlistTemp->next;
                    }
                    ctrlist* new = (ctrlist*)malloc(sizeof(ctrlist));
                    strcpy(new->patientID, kunjunganTemp->patientID);
                    new->next = NULL;

                    ctrlistTemp->next = new;
                }

            }
            return ctrlistHead;
    }

    // Cari nama pasien
    while(ctrlistHead != NULL) {
        while(ctrlistHead->nama[0] == '\0'){
            if(strcmp(ctrlistHead->patientID, pasienTemp->patientID) == 0){
                strcpy(ctrlistHead->nama, pasienTemp->nama);
                pasienTemp = pasienHead;//rewind temp
                break;
            }else{
                pasienTemp = pasienTemp->next;
            }
        }
    }
    if (!found) {
        printf("Tidak ada pasien yang kontrol pada tanggal tersebut.\n");
    }
    
    return ctrlistHead;
}

// Fungsi untuk input tanggal dari pengguna
date inputControlDate() {
    date controlDate;
    printf("Masukkan tanggal kontrol (dd mm yyyy): ");
    scanf("%d %d %d", &controlDate.date, &controlDate.month, &controlDate.year);

    return controlDate;
}

// Fungsi utama program
// int control() {
//     DataPasien* pasienHead = NULL;
//     DataKunjungan* kunjunganHead = NULL;

//     // Input tanggal dari pengguna
//     date controlDate = inputControlDate();

//     // Cari pasien yang kontrol pada tanggal yang diinput
//     ctrlist* listhead = findPatientsByControlDate(pasienHead, kunjunganHead, controlDate);
// }