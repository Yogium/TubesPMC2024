//Nama: Nicholas Darren
//Nama file: deleteRiwayat.c
//Deskripsi : fungsi ini menghapus riwayat kedatangan pasien
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

void deleteRiwayat(DataKunjungan** head, const char* patientID) { //Fungsi untuk delete riwayat kunjungan pasien
    if (*head == NULL) {
        printf("Daftar kunjungan kosong.\n");
        return;
    }

    DataKunjungan* temp = *head;
    DataKunjungan* prev = NULL;

    // Jika node pertama yang harus dihapus
    if (strcmp(temp->patientID, patientID) == 0) {
        *head = temp->next;
        free(temp);
        printf("Kunjungan untuk pasien dengan ID %s sudah dihapus.\n", patientID);
        return;
    }

    // Cari node yang harus dihapus
    while (temp != NULL && strcmp(temp->patientID, patientID) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // Jika pasien tidak ditemukan dalam daftar kunjungan
    if (temp == NULL) {
        printf("Kunjungan untuk pasien dengan ID %s tidak ditemukan.\n", patientID);
        return;
    }

    // Hapus node dari daftar kunjungan
    prev->next = temp->next;
    free(temp);
    printf("Kunjungan untuk pasien dengan ID %s sudah dihapus.\n", patientID);
}

int main(){
    DataKunjungan* kunjunganHead = NULL;
  
    char idToModify[20];
    printf("Masukkan ID pasien yang ingin dihapus: ");
    fgets(idToModify, sizeof(idToModify), stdin);
    idToModify[strcspn(idToModify, "\n")] = 0;
  
    deleteRiwayat(&kunjunganHead, idToModify);
    return 0;
}
