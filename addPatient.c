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

date parseDate(char* dateString, char* original);

void addPatient(DataPasien** head) {
    DataPasien* newNode = createDataPasienNode();
    printf("Masukkan data pasien:\n");

    DataPasien* temp = *head;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }

    //Ini buat automatically assign index ke last index + 1
    if (temp != NULL) {
        newNode->index = temp->index + 1; // tambah 1 indexnya
    } else {
        newNode->index = 1; // Kalo linked list kosong, index =1
    }

    printf("Nama: ");
    scanf(" %[^\n]s", newNode->nama);

    printf("Alamat: ");
    scanf(" %[^\n]s", newNode->alamat);

    printf("Kota: ");
    scanf(" %[^\n]s", newNode->kota);

    printf("Tempat Lahir: ");
    scanf(" %[^\n]s", newNode->tempatLahir);

    char dateString[50];
    int validDate = 0;
    while (!validDate) { // Dibikin agar wajibin user masukin tanggal yang valid, kalo ngga di loop nanti programnya error
        printf("Tanggal Lahir (dd mmm yyyy): ");
        fgets(dateString, sizeof(dateString), stdin);
        dateString[strcspn(dateString, "\n")] = 0;
        char original[20];
        newNode->tgllahir = parseDate(dateString, original);
        if (newNode->tgllahir.date > 0 && newNode->tgllahir.month > 0 && newNode->tgllahir.year > 0) {
            validDate = 1; // Jadi 1 and break the loop kalo valid
        } else {
            printf("Format tanggal tidak valid. Masukkan ulang.\n");
        }
    }

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
