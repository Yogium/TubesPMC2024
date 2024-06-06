//Nama : Nicholas Darren
//Nama file : addPatient.c
// Deskripsi : Fungsi ini untuk Menambahkan Pasien Baru
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "parsingDate.c"
#include "LinkedList.c"

date parseDate(char* dateString, char* original); //Deklarasi fungsi

void addPatient(DataPasien** head) {
    DataPasien* newNode = createDataPasienNode();

    printf("Masukkan data pasien:\n");
    
    printf("Index: ");
    scanf("%d", &newNode->index);

    printf("Nama: ");
    scanf(" %[^\n]s", newNode->nama);

    printf("Alamat: ");
    scanf(" %[^\n]s", newNode->alamat);

    printf("Kota: ");
    scanf(" %[^\n]s", newNode->kota);

    printf("Tempat Lahir: ");
    scanf(" %[^\n]s", newNode->tempatLahir);

    printf("Tanggal Lahir (dd mmm yyyy): ");
    char dateString[50];
    fgets(dateString, sizeof(dateString), stdin);
    dateString[strcspn(dateString, "\n")] = 0;
    char original[20];
    newNode->tgllahir = parseDate(dateString, original);

    printf("Umur: ");
    scanf("%d", &newNode->umur);

    printf("BPJS: ");
    scanf("%s", newNode->BPJS);

    printf("Patient ID: ");
    scanf("%s", newNode->patientID);

    // Add pasien baru
    insertDataPasienAtEnd(head, newNode); //fungsi ini pake yang dibuat El di linkedlist.c

    printf("Pasien berhasil ditambahkan!\n");
}

int main(){
    DataPasien* pasienHead = NULL;
    addPatient(&pasienHead);
}
