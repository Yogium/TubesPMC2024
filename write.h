/*  Nama      : Kennard Benaya Manli
    Nama file : write.c
    Deskripsi : 
    -> write backup data pasien dan kunjungan ke dalam file csv
    -> write data pasien dan kunjungan ke dalam file csv
*/



#ifndef WRITE_H
#define WRITE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "LinkedList.h"
//write backup

void writeBackupDataPasien(DataPasien* head) {
    FILE* file = fopen("Backup_Data_Pasien.csv", "w");
    if (!file) {
        printf("Failed to open file");
    }

    fprintf(file, "No,Nama Lengkap,Alamat,Kota,Tempat Lahir,Tanggal Lahir,Umur (th),No BPJS,ID Pasien,\n");

    char itobulan1[20];
    DataPasien* temp = head;
    while (temp) {
        strcpy(itobulan1, bulan[temp->tgllahir.month-1]);
        fprintf(file, "%d,%s,%s,%s,%s,%d %s %d,%d,%s,%s,\n", temp->index, temp->nama, temp->alamat, temp->kota, temp->tempatLahir, temp->tgllahir.date, itobulan1, temp->tgllahir.year, temp->umur, temp->BPJS, temp->patientID);
        temp = temp->next;
    }

    fclose(file);
}

void writeBackupDataKunjungan(DataKunjungan* head) {
    FILE* file = fopen("Backup_Riwayat_Datang.csv", "w");
    if (!file) {
        printf("Failed to open file");
    }

    fprintf(file, "No,Tanggal,ID Pasien,Diagnosis,Tindakan,Kontrol,Biaya (Rp),\n");

    int biaya;
    char itobulan1[20];
    char itobulan2[20];
    char tempdiag[20];
    char tempaction[20];
    DataKunjungan* temp = head;
    while (temp) {
        biaya = 140000+tindakan[temp->tindakan].biaya;
        strcpy(itobulan1, bulan[temp->tanggal.month-1]);
        strcpy(itobulan2, bulan[temp->control.month-1]);
        strcpy(tempdiag, penyakit[temp->diagnosis]);
        strcpy(tempaction, tindakan[temp->tindakan].nama);
        fprintf(file, "%d,%d %s %d,%s,%d,%d,%d %s %d,%d,\n", temp->index, temp->tanggal.date, itobulan1, temp->tanggal.year, temp->patientID, temp->diagnosis, temp->tindakan, temp->control.date, itobulan2, temp->control.year, biaya);
        temp = temp->next;
    }

    fclose(file);
}

//save

void writeDataPasien(DataPasien* head) {
    FILE* file = fopen("Data_Pasien.csv", "w");
    if (!file) {
        printf("Failed to open file");
    }

    fprintf(file, "No,Nama Lengkap,Alamat,Kota,Tempat Lahir,Tanggal Lahir,Umur (th),No BPJS,ID Pasien,\n");

    char itobulan1[20];
    DataPasien* temp = head;
    while (temp) {
        strcpy(itobulan1, bulan[temp->tgllahir.month-1]);
        fprintf(file, "%d,%s,%s,%s,%s,%d %s %d,%d,%s,%s,\n", temp->index, temp->nama, temp->alamat, temp->kota, temp->tempatLahir, temp->tgllahir.date, itobulan1, temp->tgllahir.year, temp->umur, temp->BPJS, temp->patientID);
        temp = temp->next;
    }

    fclose(file);
}

void writeDataKunjungan(DataKunjungan* head) {
    FILE* file = fopen("Riwayat_Datang.csv", "w");
    if (!file) {
        printf("Failed to open file");
    }

    fprintf(file, "No,Tanggal,ID Pasien,Diagnosis,Tindakan,Kontrol,Biaya (Rp),\n");

    int biaya;
    char itobulan1[20];
    char itobulan2[20];
    char tempdiag[20];
    char tempaction[20];
    DataKunjungan* temp = head;
    while (temp) {
        biaya = 140000+tindakan[temp->tindakan].biaya;
        strcpy(itobulan1, bulan[temp->tanggal.month-1]);
        strcpy(itobulan2, bulan[temp->control.month-1]);
        strcpy(tempdiag, penyakit[temp->diagnosis]);
        strcpy(tempaction, tindakan[temp->tindakan].nama);
        fprintf(file, "%d,%d %s %d,%s,%d,%d,%d %s %d,%d,\n", temp->index, temp->tanggal.date, itobulan1, temp->tanggal.year, temp->patientID, temp->diagnosis, temp->tindakan, temp->control.date, itobulan2, temp->control.year, biaya);
        temp = temp->next;
    }

    fclose(file);
}

#endif