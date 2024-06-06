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
#include "struct.h"

int income_monthly(DataKunjungan *head, int month, int year){
    DataKunjungan *curr = head;
    int income = 0;
    while(curr != NULL){
        if(curr->tanggal.month == month && curr->tanggal.year == year){
            income += tindakan[curr->tindakan].biaya + 140000 //biaya pemeriksaan dan pendaftaran;
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
            income += tindakan[curr->tindakan].biaya + 140000 //biaya pemeriksaan dan pendaftaran;
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
int average_income_per_year(DataKunjungan* head) {
    int count;
    int* years = get_unique_years(head, &count);

    int total_income = 0;
    for (int i = 0; i < count; i++) {
        total_income += income_yearly(head, years[i]);
    }

    free(years);

    return total_income / count;
}