#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definisi struct untuk tanggal
typedef struct {
    int day;
    int month;
    int year;
    char original[20];
} Date;

// Definisi struct untuk data pasien
typedef struct Patient {
    int id;
    char name[100];
    char address[100];
    char city[50];
    char birthplace[50];
    Date birthdate;
    int age;
    char bpjs[20];
    struct Patient* next;
} Patient;

// Definisi struct untuk riwayat kedatangan
typedef struct Visit {
    Date visitDate;
    int patientId;
    char diagnosis[100];
    char action[100];
    char control[50];
    float cost;
    struct Visit* next;
} Visit;

// Fungsi untuk mendapatkan nomor bulan dari nama bulan
int getMonthNumber(char* monthName) {
    char* bulan[] = { "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember" };
    char* bulanSingkat[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    for (int i = 0; i < 12; i++) {
        if (strcasecmp(monthName, bulan[i]) == 0 || strcasecmp(monthName, bulanSingkat[i]) == 0) {
            return i + 1;
        }
    }
    return -1;
}

// Fungsi untuk parsing tanggal dari string (pertama)
Date parseDate(char* dateString) {
    Date date;
    char monthName[20];

    if (sscanf(dateString, "%d %s %d", &date.day, monthName, &date.year) == 3) {
        date.month = getMonthNumber(monthName);
        if (date.month == -1) {
            fprintf(stderr, "Nama bulan Invalid: %s\n", monthName);
            exit(EXIT_FAILURE);
        }
        sprintf(date.original, "%02d-%02d-%04d", date.day, date.month, date.year);
    } else if (sscanf(dateString, "%d-%3s-%2d", &date.day, monthName, &date.year) == 3) {
        date.month = getMonthNumber(monthName);
        if (date.month == -1) {
            fprintf(stderr, "Nama bulan singkatannya Invalid: %s\n", monthName);
            exit(EXIT_FAILURE);
        }
        if (date.year < 100) {
            date.year += 1900;
        }
        sprintf(date.original, "%02d-%02d-%04d", date.day, date.month, date.year);
    } else {
        fprintf(stderr, "Invalid date format: %s\n", dateString);
        exit(EXIT_FAILURE);
    }
    
    return date;
}

// Fungsi untuk parsing tanggal dari string (kedua, untuk visit)
Date parseDateVisit(char* dateString) {
    Date date;
    char monthName[20];

    if (sscanf(dateString, "%d %s %d", &date.day, monthName, &date.year) == 3) {
        date.month = getMonthNumber(monthName);
        if (date.month == -1) {
            fprintf(stderr, "Nama bulan Invalid: %s\n", monthName);
            exit(EXIT_FAILURE);
        }
        sprintf(date.original, "%02d-%02d-%04d", date.day, date.month, date.year);
    } else if (sscanf(dateString, "%d-%3s-%2d", &date.day, monthName, &date.year) == 3) {
        date.month = getMonthNumber(monthName);
        if (date.month == -1) {
            fprintf(stderr, "Nama bulan singkatannya Invalid: %s\n", monthName);
            exit(EXIT_FAILURE);
        }
        if (date.year < 100) {
            date.year += 2000;
        }
        sprintf(date.original, "%02d-%02d-%04d", date.day, date.month, date.year);
    } else {
        fprintf(stderr, "Invalid date format: %s\n", dateString);
        exit(EXIT_FAILURE);
    }
    
    return date;
}

// Fungsi untuk membuat node baru untuk pasien
Patient* createPatient(int id, char* name, char* address, char* city, char* birthplace, Date birthdate, int age, char* bpjs) {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    newPatient->id = id;
    strcpy(newPatient->name, name);
    strcpy(newPatient->address, address);
    strcpy(newPatient->city, city);
    strcpy(newPatient->birthplace, birthplace);
    newPatient->birthdate = birthdate;
    newPatient->age = age;
    strcpy(newPatient->bpjs, bpjs);
    newPatient->next = NULL;
    return newPatient;
}

// Fungsi untuk membuat node baru untuk riwayat kedatangan
Visit* createVisit(Date visitDate, int patientId, char* diagnosis, char* action, char* control, float cost) {
    Visit* newVisit = (Visit*)malloc(sizeof(Visit));
    newVisit->visitDate = visitDate;
    newVisit->patientId = patientId;
    strcpy(newVisit->diagnosis, diagnosis);
    strcpy(newVisit->action, action);
    strcpy(newVisit->control, control);
    newVisit->cost = cost;
    newVisit->next = NULL;
    return newVisit;
}

// Fungsi untuk menambah node di akhir linked list pasien
void appendPatient(Patient** head, int id, char* name, char* address, char* city, char* birthplace, Date birthdate, int age, char* bpjs) {
    Patient* newPatient = createPatient(id, name, address, city, birthplace, birthdate, age, bpjs);
    if (*head == NULL) {
        *head = newPatient;
    } else {
        Patient* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPatient;
    }
}

// Fungsi untuk menambah node di akhir linked list riwayat kedatangan
void appendVisit(Visit** head, Date visitDate, int patientId, char* diagnosis, char* action, char* control, float cost) {
    Visit* newVisit = createVisit(visitDate, patientId, diagnosis, action, control, cost);
    if (*head == NULL) {
        *head = newVisit;
    } else {
        Visit* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newVisit;
    }
}

// Fungsi untuk mencetak linked list pasien
void printPatients(Patient* head) {
    Patient* temp = head;
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Address: %s, City: %s, Birthplace: %s, Birthdate: %s, Age: %d, BPJS: %s\n", 
               temp->id, temp->name, temp->address, temp->city, temp->birthplace, temp->birthdate.original, temp->age, temp->bpjs);
        temp = temp->next;
    }
}

// Fungsi untuk mencetak linked list riwayat kedatangan
void printVisits(Visit* head) {
    Visit* temp = head;
    while (temp != NULL) {
        printf("Visit Date: %s, Patient ID: %d, Diagnosis: %s, Action: %s, Control: %s, Cost: %.2f\n", 
               temp->visitDate.original, temp->patientId, temp->diagnosis, temp->action, temp->control, temp->cost);
        temp = temp->next;
    }
}

int main() {
    FILE* file = fopen("/mnt/data/DataPMC20232024.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return EXIT_FAILURE;
    }

    char line[256];
    Patient* patientHead = NULL;
    Visit* visitHead = NULL;

    // Membaca data pasien
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Patients:") != NULL) {
            break;
        }
    }
    
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Visits:") != NULL) {
            break;
        }
        int id, age;
        char name[100], address[100], city[50], birthplace[50], birthdateStr[20], bpjs[20];
        sscanf(line, "%d,%99[^,],%99[^,],%49[^,],%49[^,],%19[^,],%d,%19[^,]", &id, name, address, city, birthplace, birthdateStr, &age, bpjs);
        Date birthdate = parseDate(birthdateStr);
        appendPatient(&patientHead, id, name, address, city, birthplace, birthdate, age, bpjs);
    }

    // Membaca riwayat kedatangan
    while (fgets(line, sizeof(line), file)) {
        char visitDateStr[20], diagnosis[100], action[100], control[50];
        int patientId;
        float cost;
        sscanf(line, "%19[^,],%d,%99[^,],%99[^,],%49[^,],%f", visitDateStr, &patientId, diagnosis, action, control, &cost);
        Date visitDate = parseDateVisit(visitDateStr);
        appendVisit(&visitHead, visitDate, patientId, diagnosis, action, control, cost);
    }

    fclose(file);

    printf("Patients:\n");
    printPatients(patientHead);

    printf("\nVisits:\n");
    printVisits(visitHead);

    return 0;
}