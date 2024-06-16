//Nama : Nicholas Darren
//Nama file : modifyPatient.c
// Deskripsi : Fungsi ini untuk mengubah data pasien dengan input ID dari user
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "parsingDate.c"

void modifyPatient(DataPasien** head, char* idToModify, char* newNama, char* newAlamat, char* newKota, char* newTempatLahir, char* newTglLahir, int newUmur, char* newBPJS) {
    DataPasien* temp = *head;

    while (temp != NULL && strcmp(temp->patientID, idToModify) != 0) {
        temp = temp->next;
    }

    if (temp != NULL) {
        if (strlen(newNama) > 0) {
            strcpy(temp->nama, newNama);
        }
        if (strlen(newAlamat) > 0) {
            strcpy(temp->alamat, newAlamat);
        }
        if (strlen(newKota) > 0) {
            strcpy(temp->kota, newKota);
        }
        if (strlen(newTempatLahir) > 0) {
            strcpy(temp->tempatLahir, newTempatLahir);
        }
        if (strlen(newTglLahir) > 0) {
            char originalDate[20];
            temp->tgllahir = parseDate(newTglLahir, originalDate);
            if (temp->tgllahir.date == 0 || temp->tgllahir.month == 0 || temp->tgllahir.year == 0) {
                printf("Invalid date format.\n");
                return;
            }
        }
        if (newUmur > 0) {
            temp->umur = newUmur;
        }
        if (strlen(newBPJS) > 0) {
            strcpy(temp->BPJS, newBPJS);
        }

        printf("Data pasien berhasil diubah!\n");
    } else {
        printf("Pasien dengan ID %s tidak ditemukan.\n", idToModify);
    }
}

int main() {
    DataPasien* pasienHead = NULL;
    char idToModify[20];
    char newNama[100] = ""; //Default kosong atau ketika tidak diubah
    char newAlamat[100] = "";
    char newKota[50] = "";
    char newTempatLahir[50] = "";
    char newTglLahir[20] = "";
    int newUmur = 0;
    char newBPJS[20] = "";

    printf("Masukkan ID pasien yang ingin diubah: ");
    fgets(idToModify, sizeof(idToModify), stdin);
    idToModify[strcspn(idToModify, "\n")] = 0; 

    printf("Masukkan nama baru (atau kosongkan): "); //Pakai fgets karena ketika digunakan scanf program error
    fgets(newNama, sizeof(newNama), stdin);
    newNama[strcspn(newNama, "\n")] = 0; 

    printf("Masukkan alamat baru (atau kosongkan): ");
    fgets(newAlamat, sizeof(newAlamat), stdin);
    newAlamat[strcspn(newAlamat, "\n")] = 0; 

    printf("Masukkan kota baru (atau kosongkan): ");
    fgets(newKota, sizeof(newKota), stdin);
    newKota[strcspn(newKota, "\n")] = 0;

    printf("Masukkan tempat lahir baru (atau kosongkan): ");
    fgets(newTempatLahir, sizeof(newTempatLahir), stdin);
    newTempatLahir[strcspn(newTempatLahir, "\n")] = 0;

    printf("Masukkan tanggal lahir baru (dd NamaBulan yyyy) (atau kosongkan): ");
    fgets(newTglLahir, sizeof(newTglLahir), stdin);
    newTglLahir[strcspn(newTglLahir, "\n")] = 0;

    printf("Masukkan umur baru (atau 0 jika tidak diubah): ");
    scanf("%d", &newUmur);
    getchar();

    printf("Masukkan no BPJS baru (atau kosongkan): ");
    fgets(newBPJS, sizeof(newBPJS), stdin);
    newBPJS[strcspn(newBPJS, "\n")] = 0;

    modifyPatient(&pasienHead, idToModify, newNama, newAlamat, newKota, newTempatLahir, newTglLahir, newUmur, newBPJS);
    return 0;
}
