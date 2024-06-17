
/*
*Penulis    : M. Yoga Putrapratama/13222050
*Nama File  : struct.h
*Deskripsi  : File berisi struct yang akan dipakai di dalam program
*/

#ifndef STRUCT_H
#define STRUCT_H

typedef struct{
    char nama[20];
    int biaya;
}Tindakan;

extern char penyakit[4][20] = {"Dehidrasi", "Keseleo", "Masuk Angin", "Pusing"};

extern Tindakan tindakan[6] = {{"Pendaftaran", 15000}, {"Pemeriksaan", 125000}, {"Vaksinasi", 100000}, {"Cek gula darah", 25000}, {"Pemasangan infus", 125000}, {"Pengobatan", 150000}};

extern char bulan[12][20] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

//struct untuk tanggal
typedef struct{
    int date;
    int month;
    int year;
}date;

//struct untuk data pasien
typedef struct DataP{
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
}DataPasien;

//struct untuk data kunjungan
typedef struct DataK{
    int index;
    date tanggal;
    char patientID[11];
    int diagnosis;
    int tindakan;
    date control;
    struct DataK *next;
}DataKunjungan;

//Convert diagnosis to integer index from array penyakit
//input: penyakit(array of penyakit in struct.h) diagnosis(diagnosis to be converted)
int getDiagnosis(char penyakit[4][20], char *diagnosis){
    for(int i = 0; i < 4; i++){
        if(strcmp(penyakit[i], diagnosis) == 0){
            return i;
        }
    }
    return -1;
}

//Convert tindakan to integer index from array tindakan
//input: tindakan(array of tindakan in struct.h) action(tindakan to be converted)
int getTindakan(Tindakan tindakan[6], char *action){
    for(int i = 0; i < 6; i++){
        if(strcmp(tindakan[i].nama, action) == 0){
            return i;
        }
    }
    return -1;
}

#endif
