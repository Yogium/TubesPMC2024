// Bedanya sama yang pertama, yang pertama ngambil input buat tahun 1900an book 1 (Data Pasien) kalo di excel, ini buat 2000an book 2 (Riwayat datang, dll) di excel
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

// Function to get the month number from the month name or abbreviation
int getMonthNumber(char* monthName) {
    char* bulan[] = { // Char nama bulan
        "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };
    char* bulanSingkat[] = { // Char nama bulan singkatan
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    
    for (int i = 0; i < 12; i++) { // Iterasi
        if (strcasecmp(monthName, bulan[i]) == 0 || strcasecmp(monthName, bulanSingkat[i]) == 0) { // Cek apabila inputnya sesuai sama nama bulan ato nama bulanSingkat
            return i + 1;
        }
    }
    return 0;
}

date parseDate(char* dateString, char* original) {
    date parsedDate;
    char monthName[20];

    if (sscanf(dateString, "%d %s %d", &parsedDate.date, monthName, &parsedDate.year) == 3) { // Tanggal dalam dd mm yyyy
        parsedDate.month = getMonthNumber(monthName); // Panggil fungsi getMonthNumber
        if (parsedDate.month == 0) { // Kalo nama bulan ga ketemu (Invalid)
            fprintf(stderr, "Nama bulan Invalid: %s\n", monthName);
            exit(EXIT_FAILURE);
        }
        sprintf(original, "%02d-%02d-%04d", parsedDate.date, parsedDate.month, parsedDate.year);

    } else if (sscanf(dateString, "%d-%3s-%2d", &parsedDate.date, monthName, &parsedDate.year) == 3) { // Buat tanggal yang dalam format dd-mmm-yy
        parsedDate.month = getMonthNumber(monthName); // Panggil fungsi getMonthNumber
        if (parsedDate.month == 0) { // Kalo nama bulan ga ketemu (invalid)
            fprintf(stderr, "Nama bulan singkatannya Invalid: %s\n", monthName);
            exit(EXIT_FAILURE);
        }

        if (parsedDate.year < 100) { // Case kalo yang tahunnya <100
            parsedDate.year += 2000; // Jadi ditambah 2000 biar format sama
        }
        sprintf(original, "%02d-%02d-%04d", parsedDate.date, parsedDate.month, parsedDate.year);

    } else { // Format diluar tadi, berarti invalid
        fprintf(stderr, "Invalid date format: %s\n", dateString);
        exit(EXIT_FAILURE);
    }
    
    return parsedDate;
}

int main() {
    FILE* file = fopen("dates.txt", "r"); // INI INPUTNYA MASIH TXT
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    char line[256];
    date* dates = NULL;
    char (*originals)[20] = NULL;
    int dateCount = 0;
    int capacity = 10;

    dates = malloc(capacity * sizeof(date));
    originals = malloc(capacity * sizeof(*originals));
    if (!dates || !originals) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (dateCount >= capacity) {
            capacity *= 2;
            dates = realloc(dates, capacity * sizeof(date));
            originals = realloc(originals, capacity * sizeof(*originals));
            if (!dates || !originals) {
                perror("Failed to reallocate memory");
                return EXIT_FAILURE;
            }
        }

        dates[dateCount] = parseDate(line, originals[dateCount]);
        dateCount++;
    }
    fclose(file);

    printf("Dates in dd-mm-yyyy format:\n"); // PRINT
    for (int i = 0; i < dateCount; i++) {
        printf("%s\n", originals[i]);
    }

    free(dates);
    free(originals);

    return 0;
}
