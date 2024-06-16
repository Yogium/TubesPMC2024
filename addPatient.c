//Nama : Nicholas Darren
//Nama file : addPatient.c
// Deskripsi : Fungsi ini untuk Menambahkan Pasien Baru
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "parsingDate.c"

//parameters sbg input
void addPatient(DataPasien** head, char* nama, char* alamat, char* kota, char* tempatLahir, char* tglLahir, int umur, char* BPJS, char* patientID) {
    DataPasien* newNode = createDataPasienNode();
    DataPasien* temp = *head;

    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }

    if (temp != NULL) {
        newNode->index = temp->index + 1; // Dimasukkan ke index + 1
    } 
    else {
        newNode->index = 1; // Bila linked list kosong, index = 1
    }

    strcpy(newNode->nama, nama);
    strcpy(newNode->alamat, alamat);
    strcpy(newNode->kota, kota);
    strcpy(newNode->tempatLahir, tempatLahir);

    char originalDate[20]; // Buffer untuk menyimpan tanggal yang sudah diformat
    newNode->tgllahir = parseDate(tglLahir, originalDate); // Memanggil parseDate untuk mendapatkan tanggal yang sudah diformat
    if (newNode->tgllahir.date == 0 || newNode->tgllahir.month == 0 || newNode->tgllahir.year == 0) {
        printf("Invalid date format.\n");
        free(newNode);
        return;
    }

    newNode->umur = umur;
    strcpy(newNode->BPJS, BPJS);
    strcpy(newNode->patientID, patientID);

    // Add the new patient node
    insertDataPasienAtEnd(head, newNode);

    printf("Pasien berhasil ditambahkan!\n");
}

int main() {
    DataPasien* pasienHead = NULL;


    char nama[50];
    char alamat[100];
    char kota[20];
    char tempatLahir[20];
    char tglLahir[20];
    int umur;
    char BPJS[20];
    char patientID[20];

    printf("Masukkan data pasien:\n");

    printf("Nama: ");
    scanf(" %[^\n]", nama);

    printf("Alamat: ");
    scanf(" %[^\n]", alamat);

    printf("Kota: ");
    scanf(" %[^\n]", kota);

    printf("Tempat Lahir: ");
    scanf(" %[^\n]", tempatLahir);

    printf("Tanggal Lahir (dd NamaBulan yyyy): ");
    scanf(" %[^\n]", tglLahir);

    printf("Umur: ");
    scanf("%d", &umur);
    while (getchar() != '\n');

    printf("BPJS: ");
    scanf(" %[^\n]", BPJS);

    printf("Patient ID: ");
    scanf(" %[^\n]", patientID);

    addPatient(&pasienHead, nama, alamat, kota, tempatLahir, tglLahir, umur, BPJS, patientID);

    return 0;
}
