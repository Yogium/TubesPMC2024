#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "parsingDate.c"

//fungsi untuk mencari index penyakit
int findDisease(char* disease){
    for(int i = 0; i < 4; i++){
        if(strcmp(disease, penyakit[i]) == 0){
            return i;
        }
    }
    return -1;
}

//fungsi untuk mencari index tindakan
int findAction(char* action){
    for(int i = 0; i < 6; i++){
        if(strcmp(action, tindakan[i].nama) == 0){
            return i;
        }
    }
    return -1;
}


// fungsi untuk membuat node baru untuk pasien
DataPasien* createpatient(int index, char* name, char* address, char* city, char* birthplace, date birthdate, int age, char* bpjs, char* patientID) {
    DataPasien* newpatient = (DataPasien*)malloc(sizeof(DataPasien));
    newpatient->index = index;
    strcpy(newpatient->nama, name);
    strcpy(newpatient->alamat, address);
    strcpy(newpatient->kota, city);
    strcpy(newpatient->tempatLahir, birthplace);
    newpatient->tgllahir = birthdate;
    newpatient->umur = age;
    strcpy(newpatient->BPJS, bpjs);
    newpatient->next = NULL;
    return newpatient;
}

// fungsi untuk membuat node baru untuk riwayat kedatangan
DataKunjungan* createvisit(int index, date visitdate, char* patientid, char* diagnosis, char* action, date control) {
    DataKunjungan* newvisit = (DataKunjungan*)malloc(sizeof(DataKunjungan));
    newvisit->tanggal = visitdate;
    strcpy(newvisit->patientID, patientid);
    newvisit->diagnosis = findDisease(diagnosis);
    newvisit->tindakan = findAction(action);
    newvisit->control = control;
    newvisit->next = NULL;
    return newvisit;
}

// fungsi untuk menambah node di akhir linked list pasien
void appendpatient(DataPasien** head, int index, char* name, char* address, char* city, char* birthplace, date birthdate, int age, char* bpjs, char* patientID) {
    DataPasien* newpatient = createpatient(index, name, address, city, birthplace, birthdate, age, bpjs, patientID);
    if (*head == NULL) {
        *head = newpatient;
    } else {
        DataPasien* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newpatient;
    }
}

// fungsi untuk menambah node di akhir linked list riwayat kedatangan
void appendvisit(DataKunjungan** head, int index, date visitdate, char* patientid, char* diagnosis, char* action, date control) {
    DataKunjungan* newvisit = createvisit(index, visitdate, patientid, diagnosis, action, control);
    if (*head == NULL) {
        *head = newvisit;
    } else {
        DataKunjungan* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newvisit;
    }
}

// fungsi untuk mencetak linked list pasien
void printpatients(DataPasien* head) {
    DataPasien* temp = head;
    while (temp != NULL) {
        printf("name: %s, address: %s, city: %s, birthplace: %s, birthdate: %s, age: %d, bpjs: %s\n", 
            temp->nama, temp->alamat, temp->kota, temp->tempatLahir, temp->tgllahir.original, temp->umur, temp->BPJS);
        temp = temp->next;
    }
}

// fungsi untuk mencetak linked list riwayat kedatangan
void printvisits(DataKunjungan* head) {
    DataKunjungan* temp = head;
    while (temp != NULL) {
        printf("visit date: %s, patient id: %s, diagnosis: %s, action: %s, control: %s\n", 
               temp->tanggal.original, temp->patientID, penyakit[temp->diagnosis], tindakan[temp->tindakan].nama, temp->control.original);
        temp = temp->next;
    }
}

void init_LL(DataPasien** patientHead, DataKunjungan** kunjunganHead ){
    *patientHead = NULL;
    *kunjunganHead = NULL;
    FILE* flPasien = fopen("Data_Pasien.csv", "r");
    FILE* flKunjungan = fopen("Riwayat_Datang.csv", "r");
    if(flPasien == NULL){
        printf("Error opening patient data\n");
        return;
    }
    if(flKunjungan == NULL){
        printf("Error opening visit data\n");
        return;
    }
    char originalBirthDate[20][100];
    char line[256];
     while (fgets(line, sizeof(line), flPasien)) {
        if (strstr(line, "visits:") != NULL) {
            break;
        }

        int id, age;
        char name[100], address[100], city[50], birthplace[50], birthdatestr[20], bpjs[20], patID[11];
        sscanf(line, "%d,%99[^,],%99[^,],%49[^,],%49[^,],%19[^,],%d,%19[^,],%11[^,,]", &id, name, address, city, birthplace, birthdatestr, &age, bpjs, patID);
        date birthdate = parseDate(birthdatestr, originalBirthDate);
        appendpatient(&patientHead, id, name, address, city, birthplace, birthdate, age, bpjs, patID);
    }

    // membaca riwayat kedatangan
    while (fgets(line, sizeof(line), flKunjungan)) {
        char visitdatestr[20], diagnosis[100], action[100], controlstr[50], patientid[11];
        int index;
        float cost;
        char originalVisit[20][100], originalControl[20][100];
        sscanf(line, "%d,%19[^,],%11[^,],%99[^,],%99[^,],%49[^,]", &index, visitdatestr, patientid, diagnosis, action, controlstr);
        date visitdate = parseDate(visitdatestr, originalVisit);
        date control = parseDate(controlstr, originalControl);
        appendvisit(kunjunganHead, index, visitdate, patientid, diagnosis, action, control);
    }   
    fclose(flPasien);
    fclose(flKunjungan);
}

int main() {
    DataPasien* patienthead;
    DataKunjungan* visithead;
    init_LL(&patienthead, &visithead);
    printf("patients:\n");
    printpatients(patienthead);

    printf("\nvisits:\n");
    printvisits(visithead);

    return 0;
}
