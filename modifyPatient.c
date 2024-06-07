//Nama : Nicholas Darren
//Nama file : modifyPatient.c
// Deskripsi : Fungsi ini untuk mengubah data pasien dengan input ID dari user
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "parsingDate.c"

void modifyPatient(DataPasien* head, char *patientID) { //Fungsi buat ubah data pasien
    DataPasien* temp = head;
    while (temp != NULL) { //Cari pasien dengan ID yang sudah dimasukkan pengguna
        if (strcmp(temp->patientID, patientID) == 0) {
            char choice;
            char input[256];
            
            printf("Ubah fungsi:\n"); 
            printf("1. Nama Lengkap\n");
            printf("2. Alamat\n");
            printf("3. Kota\n");
            printf("4. Tempat Lahir\n");
            printf("5. Tanggal Lahir\n");
            printf("6. Umur\n");
            printf("7. No BPJS\n");
            printf("8. Exit\n");
            printf("Masukkan angka: ");
            scanf(" %c", &choice);
            getchar();

            switch (choice) { //Dibikin menu aja
                case '1':
                    printf("Masukkan nama baru: ");
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
                    strcpy(temp->nama, input);
                    break;
                case '2':
                    printf("Masukkan alamat baru: ");
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
                    strcpy(temp->alamat, input);
                    break;
                case '3':
                    printf("Masukkan kota baru: ");
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
                    strcpy(temp->kota, input);
                    break;
                case '4':
                    printf("Masukkan tempat lahir baru: ");
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
                    strcpy(temp->tempatLahir, input);
                    break;
                case '5':
                    printf("Masukkan tanggal lahir baru (format: dd mm yyyy or dd-mm-yy): ");
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
                    char original[20];
                    temp->tgllahir = parseDate(input, original);
                    break;
                case '6':
                    printf("Masukkan umur baru: ");
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
                    temp->umur = atoi(input);
                    break;
                case '7':
                    printf("Masukkan no BPJS baru: ");
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
                    strcpy(temp->BPJS, input);
                    break;
                case '8': //Exit
                    printf("Keluar.\n");
                    return;
                default: //Pilihan diluar 1 sampai 8 invalid
                    printf("Invalid.\n");
                    break;
            }
            return;
        }
        temp = temp->next;
    }
    printf("Pasien dengan ID %s tidak ditemukan.\n", patientID);
}

int main(){
    DataPasien* patientHead = NULL;
    char idToModify[20];
    printf("Masukkan ID pasien yang ingin diubah: ");
    fgets(idToModify, sizeof(idToModify), stdin);
    idToModify[strcspn(idToModify, "\n")] = 0;
    modifyPatient(patientHead, idToModify);
    return 0;
}
