#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include "gui_commonfunc.h"
#include "modifyPatient.c"
#include <stdlib.h>
#include "searchPatient.c"
#include "deletePatient.c"
#include "addPatient.c"
#include "parsingDate.h"

#ifndef GUI_PASIEN_H

enum patientColumns{
    COL_NAME,
    COL_ADDRESS,
    COL_CITY,
    COL_BIRTHPLACE,
    COL_BIRTHDATE,
    COL_AGE,
    COL_BPJS,
    COL_PID,
    PATIENT_N_COLS
};


void getTextInput(GtkWidget *entry, gpointer data){
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));
}
#endif

struct addPatientData{
    DataPasien *pasien;
    GtkWidget *entry_name;
    GtkWidget *entry_address;
    GtkWidget *entry_city;
    GtkWidget *entry_birthdate;
    GtkWidget *entry_age;
    GtkWidget *entry_bpjs;
    GtkWidget *entry_PID;
    GtkWidget *label_confirm;
};

void addPatientSaveClicked(GtkWidget *widget, gpointer data){
    //taking the data from entries
    DataPasien *pasien = ((struct addPatientData*)data)->pasien;
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(((struct addPatientData*)data)->entry_name));
    const gchar *address = gtk_entry_get_text(GTK_ENTRY(((struct addPatientData*)data)->entry_address));
    const gchar *city = gtk_entry_get_text(GTK_ENTRY(((struct addPatientData*)data)->entry_city));
    const gchar *birthdate = gtk_entry_get_text(GTK_ENTRY(((struct addPatientData*)data)->entry_birthdate));
    const gchar *age = gtk_entry_get_text(GTK_ENTRY(((struct addPatientData*)data)->entry_age));
    const gchar *bpjs = gtk_entry_get_text(GTK_ENTRY(((struct addPatientData*)data)->entry_bpjs));
    const gchar *PID = gtk_entry_get_text(GTK_ENTRY(((struct addPatientData*)data)->entry_PID));
    GtkWidget *label_confirm = ((struct addPatientData*)data)->label_confirm;

    //convert to strings
    char namestr[50];
    char addressstr[100];
    char citystr[20];
    char birthdatestr[20];
    char agestr[3];
    char bpjsstr[20];
    char PIDstr[11];

    strcpy(namestr, name);
    strcpy(addressstr, address);
    strcpy(citystr, city);
    strcpy(birthdatestr, birthdate);
    strcpy(agestr, age);
    strcpy(bpjsstr, bpjs);
    strcpy(PIDstr, PID);

    //split birthdaystr into kota lahir and tanggal lahir
    char birthcity[20];
    date Fbirthdate;
    char *token = strtok(birthdatestr, "/");
    if(token != NULL){
        strcpy(birthcity, token);
        token = strtok(NULL, "/");
        if(token != NULL){
            Fbirthdate.date = atoi(token);
            token = strtok(NULL, "/");
            if(token != NULL){
                Fbirthdate.month = atoi(token);
                token = strtok(NULL, "/");
                if(token != NULL){
                    Fbirthdate.year = atoi(token);
                }
            }
        }
    }
    

    //add the data
    addPatient(&pasien, namestr, addressstr, citystr, birthcity, Fbirthdate, atoi(agestr), bpjsstr, PIDstr);
    gtk_label_set_text(GTK_LABEL(label_confirm), "Data berhasil ditambahkan");
}

void addPatientClicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label_general;
    GtkWidget *entry_name;
    GtkWidget *entry_address;
    GtkWidget *entry_city;
    GtkWidget *entry_birthdate;
    GtkWidget *entry_age;
    GtkWidget *entry_bpjs;
    GtkWidget *entry_PID;
    GtkWidget *button_save;/*button untuk menyimpan data pasien*/
    GtkWidget *button_cancel;/*button untuk membatalkan input data pasien*/
    GtkWidget *label_confirm;

    struct addPatientData *addData = malloc(sizeof(struct addPatientData));
    addData->pasien = (DataPasien*)data;


    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Tambah Data Pasien");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    
    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create label general
    label_general = gtk_label_new("Input data pasien Baru lalu klik simpan");

    //create label name
    entry_name = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_name), "Nama Pasien");
    addData->entry_name = entry_name;

    //create label address
    entry_address = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_address), "Alamat Pasien");
    addData->entry_address = entry_address;

    //create label city
    entry_city = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_city), "Kota");
    addData->entry_city = entry_city;

    //create label birthdate
    entry_birthdate= gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_birthdate), "Tempat dan Tanggal Lahir (dalam format kota/dd/mm/yyyy)");
    addData->entry_birthdate = entry_birthdate;

    //create label age
    entry_age= gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_age), "Umur Pasien");
    addData->entry_age = entry_age;

    //create label BPJS
    entry_bpjs= gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_bpjs), "Nomor BPJS Pasien");
    addData->entry_bpjs = entry_bpjs;

    //create label PID
    entry_PID= gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_PID), "Patient ID");
    addData->entry_PID = entry_PID;

    //create label
    label_confirm = gtk_label_new("");
    addData->label_confirm = label_confirm;

    //save button
    button_save = gtk_button_new_with_label("Simpan");
    g_signal_connect(button_save, "clicked", G_CALLBACK(addPatientSaveClicked), addData);

    //cancel button
    button_cancel = gtk_button_new_with_label("Batal");
    g_signal_connect(button_cancel, "clicked", G_CALLBACK(closeWindow), window);

    //pack all widget
    gtk_box_pack_start(GTK_BOX(vbox), label_general, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_name, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_address, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_city, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_birthdate, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_age, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_bpjs, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_PID, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label_confirm, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_save, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_cancel, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}

struct searchPatientData{
    DataPasien *pasien;
    GtkWidget *entryChoice;
    GtkListStore *searchList;
};

void searchPatientButtonClicked(GtkWidget *widget, gpointer data){
    if(data == NULL){
        printf("Data tidak ditemukan\n");
        return;
    }
    DataPasien *pasien = ((struct searchPatientData*)data)->pasien;
    const gchar *input = gtk_entry_get_text(GTK_ENTRY(((struct searchPatientData*)data)->entryChoice));
    DataPasien *foundPasienHead = NULL;
    char searchID[20];
    strcpy(searchID, input);
    foundPasienHead = searchPatient(pasien, searchID);
    DataPasien *searched = foundPasienHead;
    GtkListStore *searchList = ((struct searchPatientData*)data)->searchList;
    gtk_list_store_clear(searchList);
    while(searched != NULL){
        GtkTreeIter iter;
        char birthdate[20];
        sprintf(birthdate, "%d-%d-%d", searched->tgllahir.date, searched->tgllahir.month, searched->tgllahir.year);
        gtk_list_store_insert_with_values(searchList, &iter, -1, COL_NAME, searched->nama, COL_ADDRESS, searched->alamat, COL_CITY, searched->kota, COL_BIRTHPLACE, searched->tempatLahir, COL_BIRTHDATE, birthdate , COL_AGE, searched->umur, COL_BPJS, searched->BPJS, COL_PID, searched->patientID, -1);
        searched = searched->next;
    }
}

void searchPatientClicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *entryChoice;
    GtkWidget *button_search;/*button untuk mencari data pasien*/
    GtkListStore *searchList;
    GtkTreeViewColumn *column;
    GtkWidget *view;

    DataPasien *pasien = (DataPasien*)data;
    struct searchPatientData *searchData = malloc(sizeof(struct searchPatientData));
    searchData->pasien = pasien;

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Cari Data Pasien");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    
    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create entry choice
    entryChoice = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryChoice), "Masukkan ID pasien yang ingin dicari");
    searchData->entryChoice = entryChoice;


    //create list store
    searchList = gtk_list_store_new(PATIENT_N_COLS, G_TYPE_STRING/*NAMA*/, G_TYPE_STRING/*ALAMAT*/, G_TYPE_STRING/*KOTA*/, G_TYPE_STRING/*TEMPAT LAHIR*/, G_TYPE_STRING/*TANGGAL LAHIR*/, G_TYPE_INT/*UMUR*/, G_TYPE_STRING/*BPJS*/, G_TYPE_STRING/*PID*/);
    view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(searchList));

    column = gtk_tree_view_column_new_with_attributes("Nama", gtk_cell_renderer_text_new(), "text", COL_NAME, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Alamat", gtk_cell_renderer_text_new(), "text", COL_ADDRESS, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Kota", gtk_cell_renderer_text_new(), "text", COL_CITY, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Tempat Lahir", gtk_cell_renderer_text_new(), "text", COL_BIRTHPLACE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Tanggal Lahir", gtk_cell_renderer_text_new(), "text", COL_BIRTHDATE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Umur", gtk_cell_renderer_text_new(), "text", COL_AGE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("BPJS", gtk_cell_renderer_text_new(), "text", COL_BPJS, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Patient ID", gtk_cell_renderer_text_new(), "text", COL_PID, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    searchData->searchList = searchList;

    //click search button
    button_search = gtk_button_new_with_label("Cari");
    g_signal_connect(button_search, "clicked", G_CALLBACK(searchPatientButtonClicked), searchData);
    
    //pack all widget
    gtk_box_pack_start(GTK_BOX(vbox), entryChoice, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_search, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}

struct editPatientData{
    GtkWidget *label;
    DataPasien *pasien;
    GtkWidget *PIDEntry;
    GtkWidget *nameEntry;
    GtkWidget *addressEntry;
    GtkWidget *cityEntry;
    GtkWidget *birthdateEntry;
    GtkWidget *ageEntry;
    GtkWidget *bpjsEntry;
};

void editPatientSaveClicked(GtkWidget *widget, gpointer data){
    //taking the data from entries
    DataPasien *pasien = ((struct editPatientData*)data)->pasien;
    const gchar *PID = gtk_entry_get_text(GTK_ENTRY(((struct editPatientData*)data)->PIDEntry));
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(((struct editPatientData*)data)->nameEntry));
    const gchar *address = gtk_entry_get_text(GTK_ENTRY(((struct editPatientData*)data)->addressEntry));
    const gchar *city = gtk_entry_get_text(GTK_ENTRY(((struct editPatientData*)data)->cityEntry));
    const gchar *birthdate = gtk_entry_get_text(GTK_ENTRY(((struct editPatientData*)data)->birthdateEntry));
    const gchar *age = gtk_entry_get_text(GTK_ENTRY(((struct editPatientData*)data)->ageEntry));
    const gchar *bpjs = gtk_entry_get_text(GTK_ENTRY(((struct editPatientData*)data)->bpjsEntry));
    GtkWidget *label = ((struct editPatientData*)data)->label;


    //convert to strings
    char PIDstr[11];
    char namestr[50];
    char addressstr[100];
    char citystr[20];
    char birthdatestr[20];
    char agestr[3];
    char bpjsstr[20];

    strcpy(PIDstr, PID);
    strcpy(namestr, name);
    strcpy(addressstr, address);
    strcpy(citystr, city);
    strcpy(birthdatestr, birthdate);
    strcpy(agestr, age);
    strcpy(bpjsstr, bpjs);

    //split birthdaystr into kota lahir and tanggal lahir
    char *token = strtok(birthdatestr, "/");
    char birthcity[20];
    date Fbirthdate;
    if(token != NULL){
        strcpy(birthcity, token);
        token = strtok(NULL, "/");
        if(token != NULL){
            Fbirthdate.date = atoi(token);
            token = strtok(NULL, "/");
            if(token != NULL){
                Fbirthdate.month = atoi(token);
                token = strtok(NULL, "/");
                if(token != NULL){
                    Fbirthdate.year = atoi(token);
                }
            }
        }
    }

    char monthList[12][12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

    char birthdatestr2[20];
    sprintf(birthdatestr2, "%d %s %d", Fbirthdate.date, monthList[Fbirthdate.month-1], Fbirthdate.year);

    //edit the data
    int success = modifyPatient(&pasien, PIDstr, namestr, addressstr, citystr, birthcity, birthdatestr2, atoi(agestr), bpjsstr);
    if(success == 0){
        gtk_label_set_text(GTK_LABEL(label), "Data tidak ditemukan");
    }
    else{
        gtk_label_set_text(GTK_LABEL(label), "Data berhasil diubah");
    }
}

void editPatientClicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *PIDEntry;
    GtkWidget *nameEntry;
    GtkWidget *addressEntry;
    GtkWidget *cityEntry;
    GtkWidget *birthdateEntry;
    GtkWidget *ageEntry;
    GtkWidget *bpjsEntry;
    GtkWidget *label;
    GtkWidget *saveButton;/*button untuk menyimpan data pasien*/

    DataPasien *pasien = (DataPasien*)data;
    struct editPatientData *editData = malloc(sizeof(struct editPatientData));
    editData->pasien = pasien;

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Edit Data Pasien");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create label
    label = gtk_label_new("");
    editData->label = label;

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create entry PID
    PIDEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(PIDEntry), "Masukkan ID pasien yang ingin diedit");
    editData->PIDEntry = PIDEntry;

    //create entry name
    nameEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(nameEntry), "Nama Pasien");
    editData->nameEntry = nameEntry;

    //create entry address
    addressEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(addressEntry), "Alamat Pasien");
    editData->addressEntry = addressEntry;

    //create entry city
    cityEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(cityEntry), "Kota");
    editData->cityEntry = cityEntry;

    //create entry birthdate
    birthdateEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(birthdateEntry), "Tempat dan Tanggal Lahir (dalam format kota/tanggal contoh: Jakarta/01 Januari 2000)");
    editData->birthdateEntry = birthdateEntry;

    //create entry age
    ageEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(ageEntry), "Umur Pasien");
    editData->ageEntry = ageEntry;

    //create entry bpjs
    bpjsEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(bpjsEntry), "Nomor BPJS Pasien");
    editData->bpjsEntry = bpjsEntry;

    //create save button
    saveButton = gtk_button_new_with_label("Simpan");
    g_signal_connect(saveButton, "clicked", G_CALLBACK(editPatientSaveClicked), editData);

    //pack all widget
    gtk_box_pack_start(GTK_BOX(vbox), PIDEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), nameEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), addressEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), cityEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), birthdateEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), ageEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), bpjsEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), saveButton, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}

