//Nama : Nicholas Darren
//Nama file : modifyPatient.c
// Deskripsi : Fungsi ini untuk mengubah data pasien dengan input ID dari user
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "parsingDate.h"

void modifyPatient(DataPasien** head) {
    char idToModify[20];
    printf("Masukkan ID pasien yang ingin diubah: ");
    fgets(idToModify, sizeof(idToModify), stdin);
    idToModify[strcspn(idToModify, "\n")] = 0;
    DataPasien* temp = *head;
    
    while (temp != NULL) {
        if (strcmp(temp->patientID, idToModify) == 0) {
            int choice;
            char input[256];

            while (1) { // Loop sampai user press exit
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
                scanf(" %d", &choice);
                getchar();

                switch (choice) { // Dibikin menu dengan switch case
                    case '1':
                        printf("Masukkan nama baru: ");
                        scanf(" %[^\n]", input);
                        strcpy(temp->nama, input);
                        printf("Nama berhasil diganti\n");
                        break;
                    case '2':
                        printf("Masukkan alamat baru: ");
                        scanf(" %[^\n]", input);
                        strcpy(temp->alamat, input);
                        printf("Alamat berhasil diganti\n");
                        break;
                    case '3':
                        printf("Masukkan kota baru: ");
                        scanf(" %[^\n]", input);
                        strcpy(temp->kota, input);
                        printf("Kota berhasil diganti\n");
                        break;
                    case '4':
                        printf("Masukkan tempat lahir baru: ");
                        scanf(" %[^\n]", input);
                        strcpy(temp->tempatLahir, input);
                        printf("Tempat lahir berhasil diganti\n");
                        break;
                    case '5':
                        printf("Masukkan tanggal lahir baru (format: dd mm yyyy or dd-mm-yy): ");
                        scanf(" %[^\n]", input);
                        char original[20];
                        temp->tgllahir = parseDate(input, original);
                        printf("Tanggal lahir berhasil diganti\n");
                        break;
                    case '6':
                        printf("Masukkan umur baru: ");
                        scanf(" %[^\n]", input);
                        temp->umur = atoi(input);
                        printf("Umur berhasil diganti\n");
                        break;
                    case '7':
                        printf("Masukkan no BPJS baru: ");
                        scanf(" %[^\n]", input);
                        strcpy(temp->BPJS, input);
                        printf("No BPJS berhasil diganti\n");
                        break;
                    case '8':
                        printf("Keluar.\n");
                        return;
                    default:
                        printf("Invalid.\n");
                        break;
                }
            }
        }
        temp = temp->next;
    }
    printf("Pasien dengan ID %s tidak ditemukan.\n", idToModify);
}

// int main(){
//     DataPasien* pasienHead = NULL;
//     modifyPatient(&pasienHead);
//     return 0;
// }

