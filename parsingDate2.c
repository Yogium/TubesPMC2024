// Bedanya sama yang pertama, yang pertama ngambil input buat tahun 1900an book 1 (Data Pasien) kalo di excel, ini buat 2000an book 2 (Riwayat datang, dll) di excel


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int day;
    int month;
    int year;
    char original[20];
} Date;

// Function to get the month number from the month name or abbreviation
int getMonthNumber(char* monthName) {
    char* bulan[] = { // Char nama bulan
        "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };
    char* bulanSingkat[] = { // Char nama bulan singkatan
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    
    for (int i = 0; i < 12; i++) { //Iterasi
        if (strcasecmp(monthName, bulan[i]) == 0 || strcasecmp(monthName, bulanSingkat[i]) == 0) { //Cek apabila inputnya sesuai sama nama bulan ato nama bulanSingkat
            return i + 1;
        }
    }
    return -1;
}


Date parseDate(char* dateString) {
    Date date;
    char monthName[20];

    if (sscanf(dateString, "%d %s %d", &date.day, monthName, &date.year) == 3) { //Tanggal dalam dd mm yyyy
        date.month = getMonthNumber(monthName); //Panggil fungsi getMonthNumber
        if (date.month == -1) { //Kalo nama bulan ga ketemu (Invalid)
            fprintf(stderr, "Nama bulan Invalid: %s\n", monthName);
            exit(EXIT_FAILURE);
        }
        sprintf(date.original, "%02d-%02d-%04d", date.day, date.month, date.year);

    } else if (sscanf(dateString, "%d-%3s-%2d", &date.day, monthName, &date.year) == 3) { //Buat tanggal yang dalam format dd-mmm-yy
        date.month = getMonthNumber(monthName); //Panggil fungsi getMonthNumber
        if (date.month == -1) { //Kalo nama bulan ga ketemu (invalid)
            fprintf(stderr, "Nama bulan singkatannya Invalid: %s\n", monthName);
            exit(EXIT_FAILURE);
        }

        if (date.year < 100) { //Case kalo yang tahunnya <100
            date.year += 2000; //Jadi ditambah 1900 biar format sama
        }
        sprintf(date.original, "%02d-%02d-%04d", date.day, date.month, date.year);

    } else { //Format diluar tadi, berarti invalid
        fprintf(stderr, "Invalid date format: %s\n", dateString);
        exit(EXIT_FAILURE);
    }
    
    return date;
}

int main() {
    FILE* file = fopen("dates2.txt", "r"); //INI INPUTNYA MASIH TXT
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    char line[256];
    Date* dates = NULL;
    int dateCount = 0;
    int capacity = 10;

    dates = malloc(capacity * sizeof(Date));
    if (!dates) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (dateCount >= capacity) {
            capacity *= 2;
            dates = realloc(dates, capacity * sizeof(Date));
            if (!dates) {
                perror("Failed to reallocate memory");
                return EXIT_FAILURE;
            }
        }

        Date date = parseDate(line);
        dates[dateCount++] = date;
    }
    fclose(file);

    printf("Dates in dd-mm-yyyy format:\n"); // PRINT
    for (int i = 0; i < dateCount; i++) {
        printf("%s\n", dates[i].original);
    }

    free(dates);

    return 0;
}
