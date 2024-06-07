/*
Pembuat file: M Yoga Putrapratama/13222050
Nama file: visit_manipulate.c
Deskripsi: fungsi untuk melakukan hal di bawah kepada data kunjungan:
1. Menambahkan data kunjungan
2. Menghapus data kunjungan
3. Mengubah data kunjungan
4. Mencari dan menampilkan data kunjungan
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

DataKunjungan *createVisit(DataPasien *pasien, int diagnosis, int tindakan, date control){
    DataKunjungan *newVisit = (DataKunjungan*)malloc(sizeof(DataKunjungan));
    newVisit->index = pasien->index;
    newVisit->tanggal = control;
    strcpy(newVisit->patientID, pasien->patientID);
    newVisit->diagnosis = diagnosis;
    newVisit->tindakan = tindakan;
    newVisit->control = control;
    newVisit->next = NULL;
    return newVisit;
}

void addVisit(DataKunjungan **head, DataPasien *pasien){

}