
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


typedef struct{
    int date;
    int month;
    int year;
}date;

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

typedef struct DataK{
    int index;
    date tanggal;
    char patientID[11];
    int diagnosis;
    int tindakan;
    date control;
    struct DataK *next;
}DataKunjungan;

#endif
