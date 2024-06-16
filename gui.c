#include <gtk/gtk.h>
#include <string.h>
#include "struct.h"
#include "LinkedList.h"
#include "gui_pasien.h"
#include "controlPatient.c"
#include "gui_cashflow.h"
#include "gui_commonfunc.h"
#include "gui_sick.h"

enum controlColumns {
    COL_PATIENT_ID,
    COL_PATIENT_NAME,
    CONTROL_N_COLUMNS
};

enum sickColumns {
    COL_SICK_NAME,
    COL_SICK_COUNT,
    SICK_N_COLUMNS
};

enum diagColumns {
    COL_DIAG_NAME,
    COL_DIAG_TINDAKAN,
    COL_DIAG_DATE,
    DIAG_N_COLUMNS
};

struct controlStruct{
    GtkWidget *entryDate;
    DataKunjungan *kunjungan;
    DataPasien *pasien;
    GtkListStore *controlList;
};

struct generalLL{
    DataKunjungan *kunjungan;
    DataPasien *pasien;
};



void patient_clicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *add_button;
    GtkWidget *edit_button;
    GtkWidget *delete_button;
    GtkWidget *search_button;
    GtkWidget *back_button;

    DataPasien *pasien = ((struct generalLL*)data)->pasien;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "data pasien");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //add button
    add_button = gtk_button_new_with_label("tambah data pasien");
    g_signal_connect(add_button, "clicked", G_CALLBACK(addPatientClicked), pasien);

    //edit button
    edit_button = gtk_button_new_with_label("edit data pasien");
    g_signal_connect(edit_button, "clicked", G_CALLBACK(editPatientClicked), pasien);

    //delete button 
    delete_button = gtk_button_new_with_label("hapus data pasien");
    g_signal_connect(delete_button, "clicked", G_CALLBACK(delPatientClicked), pasien);

    //search button
    search_button = gtk_button_new_with_label("cari data pasien");
    g_signal_connect(search_button, "clicked", G_CALLBACK(searchPatientClicked), pasien);

    //back button
    back_button = gtk_button_new_with_label("kembali");
    g_signal_connect(back_button, "clicked", G_CALLBACK(closeWindow), window);

    //add button to vbox
    gtk_box_pack_start(GTK_BOX(vbox), add_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), edit_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), delete_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), search_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), back_button, TRUE, TRUE, 0);

    //add vbox to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}

void visitClicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *add_button;
    GtkWidget *edit_button;
    GtkWidget *delete_button;
    GtkWidget *search_button;
    GtkWidget *back_button;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "data kunjungan");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //add button
    add_button = gtk_button_new_with_label("tambah data kunjungan");
    //insert function for add button

    //edit button
    edit_button = gtk_button_new_with_label("edit data kunjungan");
    //insert function for edit button

    //delete button
    delete_button = gtk_button_new_with_label("hapus data kunjungan");
    //insert function for delete button

    //search button
    search_button = gtk_button_new_with_label("cari data kunjungan");
    //insert function for search button

    //back button
    back_button = gtk_button_new_with_label("kembali");
    g_signal_connect(back_button, "clicked", G_CALLBACK(closeWindow), window);

    //add button to vbox
    gtk_box_pack_start(GTK_BOX(vbox), add_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), edit_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), delete_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), search_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), back_button, TRUE, TRUE, 0);

    //add vbox to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);   
}

void controlSearchClicked(GtkWidget *widget, gpointer data){
    DataPasien *pasien = ((struct controlStruct*)data)->pasien;
    DataKunjungan *kunjungan = ((struct controlStruct*)data)->kunjungan;
    GtkWidget *entryDate = ((struct controlStruct*)data)->entryDate;
    const char *date = gtk_entry_get_text(GTK_ENTRY(entryDate));
    char *dateCopy = malloc(strlen(date) + 1);
    dateCopy = strcpy(dateCopy, date);
    ctrlist *controlLLHead = NULL;
    controlLLHead = findPatientsByControlDate(pasien, kunjungan, dateCopy);
    ctrlist *temp = controlLLHead;
    GtkListStore *controlList = (((struct controlStruct*)data)->controlList);
    GtkTreeIter iter;
    if(controlLLHead == NULL){
        return;
    }
    while(temp != NULL){
        gtk_list_store_insert_with_values(controlList, &iter, -1, COL_PATIENT_ID, temp->patientID, COL_PATIENT_NAME, temp->nama, -1);
        temp = temp->next;
    }
}


void controlClicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *exitButton;
    GtkListStore *controlList;
    GtkTreeViewColumn *column;
    GtkWidget *searchButton;
    GtkWidget *view;
    GtkWidget *label;

    //declare the head for LL
    struct controlStruct *controlData = malloc(sizeof(struct controlStruct));
    controlData->kunjungan = ((struct generalLL*)data)->kunjungan;
    controlData->pasien = ((struct generalLL*)data)->pasien; 

    //create list
    controlList = gtk_list_store_new(CONTROL_N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING);
    view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(controlList));

    column = gtk_tree_view_column_new_with_attributes("Patient ID", gtk_cell_renderer_text_new(), "text", COL_PATIENT_ID, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Patient Name", gtk_cell_renderer_text_new(), "text", COL_PATIENT_NAME, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    controlData->controlList = controlList;

    //create label
    label = gtk_label_new("Masukkan Tanggal dalam Format dd/mm/yyyy");

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "data kontrol");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create entry
    controlData->entryDate = gtk_entry_new();
    //g_signal_connect(controlData->entryDate, "activate", G_CALLBACK(controlSearchClicked), controlData);

    //create search button
    searchButton = gtk_button_new_with_label("Search");
    g_signal_connect(searchButton, "clicked", G_CALLBACK(controlSearchClicked), controlData);

    //create exit button
    exitButton = gtk_button_new_with_label("kembali");
    g_signal_connect(exitButton, "clicked", G_CALLBACK(closeWindow), window);

    //add entry to vbox
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), controlData->entryDate, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), searchButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), exitButton, TRUE, TRUE, 0);

    //add vbox to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
    
}

void diagClicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *entry_PID;/*masukkan PID*/
    GtkWidget *searchButton;/*tombol search*/
    GtkWidget *patientNameLabel;/*nama pasien*/
    GtkListStore *diagList;
    GtkTreeViewColumn *column;
    GtkWidget *view;
    GtkWidget *exitButton;

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "riwayat sakit pasien");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create search button
    searchButton = gtk_button_new_with_label("Search");
    //insert function for search button

    //create label
    patientNameLabel = gtk_label_new("Nama Pasien: ");

    //create entry
    entry_PID = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_PID), "Masukkan Patient ID");

    //create list
    diagList = gtk_list_store_new(DIAG_N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(diagList));

    column = gtk_tree_view_column_new_with_attributes("Diagnosis", gtk_cell_renderer_text_new(), "text", COL_DIAG_NAME, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Tindakan", gtk_cell_renderer_text_new(), "text", COL_DIAG_TINDAKAN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Tanggal Control", gtk_cell_renderer_text_new(), "text", COL_DIAG_DATE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    //create exit button
    exitButton = gtk_button_new_with_label("kembali");
    g_signal_connect(exitButton, "clicked", G_CALLBACK(closeWindow), window);

    //add entry to vbox
    gtk_box_pack_start(GTK_BOX(vbox), entry_PID, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), searchButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), patientNameLabel, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), exitButton, TRUE, TRUE, 0);

    //add vbox to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}

// void cashflowClicked(GtkWidget *widget, gpointer data){
//     GtkWidget *window;
//     GtkWidget *vbox;
//     GtkWidget *exitButton;
//     GtkWidget *yearButton;
//     GtkWidget *monthButton;
//     GtkWidget *averageLabel;
//     GtkWidget *averageValue; 
//     //create window
//     window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//     gtk_window_set_title(GTK_WINDOW(window), "data kas");
//     gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

//     //create vbox
//     vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

//     //create year button
//     yearButton = gtk_button_new_with_label("Lihat Data Kas per Tahun");
//     //insert function for year button

//     //create month button
//     monthButton = gtk_button_new_with_label("Lihat Data Kas per Bulan");
//     //insert function for month button

