//Nama : Nicholas Darren
//Nama file : addPatient.c
// Deskripsi : Fungsi ini untuk Menambahkan Pasien Baru
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "parsingDate.c"

void addPatient(DataPasien** head) {
    DataPasien* newNode = createDataPasienNode();
    printf("Masukkan data pasien:\n");

    DataPasien* temp = *head;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }

    // Ini buat automatically assign index ke last index + 1
    if (temp != NULL) {
        newNode->index = temp->index + 1; // tambah 1 indexnya
    } else {
        newNode->index = 1; // Kalo linked list kosong, index =1
    }

    printf("Nama: ");
    scanf(" %[^\n]", newNode->nama);

    printf("Alamat: ");
    scanf(" %[^\n]", newNode->alamat);

    printf("Kota: ");
    scanf(" %[^\n]", newNode->kota);

    printf("Tempat Lahir: ");
    scanf(" %[^\n]", newNode->tempatLahir);

    int day, year;
    char monthName[20];
    int validDate = 0;
    while (!validDate) { // Loop until valid date is entered
        printf("Tanggal Lahir (dd NamaBulan yyyy): ");
        scanf("%d %s %d", &day, monthName, &year);

        // Validate month using getMonthNumber function
        int month = getMonthNumber(monthName);
        if (month > 0 && day > 0 && year > 0) {
            newNode->tgllahir.date = day;
            newNode->tgllahir.month = month;
            newNode->tgllahir.year = year;
            validDate = 1; // Break the loop if date input is valid
        } else {
            printf("Invalid. Masukkan ulang.\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }

    printf("Umur: ");
    scanf("%d", &newNode->umur);

    printf("BPJS: ");
    scanf("%s", newNode->BPJS);

    printf("Patient ID: ");
    scanf("%s", newNode->patientID);

    // Add pasien baru
    insertDataPasienAtEnd(head, newNode);

    printf("Pasien berhasil ditambahkan!\n");
}

int main(){
    DataPasien* pasienHead = NULL;
    addPatient(&pasienHead);
}
