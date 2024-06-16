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

void searchPatient(DataPasien* head, const char* input) {
    DataPasien* temp = head;
    int found = 0;

    // Cek apakah input dianggap sebagai ID (asumsikan ID diawali dengan "KX ")
    if (strlen(input) >= 3 && input[0] == 'K' && input[1] == 'X' && input[2] == ' ') { // Kalo KXspasi = ID
        while (temp != NULL) {
            if (strcmp(temp->patientID, input) == 0) { //compare stringnya
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
                found = 1; //Berarti found
                break;
            }
            temp = temp->next;
        }

        if (!found) { //Bila not found
            printf("Pasien dengan ID '%s' tidak ditemukan.\n", input);
        }
    } else {
        // Input dianggap sebagai nama
        while (temp != NULL) {
            if (strstr(temp->nama, input) != NULL) { //Huruf besar atau kecil berpengaruh
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
                found = 1; // Berarti found
            }
            temp = temp->next;
        }

        if (!found) { //Bila not found
            printf("Pasien dengan nama '%s' tidak ditemukan.\n", input);
        }
    }
}

int main() {
    DataPasien* pasienHead = NULL;
    char input[50];
    printf("Masukkan nama atau ID pasien: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Hilangkan karakter newline jika ada

    searchPatient(pasienHead, input);

    return 0;
}
