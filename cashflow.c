/*
Name Penulis    : Kennard Benaya Manli
Nama File       : cashflow.c

->pendapatan bulanan
->pendapatan tahunan
->rata-rata pendapatan per tahun

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "struct.h"
#include "LinkedList.h"


int income_monthly(DataKunjungan *head, int month, int year){
    DataKunjungan *curr = head;
    int income = 0;
    while(curr != NULL){
        if(curr->tanggal.month == month && curr->tanggal.year == year){
            income += tindakan[curr->tindakan].biaya + 140000; //biaya pemeriksaan dan pendaftaran;
        }
        curr = curr->next;
    }
    return income;
}

int income_yearly(DataKunjungan *head, int year){
    DataKunjungan *curr = head;
    int income = 0;
    while(curr != NULL){
        if(curr->tanggal.year == year){
            income += tindakan[curr->tindakan].biaya + 140000 ;//biaya pemeriksaan dan pendaftaran;
        }
        curr = curr->next;
    }
    return income;
}


// function to compare two integers (for qsort)
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// function to get unique years from linked list
int* get_unique_years(DataKunjungan* head, int* count) {
    int size = 10; // initial size
    int* years = malloc(size * sizeof(int));
    *count = 0; // number of unique years

    DataKunjungan* curr = head;
    while (curr != NULL) {
        if (*count >= size) { // if array is full, double its size
            size *= 2;
            years = realloc(years, size * sizeof(int));
        }
        years[(*count)++] = curr->tanggal.year;
        curr = curr->next;
    }

    // sort the array
    qsort(years, *count, sizeof(int), compare);

    // remove duplicates
    int j = 0;
    for (int i = 1; i < *count; i++) {
        if (years[i] != years[j]) {
            years[++j] = years[i];
        }
    }
    *count = j + 1;

    // shrink array to its actual size
    years = realloc(years, *count * sizeof(int));

    return years;
}

// function to get average income per year
float average_income_per_year(DataKunjungan* head) {
    int count;
    int* years = get_unique_years(head, &count);

    int total_income = 0;
    for (int i = 0; i < count; i++) {
        total_income += income_yearly(head, years[i]);
    }

    free(years);

    return total_income / count*1.0;
}

void cashflow(DataKunjungan *head){
    setlocale(LC_NUMERIC, "");
    int month, year;

    //selector
    int choice;
    printf("Pilih menu:\n");
    printf("1. Pendapatan bulanan\n");
    printf("2. Pendapatan tahunan\n");
    printf("3. Rata-rata pendapatan per tahun\n");
    printf("Pilihan: ");
    scanf("%d", &choice);

    switch (choice){
        case 1:
            printf("Masukkan bulan dan tahun (MM YYYY): ");
            scanf("%d %d", &month, &year);

            printf("Pendapatan %d/%d : Rp. %'d\n", month, year, income_monthly(head, month, year));
            break;
        case 2:
            printf("Masukkan tahun (YYYY): ");
            scanf("%d", &year);
            printf("Pendapatan %d : Rp. %d'\n",year, income_yearly(head, year));
            break;
        case 3:
            printf("Pendapatan rata-rata per tahun: Rp. %'.2f\n", average_income_per_year(head));
            break;
    }
}


