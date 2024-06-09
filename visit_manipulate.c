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

DataKunjungan* deleteVisit(DataKunjungan *head, char *patientID){
    DataKunjungan *temp = head;
    DataKunjungan *prev = NULL;
    while(temp != NULL){
        if(strcmp(temp->patientID, patientID) == 0){
            if(prev == NULL){
                head = temp->next;
            }else{
                prev->next = temp->next;
            }
            free(temp);
            return head;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}

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

void printVisit(DataKunjungan *head){
    DataKunjungan *temp = head;
    while(temp != NULL){
        printf("Index: %d\n", temp->index);
        printf("Tanggal: %d-%d-%d\n", temp->tanggal.date, temp->tanggal.month, temp->tanggal.year);
        printf("Patient ID: %s\n", temp->patientID);
        printf("Diagnosis: %s\n", penyakit[temp->diagnosis]);
        printf("Tindakan: %s\n", tindakan[temp->tindakan].nama);
        printf("Control: %d-%d-%d\n", temp->control.date, temp->control.month, temp->control.year);
        temp = temp->next;
    }
}