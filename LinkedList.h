/*  Nama      : Nusaiba El Qonitat
    Nama file : LinkedList.c
    Deskripsi : Fungsi untuk menginput informasi dalam file csv ke dalam linked list
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "parsingDate.h"

// Fungsi untuk membuat node baru dari DataPasien
DataPasien* createDataPasienNode() {
    DataPasien* newNode = (DataPasien*)malloc(sizeof(DataPasien));
    if (!newNode) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    newNode->next = NULL;
    return newNode;
}

// Fungsi untuk menambahkan node DataPasien di akhir linked list
void insertDataPasienAtEnd(DataPasien** head, DataPasien* newNode) {
    if (*head == NULL) {
        *head = newNode;
    } else {
        DataPasien* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Fungsi untuk membaca dan mem-parsing data pasien dari file
void parseDataPasienFromFile(const char* filename, DataPasien** head) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    char line[256];

    // Skip header
    if (fgets(line, sizeof(line), file)) {
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = '\0';

            DataPasien* newNode = createDataPasienNode();

            char* token = strtok(line, ",");
            int colomnCount = 0;
            char dateString[50];

            while (token) {
                switch (colomnCount) {
                    case 0: newNode->index = atoi(token); break;
                    case 1: strcpy(newNode->nama, token); break;
                    case 2: strcpy(newNode->alamat, token); break;
                    case 3: strcpy(newNode->kota, token); break;
                    case 4: strcpy(newNode->tempatLahir, token); break;
                    case 5: strcpy(dateString, token); break;
                    case 6: newNode->umur = atoi(token); break;
                    case 7: strcpy(newNode->BPJS, token); break;
                    case 8: strcpy(newNode->patientID, token); break;
                }
                colomnCount++;
                token = strtok(NULL, ",");
            }

            char original[20];
            newNode->tgllahir = parseDate(dateString, original);

            insertDataPasienAtEnd(head, newNode);
        }
    }
    fclose(file);
}

// Fungsi untuk mencetak seluruh data pasien dari linked list
void printDataPasienList(DataPasien* head) {
    DataPasien* temp = head;
    while (temp != NULL) {
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
        temp = temp->next;
    }
}

// Fungsi untuk membebaskan memori dari seluruh linked list data pasien
void freeDataPasienList(DataPasien* head) {
    DataPasien* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Fungsi untuk membuat node baru dari DataKunjungan
DataKunjungan* createDataKunjunganNode() {
    DataKunjungan* newNode = (DataKunjungan*)malloc(sizeof(DataKunjungan));
    if (!newNode) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    newNode->next = NULL;
    return newNode;
}

// Fungsi untuk menambahkan node DataKunjungan di akhir linked list
void insertDataKunjunganAtEnd(DataKunjungan** head, DataKunjungan* newNode) {
    if (*head == NULL) {
        *head = newNode;
    } else {
        DataKunjungan* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Fungsi untuk membaca dan mem-parsing data kunjungan dari file
void parseDataKunjunganFromFile(const char* filename, DataKunjungan** head) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    char line[256];

    // Skip header
    if (fgets(line, sizeof(line), file)) {
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = '\0';

            DataKunjungan* newNode = createDataKunjunganNode();

            char* token = strtok(line, ",");
            int colomnCount = 0;
            char dateString[50], controlDateString[50];

            while (token) {
                switch (colomnCount) {
                    case 0: newNode->index = atoi(token); break;
                    case 1: strcpy(dateString, token); break;
                    case 2: strcpy(newNode->patientID, token); break;
                    case 3: newNode->diagnosis = atoi(token); break;
                    case 4: newNode->tindakan = atoi(token); break;
                    case 5: strcpy(controlDateString, token); break;
                }
                colomnCount++;
                token = strtok(NULL, ",");
            }

            char original[20];
            newNode->tanggal = parseDate(dateString, original);
            newNode->control = parseDate(controlDateString, original);

            insertDataKunjunganAtEnd(head, newNode);
        }
    }
    fclose(file);
}

// Fungsi untuk mencetak seluruh data kunjungan dari linked list
void printDataKunjunganList(DataKunjungan* head) {
    DataKunjungan* temp = head;
    while (temp != NULL) {
        printf("Index: %d\n", temp->index);
        printf("Tanggal: %02d-%02d-%04d\n", temp->tanggal.date, temp->tanggal.month, temp->tanggal.year);
        printf("Patient ID: %s\n", temp->patientID);
        printf("Diagnosis: %s\n", penyakit[temp->diagnosis]);
        printf("Tindakan: %s (Rp %d)\n", tindakan[temp->tindakan].nama, tindakan[temp->tindakan].biaya);
        printf("Control Date: %02d-%02d-%04d\n", temp->control.date, temp->control.month, temp->control.year);
        printf("\n");
        temp = temp->next;
    }
}

// Fungsi untuk membebaskan memori dari seluruh linked list data kunjungan
void freeDataKunjunganList(DataKunjungan* head) {
    DataKunjungan* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

#endif