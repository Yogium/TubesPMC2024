/*
Name Penulis    : Kennard Benaya Manli
Nama File       : penyakit.c

-> List penyakit dan jumlah pasien yang terkena penyakit tersebut

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "LinkedList.h"

typedef struct ListPenyakit{
    int index;
    char penyakit[20];
    int count;
    struct ListPenyakit *next;  
}ListPenyakit;  

ListPenyakit* diagbymonth(DataKunjungan *head, int month, int year){
    ListPenyakit *ListP = malloc(4*sizeof(ListPenyakit));
    for(int i = 0; i < 4; i++){
        ListP[i].index = i;
        strcpy(ListP[i].penyakit, penyakit[i]);
        ListP[i].count = 0;
        ListP[i].next = NULL; // Initialize next to NULL
    }

    DataKunjungan *curr = head;

    // Traverse curr
    while(curr != NULL){
       //printf("%d\n", curr->diagnosis);
       if (curr->tanggal.month == month && curr->tanggal.year == year) {
        ListP[curr->diagnosis].count++;
        curr = curr->next;
    }
    
    // Sort ListP by count in descending order
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                if (ListP[j].count > ListP[i].count) {
                    ListPenyakit temp = ListP[i];
                    ListP[i] = ListP[j];
                    ListP[j] = temp;
                }
            }
        }

        // Convert to linked list
        ListPenyakit *sortedhead = malloc(4*sizeof(ListPenyakit));
        sortedhead = &ListP[0];
        for(int i = 1; i < 4; i++){
            ListPenyakit *curr = sortedhead;
            while(curr->next != NULL){
                curr = curr->next;
            }
            curr->next = &ListP[i];
        }

        // Print list
        // ListPenyakit *curr2 = sortedhead;
        // while(curr2 != NULL){
        //     printf("%s: %d\n", curr2->penyakit, curr2->count);
        //     curr2 = curr2->next;
        // }
        return sortedhead;
    }
}

ListPenyakit* diagbyyear(DataKunjungan *head, int year){
    ListPenyakit *ListP = malloc(4*sizeof(ListPenyakit));
    for(int i = 0; i < 4; i++){
        ListP[i].index = i;
        strcpy(ListP[i].penyakit, penyakit[i]);
        ListP[i].count = 0;
        ListP[i].next = NULL; // Initialize next to NULL
    }

    DataKunjungan *curr = head;

    // Traverse curr
    while(curr != NULL){
       //printf("%d\n", curr->diagnosis);
       if (curr->tanggal.year == year) {
        ListP[curr->diagnosis].count++;
       }
        curr = curr->next;
    }
    
    // Sort ListP by count in descending order
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                if (ListP[j].count > ListP[i].count) {
                    ListPenyakit temp = ListP[i];
                    ListP[i] = ListP[j];
                    ListP[j] = temp;
                }
            }
        }

        // Convert to linked list
        ListPenyakit *sortedhead = &ListP[0];
        for(int i = 1; i < 4; i++){
            ListPenyakit *curr = sortedhead;
            while(curr->next != NULL){
                curr = curr->next;
            }
            curr->next = &ListP[i];
        }

        // Print list
        ListPenyakit *curr2 = sortedhead;
        // while(curr2 != NULL){
        //     printf("%s: %d\n", curr2->penyakit, curr2->count);
        //     curr2 = curr2->next;
        // }
        return sortedhead;
    }


ListPenyakit* diagsorter(DataKunjungan *head){
    ListPenyakit ListP[4];
    for(int i = 0; i < 4; i++){
        ListP[i].index = i;
        strcpy(ListP[i].penyakit, penyakit[i]);
        ListP[i].count = 0;
        ListP[i].next = NULL; // Initialize next to NULL
    }

    DataKunjungan *curr = head;

    // Traverse curr
    while(curr != NULL){
       //printf("%d\n", curr->diagnosis);
        ListP[curr->diagnosis].count++;
        curr = curr->next;
    }
    
    // Sort ListP by count in descending order
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (ListP[j].count > ListP[i].count) {
                ListPenyakit temp = ListP[i];
                ListP[i] = ListP[j];
                ListP[j] = temp;
            }
        }
    }

    // Convert to linked list
    ListPenyakit *sortedhead = malloc(4*sizeof(ListPenyakit));
    for(int i = 1; i < 4; i++){
        ListPenyakit *curr = sortedhead;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = &ListP[i];
    }

    // Print list
    // ListPenyakit *curr2 = sortedhead;
    // while(curr2 != NULL){
    //     printf("%s: %d\n", curr2->penyakit, curr2->count);
    //     curr2 = curr2->next;
    // }
    return sortedhead;
}

// int main(){
//     DataKunjungan *head = NULL;
//     parseDataKunjunganFromFile("Riwayat_Datang.csv", &head);
//     ListPenyakit *head2 = malloc(4*sizeof(ListPenyakit));
//     head2 = diagbyyear(head, 2023);
//     printf("linkedlist\n");
//     while(head2 != NULL){
//         printf("%s: %d\n", head2->penyakit, head2->count);
//         head2 = head2->next;
//     }
//     free(head2);
// }
