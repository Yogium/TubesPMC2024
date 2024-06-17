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
DataKunjungan* updateVisit(DataKunjungan *head, char *patientID, date tanggal, DataKunjungan *newVisit){
    DataKunjungan *temp = head;
    while(temp != NULL){
        if(strcmp(temp->patientID, patientID) == 0 && temp->tanggal.date == tanggal.date && temp->tanggal.month == tanggal.month && temp->tanggal.year == tanggal.year){
            temp->index = newVisit->index;
            temp->tanggal = newVisit->tanggal;
            strcpy(temp->patientID, newVisit->patientID);
            temp->diagnosis = newVisit->diagnosis;
            temp->tindakan = newVisit->tindakan;
            temp->control = newVisit->control;
            free(newVisit);
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
void addVisitProcess(DataKunjungan **head, char *patientID, int diagnosis, int tindakan, char *controlstr, char* tanggalstr){
    int index = getIndex(*head);
    //parse date
    int Cdate, Cmonth, Cyear;
    int Tdate, Tmonth, Tyear;
    //parse control date
    char *token = strtok(controlstr, "/");
    Cdate = atoi(token);
    token = strtok(NULL, "/");
    Cmonth = atoi(token);
    token = strtok(NULL, "/");
    Cyear = atoi(token);
    //parse tanggal date
    token = strtok(tanggalstr, "/");
    Tdate = atoi(token);
    token = strtok(NULL, "/");
    Tmonth = atoi(token);
    token = strtok(NULL, "/");
    Tyear = atoi(token);

    date tanggal, control;
    tanggal.date = Tdate;
    tanggal.month = Tmonth;
    tanggal.year = Tyear;
    control.date = Cdate;
    control.month = Cmonth;
    control.year = Cyear;
    DataKunjungan *newVisit = createVisit(index, tanggal, patientID, diagnosis, tindakan, control);
    *head = addVisit(*head, newVisit);
}

//Fungsi untuk mendapat untuk proses menghapus data kunjungan
void deleteVisit(DataKunjungan **head, char* patientID, date tanggal){
    DataKunjungan *temp = *head;
    DataKunjungan *prev = NULL;
    while(temp != NULL){
        if(strcmp(temp->patientID, patientID) == 0 && temp->tanggal.date == tanggal.date && temp->tanggal.month == tanggal.month && temp->tanggal.year == tanggal.year){
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
void changeVisit(DataKunjungan **head, char* patientID, char* dateStr, char* controlStr, int diagnosis, int tindakan){
    date tanggal, control;
    char *token = strtok(dateStr, "/");
    tanggal.date = atoi(token);
    token = strtok(NULL, "/");
    tanggal.month = atoi(token);
    token = strtok(NULL, "/");
    tanggal.year = atoi(token);

    token = strtok(controlStr, "/");
    control.date = atoi(token);
    token = strtok(NULL, "/");
    control.month = atoi(token);
    token = strtok(NULL, "/");
    control.year = atoi(token);

    DataKunjungan *newVisit = createVisit(getIndex(*head), tanggal, patientID, diagnosis, tindakan, control);

    *head = updateVisit(*head, patientID, tanggal, newVisit);
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

int main(){
    DataKunjungan *head = NULL;
    addVisitProcess(&head, "1234567890", 0, 0, "1/1/2021", "1/1/2021");
    addVisitProcess(&head, "1234567890", 1, 1, "1/1/2021", "1/1/2021");
    addVisitProcess(&head, "1234567890", 2, 2, "1/1/2021", "1/1/2021");
    addVisitProcess(&head, "1234567890", 3, 3, "1/1/2021", "1/1/2021");
    printVisit(head);
    deleteVisit(&head, "1234567890", (date){1, 1, 2021});
    printVisit(head);
    changeVisit(&head, "1234567890", "1/1/2021", "1/1/2021", 0, 0);
    printVisit(head);
    searchVisitProcess(head);
    return 0;
}