//     //create average label
//     float averagePerYear = 
//     averageLabel = gtk_label_new("Rata-rata Kas Setiap Tahun");
//     float average = 0;//insert function to get average
//     char averageString[100];
//     sprintf(averageString, "Rp. %.2f", average);
//     averageValue = gtk_label_new(averageString);


//     //create exit button
//     exitButton = gtk_button_new_with_label("kembali");
//     g_signal_connect(exitButton, "clicked", G_CALLBACK(closeWindow), window);

//     //add button to vbox
//     gtk_box_pack_start(GTK_BOX(vbox), yearButton, TRUE, TRUE, 0);
//     gtk_box_pack_start(GTK_BOX(vbox), monthButton, TRUE, TRUE, 0);
//     gtk_box_pack_start(GTK_BOX(vbox), averageLabel, TRUE, TRUE, 0);
//     gtk_box_pack_start(GTK_BOX(vbox), averageValue, TRUE, TRUE, 0);
//     gtk_box_pack_start(GTK_BOX(vbox), exitButton, TRUE, TRUE, 0);

//     //add vbox to window
//     gtk_container_add(GTK_CONTAINER(window), vbox);
//     gtk_widget_show_all(window);
// }

void sickClicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *exitButton;
    GtkWidget *yearButton;
    GtkWidget *monthButton;

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "data penyakit");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create year button
    yearButton = gtk_button_new_with_label("Lihat Data Penyakit per Tahun");

    //create month button
    monthButton = gtk_button_new_with_label("Lihat Data Penyakit per Bulan");
    g_signal_connect(monthButton, "clicked", G_CALLBACK(sickMonthPressed), data);


    //create exit button

    exitButton = gtk_button_new_with_label("Kembali");
    g_signal_connect(exitButton, "clicked", G_CALLBACK(closeWindow), window);

    //add button to vbox
    gtk_box_pack_start(GTK_BOX(vbox), yearButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), monthButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), exitButton, TRUE, TRUE, 0);

   //add view to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *control_button;
    GtkWidget *visit_button;
    GtkWidget *patient_button;
    GtkWidget *cash_button;
    GtkWidget *sick_button;
    GtkWidget *diag_button; /*tombol untuk riwayat sakit pasien*/
    
    //initialize linkedlist
    DataPasien* pasienHead = NULL;
    DataKunjungan* kunjunganHead = NULL;
    parseDataPasienFromFile("Data_Pasien.csv", &pasienHead);
    parseDataKunjunganFromFile("Riwayat_Datang.csv", &kunjunganHead);
    struct generalLL LL = {kunjunganHead, pasienHead};

    // initialize gtk
    gtk_init(&argc, &argv);

    //main window creation
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "rumah sakit x");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //patient button
    patient_button = gtk_button_new_with_label("Data Pasien");
    g_signal_connect(patient_button, "clicked", G_CALLBACK(patient_clicked), &LL);


    //visit button  
    visit_button = gtk_button_new_with_label("Data Kunjungan");
    g_signal_connect(visit_button, "clicked", G_CALLBACK(visitClicked), &LL);

    //control button
    control_button = gtk_button_new_with_label("Data Kontrol");
    g_signal_connect(control_button, "clicked", G_CALLBACK(controlClicked), &LL);

    //diagnosis button
    diag_button = gtk_button_new_with_label("Riwayat Sakit Pasien");
    g_signal_connect(diag_button, "clicked", G_CALLBACK(diagClicked), NULL);

    //cash button
    cash_button = gtk_button_new_with_label("Data Kas/Cashflow");
    g_signal_connect(cash_button, "clicked", G_CALLBACK(cashflowClicked), kunjunganHead);

    //sick button
    sick_button = gtk_button_new_with_label("Data Penyakit");
    g_signal_connect(sick_button, "clicked", G_CALLBACK(sickClicked), kunjunganHead);

    //add button to vbox
    gtk_box_pack_start(GTK_BOX(vbox), patient_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), visit_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), control_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), diag_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), cash_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), sick_button, TRUE, TRUE, 0);

    //add vbox to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
}