struct deletePatientData{
    GtkWidget *labelConfirm;
    DataPasien *pasien;
    GtkWidget *entryChoice;
};

void delPatientActive(GtkWidget *widget, gpointer data){
    DataPasien *pasien = ((struct deletePatientData*)data)->pasien;
    const gchar *input = gtk_entry_get_text(GTK_ENTRY(((struct deletePatientData*)data)->entryChoice));
    char searchID[20];
    strcpy(searchID, input); 
    int deleted = deletePatient(&pasien, searchID);
    if(deleted == 0){
        gtk_label_set_text(GTK_LABEL(((struct deletePatientData*)data)->labelConfirm), "Data tidak ditemukan");
    }
    else{
        char confirm[50];
        sprintf(confirm, "Data dengan ID %s berhasil dihapus", searchID);
        gtk_label_set_text(GTK_LABEL(((struct deletePatientData*)data)->labelConfirm), confirm);
    }
}

void delPatientClicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *Label;
    GtkWidget *LabelConfirm;
    GtkWidget *entryChoice;
    GtkWidget *buttonExit;/*button untuk membatalkan penghapusan data pasien*/

    DataPasien *pasien = (DataPasien*)data;
    struct deletePatientData *delData = malloc(sizeof(struct deletePatientData));
    delData->pasien = pasien;
    //create Label
    Label = gtk_label_new("Masukkan ID pasien yang ingin dihapus");

    LabelConfirm = gtk_label_new("");
    delData->labelConfirm = LabelConfirm;
    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hapus Data Pasien");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create entry choice
    entryChoice = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryChoice), "Masukkan ID pasien yang ingin dihapus");
    delData->entryChoice = entryChoice;
    g_signal_connect(entryChoice, "activate", G_CALLBACK(delPatientActive), delData);

    //create exit button
    buttonExit = gtk_button_new_with_label("Batal");
    g_signal_connect(buttonExit, "clicked", G_CALLBACK(closeWindow), window);

    //pack all widget
    gtk_box_pack_start(GTK_BOX(vbox), Label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entryChoice, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), LabelConfirm, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), buttonExit, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}