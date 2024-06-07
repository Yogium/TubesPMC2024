#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Struktur untuk menyimpan tanggal
typedef struct {
    int date;
    int month;
    int year;
} date;

// Struktur untuk menyimpan data pasien
typedef struct DataP {
    int index;
    char nama[100];
    char alamat[100];
    char kota[50];
    char tempatLahir[50];
    date tgllahir;
    int umur;
    char BPJS[11];
    char patientID[11];
    struct DataP *next;
} DataPasien;

// Struktur untuk menyimpan data kunjungan
typedef struct DataK {
    int index;
    date tanggal;
    char patientID[11];
    int diagnosis;
    int tindakan;
    date control;
    struct DataK *next;
} DataKunjungan;

// Daftar penyakit yang tersedia
char penyakit[4][20] = {"Dehidrasi", "Keseleo", "Masuk Angin", "Pusing"};

// Struktur untuk menyimpan jenis tindakan dan biayanya
typedef struct {
    char tindakan[20];
    int biaya;
} Tindakan;

// Daftar tindakan yang tersedia
Tindakan tindakan[6] = {{"Pendaftaran", 15000}, {"Pemeriksaan", 125000}, {"Vaksinasi", 100000}, {"Cek gula darah", 25000}, {"Pemasangan infus", 125000}, {"Pengobatan", 150000}};

// Fungsi untuk mendapatkan nomor bulan dari nama bulan
int getMonthNumber(char* monthName) {
    char* bulan[] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };
    char* bulanSingkat[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    for (int i = 0; i < 12; i++) {
        if (strcasecmp(monthName, bulan[i]) == 0 || strcasecmp(monthName, bulanSingkat[i]) == 0) {
            return i + 1;
        }
    }
    return 0;
}

// Fungsi untuk mengurai string tanggal menjadi struct date
date parseDate(char* dateString, char* original) {
    date parsedDate;
    char monthName[20];

    if (sscanf(dateString, "%d %s %d", &parsedDate.date, monthName, &parsedDate.year) == 3) {
        parsedDate.month = getMonthNumber(monthName);
        if (parsedDate.month == 0) {
            fprintf(stderr, "Invalid month name: %s\n", monthName);
            exit(EXIT_FAILURE);
        }
        sprintf(original, "%02d-%02d-%04d", parsedDate.date, parsedDate.month, parsedDate.year);
    } 
    else if (sscanf(dateString, "%d-%3s-%2d", &parsedDate.date, monthName, &parsedDate.year) == 3) {
        parsedDate.month = getMonthNumber(monthName);
        if (parsedDate.month == 0) {
            fprintf(stderr, "Invalid month name: %s\n", monthName);
            exit(EXIT_FAILURE);
        }

        if (parsedDate.year < 100) {
            parsedDate.year += (parsedDate.year >= 50) ? 1900 : 2000;
        }
        sprintf(original, "%02d-%02d-%04d", parsedDate.date, parsedDate.month, parsedDate.year);
    } 
    else {
        fprintf(stderr, "Invalid date format: %s\n", dateString);
        exit(EXIT_FAILURE);
    }
    
    return parsedDate;
}

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
        printf("Tindakan: %s (Rp %d)\n", tindakan[temp->tindakan].tindakan, tindakan[temp->tindakan].biaya);
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

