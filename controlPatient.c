/*  Nama      : Kennard Benaya Manli
    Nama file : controlPatient.c
    Deskripsi : Fungsi untuk mencari pasien-pasien yang akan kontrol pada tanggal yang diinput
*/
//edited by: 13222050
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

date inputControlDate(char *stringDate);

// Fungsi untuk mencari pasien berdasarkan tanggal kontrol
ctrlist* findPatientsByControlDate(DataPasien* pasienHead, DataKunjungan* kunjunganHead, char *stringDate) {
    DataKunjungan* kunjunganTemp = kunjunganHead;
    DataPasien* pasienTemp = pasienHead;
    date controlDate = inputControlDate(stringDate);

    ctrlist* listhead = NULL;
    while(kunjunganTemp != NULL){
        if(kunjunganTemp->control.date == controlDate.date && kunjunganTemp->control.month == controlDate.month && kunjunganTemp->control.year == controlDate.year){
            DataPasien* pasienTemp = pasienHead;
            while(pasienTemp != NULL){
                if(strcmp(pasienTemp->patientID, kunjunganTemp->patientID) == 0){
                    ctrlist* newnode = (ctrlist*)malloc(sizeof(ctrlist));
                    strcpy(newnode->nama, pasienTemp->nama);
                    strcpy(newnode->patientID, pasienTemp->patientID);
                    newnode->next = NULL;
                    if(listhead == NULL){
                        listhead = newnode;
                    }
                    else{
                        ctrlist* temp = listhead;
                        while(temp->next != NULL){
                            temp = temp->next;
                        }
                        temp->next = newnode;
                    }
                }
                pasienTemp = pasienTemp->next;
            }
        }
        kunjunganTemp = kunjunganTemp->next;
    }
    return listhead;

}

// Fungsi untuk input tanggal dari pengguna
date inputControlDate(char *stringDate) {
    date controlDate;
    char *token = strtok(stringDate, "/");
    if(token != NULL){
        controlDate.date = atoi(token);
        token = strtok(NULL, "/");
        controlDate.month = atoi(token);
        token = strtok(NULL, "/");
        controlDate.year = atoi(token);
    }

    //printf("Masukkan tanggal kontrol (dd mm yyyy): ");
    //scanf("%d %d %d", &controlDate.date, &controlDate.month, &controlDate.year);

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