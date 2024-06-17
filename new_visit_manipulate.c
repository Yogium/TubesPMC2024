#/*
Pembuat file: M Yoga Putrapratama/13222050
Nama file: visit_manipulate.c
Deskripsi: fungsi untuk melakukan hal di bawah kepada data kunjungan:
1. Menambahkan data kunjungan
2. Menghapus data kunjungan
3. Mengubah data kunjungan
4. Mencari dan menampilkan data kunjungan
*/

#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "LinkedList.h"

//menambahkan data kunjungan ke linked list
void addVisit(DataKunjungan **head, char* tanggal, char *patientID, int diagnosis, int tindakan, char* control) {
    DataKunjungan *newVisit = malloc(sizeof(DataKunjungan)); 

    DataKunjungan *temp = *head;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }

    if (temp != NULL) {
        newVisit->index = temp->index + 1; // Dimasukkan ke index + 1
    } 
    else {
        newVisit->index = 1; // Bila linked list kosong, index = 1
    }

    //parsing tanggal kunjungan
    char *token = strtok(tanggal, "/");
    newVisit->tanggal.date = atoi(token);
    token = strtok(NULL, "/");
    newVisit->tanggal.month = atoi(token);
    token = strtok(NULL, "/");
    newVisit->tanggal.year = atoi(token);

    //parsing tanggal kontrol
    token = strtok(control, "/");
    newVisit->control.date = atoi(token);
    token = strtok(NULL, "/");
    newVisit->control.month = atoi(token);
    token = strtok(NULL, "/");
    newVisit->control.year = atoi(token);

    //masukkan ke newvisit
    strcpy(newVisit->patientID, patientID);
    newVisit->diagnosis = diagnosis;
    newVisit->tindakan = tindakan;
    newVisit->next = NULL;

    //masukkan ke linked list
    if(*head == NULL){
        *head = newVisit;
    }else{
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newVisit;
    }
}

//fungsi untuk delete visit
void deleteVisit(DataKunjungan **head, char *patientID, date tanggal){
    DataKunjungan *temp = *head;
    DataKunjungan *prev = NULL;

    //jika data yang dihapus adalah head
    if(temp != NULL && strcmp(temp->patientID, patientID) == 0 && temp->tanggal.date == tanggal.date && temp->tanggal.month == tanggal.month && temp->tanggal.year == tanggal.year){
        *head = temp->next;
        free(temp);
        return;
    }

    //cari data yang akan dihapus
    while(temp != NULL && (strcmp(temp->patientID, patientID) != 0 || temp->tanggal.date != tanggal.date || temp->tanggal.month != tanggal.month || temp->tanggal.year != tanggal.year)){
        prev = temp;
        temp = temp->next;
    }

    //jika data tidak ditemukan
    if(temp == NULL){
        printf("Data tidak ditemukan\n");
        return;
    }

    //hapus data
    prev->next = temp->next;
    free(temp);
}

//fungsi untuk mengubah data kunjungan
void updateVisit(DataKunjungan **head, char *patientID, date tanggal, char* controlStr, int diagnosis, int tindakan){
    DataKunjungan *temp = *head;

    while(temp != NULL){
        if(strcmp(temp->patientID, patientID) == 0 && temp->tanggal.date == tanggal.date && temp->tanggal.month == tanggal.month && temp->tanggal.year == tanggal.year){
            char *token = strtok(controlStr, "/");
            temp->control.date = atoi(token);
            token = strtok(NULL, "/");
            temp->control.month = atoi(token);
            token = strtok(NULL, "/");
            temp->control.year = atoi(token);
            temp->diagnosis = diagnosis;
            temp->tindakan = tindakan;
            return;
        }
        temp = temp->next;
    }
}

//fungsi untuk mencari data kunjungan
DataKunjungan* searchVisit(DataKunjungan *head, char *patientID){
    DataKunjungan *temp = head;
    DataKunjungan *result = NULL;
    while(temp != NULL){
        if(strcmp(temp->patientID, patientID) == 0){
            DataKunjungan *foundVisit = malloc(sizeof(DataKunjungan));
            foundVisit->index = temp->index;
            foundVisit->tanggal = temp->tanggal;
            foundVisit->control = temp->control;
            foundVisit->diagnosis = temp->diagnosis;
            foundVisit->tindakan = temp->tindakan;
            foundVisit->next = NULL;
            if(result == NULL){
                result = foundVisit;
            }else{
                DataKunjungan *curr = result;
                while(curr->next != NULL){
                    curr = curr->next;
                }
                curr->next = foundVisit;
            }
        }
        temp = temp->next;
    }
    return result;
}

//selector
void selector(DataKunjungan *head){
    int exit = 0;
    int choice;
                char tanggalStr[20];
                char patientID[11];
                int diagnosis;
                int tindakan;
                char control[20];
    while(exit == 0){
        printf("Pilih menu:\n");
        printf("1. Tambah data kunjungan\n2. Hapus data kunjungan\n3. Ubah data kunjungan\n4. Cari data kunjungan\n5. Keluar\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Masukkan data kunjungan\n");

                printf("Tanggal kunjungan: ");
                scanf("%s", tanggalStr);
                printf("Patient ID: ");
                scanf("%s", patientID);
                printf("Diagnosis: ");
                scanf("%d", &diagnosis);
                printf("Tindakan: ");
                scanf("%d", &tindakan);
                printf("Tanggal kontrol: ");
                scanf("%s", control);
                addVisit(&head, tanggalStr, patientID, diagnosis, tindakan, control);
                break;
            case 2:
                //hapus data kunjungan
                char patientID[11];
                date tanggal;
                char tanggalStr[20];
                printf("Masukkan data kunjungan yang akan dihapus\n");
                printf("Patient ID: ");
                scanf("%s", patientID);
                printf("Tanggal kunjungan: (dd/mm/yyyy)");
                scanf("%s", tanggalStr);
                char *token = strtok(tanggalStr, "/");
                tanggal.date = atoi(token);
                token = strtok(NULL, "/");
                tanggal.month = atoi(token);
                token = strtok(NULL, "/");
                tanggal.year = atoi(token);
                deleteVisit(&head, patientID, tanggal);
                break;
            case 3:
                //ubah data kunjungan
                printf("Masukkan data kunjungan yang akan diubah\n");
                printf("Patient ID: ");
                scanf("%s", patientID);
                printf("Tanggal kunjungan: (dd/mm/yyyy)");
                scanf("%s", tanggalStr);
                printf("Diagnosis: ");
                scanf("%d", &diagnosis);
                printf("Tindakan: ");
                scanf("%d", &tindakan);
                printf("Tanggal kontrol: ");
                scanf("%s", control);
                updateVisit(&head, patientID, tanggal, control, diagnosis, tindakan);
                break;
            case 4:
                //cari data kunjungan
                printf("Masukkan patient ID: ");
                scanf("%s", patientID);
                DataKunjungan *result = searchVisit(head, patientID);
                break;
            case 5:
                exit = 1;
                break;
            default:
                printf("Pilihan tidak valid\n");
        }
    }
}

int main(){
    DataKunjungan *head = NULL;
    parseDataKunjunganFromFile("Riwayat_Datang.csv", &head);
    selector(head);
}