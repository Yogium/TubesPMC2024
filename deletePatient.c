//Nama : Nicholas Darren
//Nama file : deletePatient.c
//Deskripsi : Fungsi ini untuk menghapus pasien (dengan input ID)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "parsingDate.h"
#include "LinkedList.h"

void deletePatient(DataPasien** head) {


    DataPasien* patientHead = NULL;
    char idToModify[20];

    printf("Masukkan ID pasien yang ingin dihapus: ");
    fgets(idToModify, sizeof(idToModify), stdin);
    idToModify[strcspn(idToModify, "\n")] = 0;
    
    if (*head == NULL) { //Bila headnya kosong
        printf("The list is empty.\n");
        return;
    }

    DataPasien* temp = *head;
    DataPasien* prev = NULL;

    // Jika head node yang harus dihapus
    if (strcmp(temp->patientID, idToModify) == 0) {
        *head = temp->next; // Ubah head
        free(temp); // Bebaskan memori dari node yang dihapus
        printf("Patient dengan ID %s sudah dihapus.\n", idToModify);
        return;
    }

    // Cari node yang harus dihapus
    while (temp != NULL && strcmp(temp->patientID, idToModify) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // Jika patientID tidak ditemukan dalam linked list
    if (temp == NULL) {
        printf("Pasien dengan ID %s tidak ditemukan.\n", idToModify);
        return;
    }

    // Hapus node dari linked list
    prev->next = temp->next;
    free(temp); // Bebaskan memori dari node yang dihapus
    printf("Pasien dengan ID %s sudah dihapus.\n", idToModify);
}

// int main(){
//     DataPasien* patientHead = NULL;
//     deletePatient(&patientHead);
// }

