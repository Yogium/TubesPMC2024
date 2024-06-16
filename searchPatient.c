//Nama: Nicholas Darren
//Nama file: searchPatient.c
//Deskripsi: Fungsi ini search pasien berdasarkan nama nya (partial, case sensitive) atau ID nya

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "parsingDate.h"
#include "LinkedList.h"

void searchPatient(DataPasien* head) {
    int choice;
    char searchName[30];
    char searchID[11];
    DataPasien* temp;
    int found;

    printf("Pilih mode pencarian:\n");
    printf("1. Cari berdasarkan Nama\n");
    printf("2. Cari berdasarkan Patient ID\n");
    printf("Pilihan: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) { //Dibuat menu
        case 1: //Menggunakan nama
            printf("Masukkan nama atau bagian dari nama: ");
            fgets(searchName, sizeof(searchName), stdin);
            searchName[strcspn(searchName, "\n")] = '\0';

            found = 0;
            temp = head;
            while (temp != NULL) {
                if (strstr(temp->nama, searchName) != NULL) { // Case-sensitive partial menggunakan strstr yaitu fungsi yang sudah predefined di C
                    printf("Index: %d\n", temp->index);
                    printf("Nama: %s\n", temp->nama);
                    printf("Alamat: %s\n", temp->alamat);
                    printf("Kota: %s\n", temp->kota);
                    printf("Tempat Lahir: %s\n", temp->tempatLahir);
                    printf("Tanggal Lahir: %02d-%02d-%04d\n", temp->tgllahir.date, temp->tgllahir.month, temp->tgllahir.year);
                    printf("Umur: %d\n", temp->umur);
                    printf("BPJS: %s\n", temp->BPJS);
                    printf("Patient ID: %s\n", temp->patientID);
                    printf("\n");
                    found = 1;
                }
                temp = temp->next;
            }
            if (!found) { //Bila tidak ditemukan
                printf("Pasien dengan nama '%s' tidak ditemukan.\n", searchName);
            }
            break;

        case 2: //Menggunakan ID
            printf("Masukkan Patient ID: ");
            fgets(searchID, sizeof(searchID), stdin);
            searchID[strcspn(searchID, "\n")] = '\0';

            found = 0;
            temp = head;
            while (temp != NULL) {
                if (strcmp(temp->patientID, searchID) == 0) { // Case-sensitive menggunakan strcmp
                    printf("Index: %d\n", temp->index);
                    printf("Nama: %s\n", temp->nama);
                    printf("Alamat: %s\n", temp->alamat);
                    printf("Kota: %s\n", temp->kota);
                    printf("Tempat Lahir: %s\n", temp->tempatLahir);
                    printf("Tanggal Lahir: %02d-%02d-%04d\n", temp->tgllahir.date, temp->tgllahir.month, temp->tgllahir.year);
                    printf("Umur: %d\n", temp->umur);
                    printf("BPJS: %s\n", temp->BPJS);
                    printf("Patient ID: %s\n", temp->patientID);
                    printf("\n");
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!found) { //Bila ID tidak sesuai
                printf("Pasien dengan ID '%s' tidak ditemukan.\n", searchID);
            }
            break;

        default: //Diluar pilihan 1 atau 2
            printf("Pilihan tidak valid.\n");
    }
}

// int main() {
//     DataPasien* pasienHead = NULL;
//     searchPatient(pasienHead);
//     return 0;
// }
