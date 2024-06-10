//Nama : Nicholas Darren
//Nama file: addRiwayat.c
//Deskripsi: fungsi untuk menambahkan riwayat
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

date parseDate(char* dateString, char* original);

void addRiwayat(DataKunjungan** head) {
    DataKunjungan* newNode = createDataKunjunganNode();
    printf("Masukkan data kunjungan:\n");

    DataKunjungan* temp = *head;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }

    // Otomatis memberikan indeks ke indeks terakhir + 1
    if (temp != NULL) {
        newNode->index = temp->index + 1; // tambahkan indeks dengan 1
    } else {
        newNode->index = 1; // jika linked list kosong, indeks = 1
    }

    // Loop sampai pengguna memasukkan format tanggal yang benar untuk tanggal
    char tanggalString[50];
    int validTanggal = 0;
    while (!validTanggal) {
        printf("Tanggal (dd mmm yyyy): ");
        fgets(tanggalString, sizeof(tanggalString), stdin);
        tanggalString[strcspn(tanggalString, "\n")] = '\0';
        newNode->tanggal = parseDate(tanggalString, NULL); // Diperbarui di sini
        if (newNode->tanggal.date > 0 && newNode->tanggal.month > 0 && newNode->tanggal.year > 0) {
            validTanggal = 1; // tanggal valid, keluar dari loop
        } else {
            printf("Format tanggal tidak valid. Masukkan ulang.\n");
        }
    }

    printf("ID Pasien: ");
    scanf("%s", newNode->patientID);
    getchar(); // Kosongkan karakter newline yang tersisa di buffer input

    // Loop sampai pengguna memasukkan diagnosis yang valid
    int diagnosis;
    do {
        printf("Diagnosis (1. Dehidrasi, 2. Keseleo, 3. Masuk Angin, 4. Pusing): ");
        scanf("%d", &diagnosis);
        getchar(); // Kosongkan karakter newline yang tersisa di buffer input
    } while (diagnosis < 1 || diagnosis > 4); // Pastikan diagnosis berada di antara 1 dan 4
    newNode->diagnosis = diagnosis;

    // Loop sampai pengguna memasukkan tindakan yang valid
    int tindakan;
    do {
        printf("Tindakan (1. Pendaftaran, 2. Pemeriksaan, 3. Vaksinasi, 4. Cek gula darah, 5. Pemasangan infus, 6. Pengobatan): ");
        scanf("%d", &tindakan);
        getchar(); // Kosongkan karakter newline yang tersisa di buffer input
    } while (tindakan < 1 || tindakan > 6); // Pastikan tindakan berada di antara 1 dan 6
    newNode->tindakan = tindakan;

    // Loop sampai pengguna memasukkan format tanggal yang benar untuk kontrol
    char controlString[50];
    int validControl = 0;
    while (!validControl) {
        printf("Kontrol (dd mmm yyyy): ");
        fgets(controlString, sizeof(controlString), stdin);
        controlString[strcspn(controlString, "\n")] = '\0';
        newNode->control = parseDate(controlString, NULL); // Diperbarui di sini
        if (newNode->control.date > 0 && newNode->control.month > 0 && newNode->control.year > 0) {
            validControl = 1; // tanggal valid, keluar dari loop
        } else {
            printf("Format tanggal tidak valid. Masukkan ulang.\n");
        }
    }

    // Tambahkan riwayat medis baru
    insertDataKunjunganAtEnd(head, newNode);

    printf("Riwayat kunjungan berhasil ditambahkan!\n");
}


int main() {
    DataKunjungan* kunjunganHead = NULL;
    addRiwayat(kunjunganHead);
    return 0;
} 
