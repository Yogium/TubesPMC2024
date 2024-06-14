//Nama : Nicholas Darren
//Nama file : parsingDate.c
// Deskripsi : Fungsi ini menerima tanggal yang belom di format menjadi tanggal yang memiliki format yang sama yaitu dd-mm-yyyy
#ifndef PARSINGDATE_H
#define PARSINGDATE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

int getMonthNumber(char* monthName) { //Fungsi untuk ambil nama bulan lalu jadi int
    char* bulan[] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };
    char* bulanSingkat[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    for (int i = 0; i < 12; i++) { //Jadinya Januari 1, Februari 2, ...
        if (strcasecmp(monthName, bulan[i]) == 0 || strcasecmp(monthName, bulanSingkat[i]) == 0) {
            return i + 1;
        }
    }
    return 0;
}

date parseDate(char* dateString, char* original) { //Fungsi utama buat parsing tanggal
    date parsedDate;
    char monthName[20];

    if (sscanf(dateString, "%d %s %d", &parsedDate.date, monthName, &parsedDate.year) == 3) { //Parse tanggal yang Formatnya DD MMMM YY
        parsedDate.month = getMonthNumber(monthName);
        if (parsedDate.month == 0) { // Kalo nomor bulan invalid, print error
            fprintf(stderr, "Invalid month name: %s\n", monthName);
            exit(EXIT_FAILURE);
        }
        sprintf(original, "%02d-%02d-%04d", parsedDate.date, parsedDate.month, parsedDate.year); //Format tanggal jadi DD-MM-YYYY
    } 
    else if (sscanf(dateString, "%d-%3s-%2d", &parsedDate.date, monthName, &parsedDate.year) == 3) {//Parse tanggal yang Formatnya DD-Mmm-YY
        parsedDate.month = getMonthNumber(monthName);
        if (parsedDate.month == 0) { // Kalo nomor bulan invalid, print error
            fprintf(stderr, "Invalid month name: %s\n", monthName);
            exit(EXIT_FAILURE);
        }

        if (parsedDate.year < 100) { //Kalo tahun < 100 maka ditambah 1900 ato 2000 tergantung.
            parsedDate.year += (parsedDate.year >= 50) ? 1900 : 2000; //Ini pake ASUMSI kalo tahunnya 50<= YYYY < 100 bakal nambah 1900. Dan kalo YYYY<50 bakal nambah 2000
        }
        sprintf(original, "%02d-%02d-%04d", parsedDate.date, parsedDate.month, parsedDate.year);
    } 
    else { //Diluar format tersebut invalid
        fprintf(stderr, "Invalid date format: %s\n", dateString);
        exit(EXIT_FAILURE);
    }
    
    return parsedDate;
}

int parseDataFromFile(const char* filename, date** dates, char*** originals, int* dateCount, int* capacity) { //Fungsi buat parse data dari CSV dan simpen tanggal
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return 0;
    }
    char line[256];
    //Alokasi memori buat string dates & orignials
    *dates = malloc(*capacity * sizeof(date));
    *originals = malloc(*capacity * sizeof(char*));
    if (!*dates || !*originals) {
        perror("Failed to allocate memory");
        fclose(file);
        return 0;
    }

    // Skip header
    if (fgets(line, sizeof(line), file)) {
        while (fgets(line, sizeof(line), file)) { // Read setiap line
            line[strcspn(line, "\n")] = '\0';

            // CSV dipisah dengan koma
            char* token = strtok(line, ",");
            int colomnCount = 0;
            char* dateString = NULL;

            while (token) {
                colomnCount++;
                if (filename == "Data_Pasien.csv" && colomnCount == 6) { //Kalau input dari Data_Pasien.csv
                    dateString = token; // Tanggal ada di kolom 6 in Data_Pasien.csv
                    break;
                } else if (filename == "Riwayat_Datang.csv" && colomnCount == 2) { //Kalau input dari Riwayat_Datang.csv
                    dateString = token; // Tanggal ada di kolom 2 Riwayat_Datang.csv
                    break;
                }
                token = strtok(NULL, ","); //Pindah ke token selanjutnya
            }

            if (dateString && *dateCount < *capacity) { // Kalo dateCount masih dalam kapasitas
                (*originals)[*dateCount] = malloc(20 * sizeof(char)); //Alokasi memori untuk string originals
                if (!(*originals)[*dateCount]) { //Cek alokasi memori
                    perror("Failed to allocate memory");
                    fclose(file);
                    return 0;
                }
                (*dates)[*dateCount] = parseDate(dateString, (*originals)[*dateCount]); //Simpan tanggal parsed di array dates
                (*dateCount)++;
            } else if (*dateCount >= *capacity) { //Kalo dateCount lebih dari kapasitas
                *capacity *= 2;
                *dates = realloc(*dates, *capacity * sizeof(date)); //Alokasi memori lagi
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

#endif