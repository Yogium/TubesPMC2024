/*
Pembuat file: M Yoga Putrapratama/13222050
Nama file: visit_manipulate.c
Deskripsi: fungsi untuk melakukan hal di bawah kepada data kunjungan:
1. Menambahkan data kunjungan
2. Menghapus data kunjungan
3. Mengubah data kunjungan
4. Mencari dan menampilkan data kunjungan
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

//Fungsi untuk membuat data kunjungan baru
DataKunjungan* createVisit(int index, date tanggal, char *patientID, int diagnosis, int tindakan, date control){
    DataKunjungan *newVisit = (DataKunjungan*)malloc(sizeof(DataKunjungan));
    newVisit->index = index;
    newVisit->tanggal = tanggal;
    strcpy(newVisit->patientID, patientID);
    newVisit->diagnosis = diagnosis;
    newVisit->tindakan = tindakan;
    newVisit->control = control;
    newVisit->next = NULL;
    return newVisit;
}

//Fungsi untuk menambahkan data kunjungan ke linked list
DataKunjungan* addVisit(DataKunjungan *head, DataKunjungan *newVisit){
    DataKunjungan *temp = head;
    if(head == NULL){
        head = newVisit;
    }else{
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newVisit;
    }
    return head;
}

//Fungsi untuk mencari data kunjungan berdasarkan patientID
DataKunjungan* searchVisit(DataKunjungan *head, char *patientID){
    DataKunjungan *temp = head;
    while(temp != NULL){
        if(strcmp(temp->patientID, patientID) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

//Fungsi untuk mengubah data kunjungan berdasarkan patientID
DataKunjungan* updateVisit(DataKunjungan *head, char *patientID, DataKunjungan *newVisit){
    DataKunjungan *temp = head;
    while(temp != NULL){
        if(strcmp(temp->patientID, patientID) == 0){
            temp->index = newVisit->index;
            temp->tanggal = newVisit->tanggal;
            strcpy(temp->patientID, newVisit->patientID);
            temp->diagnosis = newVisit->diagnosis;
            temp->tindakan = newVisit->tindakan;
            temp->control = newVisit->control;
            return head;
        }
        temp = temp->next;
    }
    return head;
}

//Fungsi untuk menampilkan data kunjungan
void printVisit(DataKunjungan *head){
    DataKunjungan *temp = head;
    while(temp != NULL){
        printf("Tanggal: %d-%d-%d\n", temp->tanggal.date, temp->tanggal.month, temp->tanggal.year);
        printf("Patient ID: %s\n", temp->patientID);
        printf("Diagnosis: %s\n", penyakit[temp->diagnosis]);
        printf("Tindakan: %s\n", tindakan[temp->tindakan].nama);
        printf("Control: %d-%d-%d\n", temp->control.date, temp->control.month, temp->control.year);
        temp = temp->next;
    }
}

int getIndex(DataKunjungan *head){
    DataKunjungan *temp = head;
    int index = 0;
    while(temp != NULL){
        index++;
        temp = temp->next;
    }
    return index;
}

//Fungsi untuk mendapat untuk proses menambah data kunjungan
void addVisitProcess(DataKunjungan **head){
    int diagnosis, tindakan;
    char patientID[11];
    int index = getIndex(*head);
    date tanggal, control;
    printf("Masukkan tanggal kunjungan (dd-mm-yyyy): ");
    scanf("%d-%d-%d", &tanggal.date, &tanggal.month, &tanggal.year);
    printf("Masukkan patient ID: ");
    scanf("%s", patientID);
    printf("Masukkan diagnosis: ");
    scanf("%d", &diagnosis);
    printf("Masukkan tindakan: ");
    scanf("%d", &tindakan);
    printf("Masukkan tanggal control (dd-mm-yyyy): ");
    scanf("%d-%d-%d", &control.date, &control.month, &control.year);
    DataKunjungan *newVisit = createVisit(index, tanggal, patientID, diagnosis, tindakan, control);
    *head = addVisit(*head, newVisit);
}

//Fungsi untuk mendapat untuk proses menghapus data kunjungan
void deleteVisit(DataKunjungan **head){
    char patientID[11];
    printf("Masukkan patient ID: ");
    scanf("%s", patientID);
    DataKunjungan *temp = *head;
    DataKunjungan *prev = NULL;
    while(temp != NULL){
        if(strcmp(temp->patientID, patientID) == 0){
            if(prev == NULL){
                *head = temp->next;
                printf("Data kunjungan berhasil dihapus\n");
            }else{
                prev->next = temp->next;
                printf("Data kunjungan berhasil dihapus\n");
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

//Fungsi untuk mendapat untuk proses mengubah data kunjungan
void changeVisit(DataKunjungan **head){
    int diagnosis, tindakan;
    char patientID[11];
    date tanggal, control;
    printf("Masukkan patient ID: ");
    scanf("%s", patientID);
    printf("Masukkan tanggal kunjungan (dd-mm-yyyy): ");
    scanf("%d-%d-%d", &tanggal.date, &tanggal.month, &tanggal.year);
    printf("Masukkan diagnosis: ");
    scanf("%d", &diagnosis);
    printf("Masukkan tindakan: ");
    scanf("%d", &tindakan);
    printf("Masukkan tanggal control (dd-mm-yyyy): ");
    scanf("%d-%d-%d", &control.date, &control.month, &control.year);
    DataKunjungan *newVisit = createVisit(getIndex(*head), tanggal, patientID, diagnosis, tindakan, control);
    *head = updateVisit(*head, patientID, newVisit);
}

//Fungsi untuk mendapat untuk proses mencari data kunjungan
void searchVisitProcess(DataKunjungan *head){
    char patientID[11];
    printf("Masukkan patient ID: ");
    scanf("%s", patientID);
    DataKunjungan *result = searchVisit(head, patientID);
    if(result == NULL){
        printf("Data kunjungan tidak ditemukan\n");
    }else{
        printVisit(result);
    }
}

