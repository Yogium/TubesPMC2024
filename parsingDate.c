//Nama : Nicholas Darren
//Nama file : parsingDate.c
// Deskripsi : Fungsi ini menerima tanggal yang belom di format menjadi tanggal yang memiliki format yang sama yaitu dd-mm-yyyy
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

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

date parseDate(char* dateString, char* original) {
    date parsedDate;
    char monthName[20];

    if (sscanf(dateString, "%d %s %d", &parsedDate.date, monthName, &parsedDate.year) == 3) {
        parsedDate.month = getMonthNumber(monthName);
        if (parsedDate.month == 0) {
            fprintf(stderr, "Invalid month name: %s\n", monthName);
            return parsedDate;
        }
        sprintf(original, "%02d-%02d-%04d", parsedDate.date, parsedDate.month, parsedDate.year);
    } 
    else if (sscanf(dateString, "%d-%3s-%2d", &parsedDate.date, monthName, &parsedDate.year) == 3) {
        parsedDate.month = getMonthNumber(monthName);
        if (parsedDate.month == 0) {
            fprintf(stderr, "Invalid month name: %s\n", monthName);
            return parsedDate;
        }

        if (parsedDate.year < 100) {
            parsedDate.year += (parsedDate.year >= 50) ? 1900 : 2000;
        }
        sprintf(original, "%02d-%02d-%04d", parsedDate.date, parsedDate.month, parsedDate.year);
    } 
    else {
        fprintf(stderr, "Invalid date format: %s\n", dateString);
        return parsedDate;
    }
    
    return parsedDate;
}

int parseDataFromFile(const char* filename, date** dates, char*** originals, int* dateCount, int* capacity) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return 0;
    }
    char line[256];
    *dates = malloc(*capacity * sizeof(date));
    *originals = malloc(*capacity * sizeof(char*));
    if (!*dates || !*originals) {
        perror("Failed to allocate memory");
        fclose(file);
        return 0;
    }

    if (fgets(line, sizeof(line), file)) {
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = '\0';
            char* token = strtok(line, ",");
            int colomnCount = 0;
            char* dateString = NULL;

            while (token) {
                colomnCount++;
                if (filename == "Data_Pasien.csv" && colomnCount == 6) {
                    dateString = token;
                    break;
                } else if (filename == "Riwayat_Datang.csv" && colomnCount == 2) {
                    dateString = token;
                    break;
                }
                token = strtok(NULL, ",");
            }

            if (dateString && *dateCount < *capacity) {
                (*originals)[*dateCount] = malloc(20 * sizeof(char));
                if (!(*originals)[*dateCount]) {
                    perror("Failed to allocate memory");
                    fclose(file);
                    return 0;
                }
                (*dates)[*dateCount] = parseDate(dateString, (*originals)[*dateCount]);
                (*dateCount)++;
            } else if (*dateCount >= *capacity) {
                *capacity *= 2;
                *dates = realloc(*dates, *capacity * sizeof(date));
                *originals = realloc(*originals, *capacity * sizeof(char*));
                if (!*dates || !*originals) {
                    perror("Failed to reallocate memory");
                    fclose(file);
                    return 0;
                }
            }
        }
    }
    fclose(file);
    return 1;
}

int main() {
    int capacity_pasien = 10;
    int capacity_riwayat = 10;
    int dateCount_pasien = 0;
    int dateCount_riwayat = 0;
    date* dates_pasien = NULL;
    date* dates_riwayat = NULL;
    char** originals_pasien = NULL;
    char** originals_riwayat = NULL;

    if (!parseDataFromFile("Data_Pasien.csv", &dates_pasien, &originals_pasien, &dateCount_pasien, &capacity_pasien)) {
        fprintf(stderr, "Failed to parse data from Data_Pasien.csv\n");
        return 1;
    }

    printf("Dates from Data_Pasien.csv in dd-mm-yyyy format:\n");
    for (int i = 0; i < dateCount_pasien; i++) {
        printf("%s\n", originals_pasien[i]);
    }

    if (!parseDataFromFile("Riwayat_Datang.csv", &dates_riwayat, &originals_riwayat, &dateCount_riwayat, &capacity_riwayat)) {
        fprintf(stderr, "Failed to parse data from Riwayat_Datang.csv\n");
        for (int i = 0; i < dateCount_pasien; i++) {
            free(originals_pasien[i]);
        }
        free(originals_pasien);
        free(dates_pasien);
        return 1;
    }

    printf("\nDates from Riwayat_Datang.csv in dd-mm-yyyy format:\n");
    for (int i = 0; i < dateCount_riwayat; i++) {
        printf("%s\n", originals_riwayat[i]);
    }

    for (int i = 0; i < dateCount_pasien; i++) {
        free(originals_pasien[i]);
    }
    free(originals_pasien);
    free(dates_pasien);

    for (int i = 0; i < dateCount_riwayat; i++) {
        free(originals_riwayat[i]);
    }
    free(originals_riwayat);
    free(dates_riwayat);

    return 0;
}
