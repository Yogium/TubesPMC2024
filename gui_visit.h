#include <gtk/gtk.h>
#include "struct.h"
#include "LinkedList.h"
#include "gui_commonfunc.h"
#include "new_visit_manipulate.c"

struct addVisitData{
    GtkWidget *label;
    GtkWidget *entryPatientID;
    GtkWidget *entryDate;
    GtkWidget *entryDiagnosis;
    GtkWidget *entryTindakan;
    GtkWidget *entryControl;
    DataKunjungan *kunjungan;
};

void visitAddSave(GtkWidget *widget, gpointer data){
    DataKunjungan *kunjunganHead = ((struct addVisitData*)data)->kunjungan;
    const char *patientID = gtk_entry_get_text(GTK_ENTRY(((struct addVisitData*)data)->entryPatientID));
    const char *date = gtk_entry_get_text(GTK_ENTRY(((struct addVisitData*)data)->entryDate));
    const char *diagnosis = gtk_entry_get_text(GTK_ENTRY(((struct addVisitData*)data)->entryDiagnosis));
    const char *tindakanEntry = gtk_entry_get_text(GTK_ENTRY(((struct addVisitData*)data)->entryTindakan));
    const char *control = gtk_entry_get_text(GTK_ENTRY(((struct addVisitData*)data)->entryControl));

    char patientIDcpy[11];
    char datecpy[11];
    char diagnosiscpy[20];
    char tindakancpy[20];
    char controlcpy[11];
    strcpy(patientIDcpy, patientID);
    strcpy(datecpy, date);
    strcpy(diagnosiscpy, diagnosis);
    strcpy(tindakancpy, tindakanEntry);
    strcpy(controlcpy, control);

    int diagnosisIndex = getDiagnosis(penyakit, diagnosiscpy);
    int tindakanIndex = getTindakan(tindakan, tindakancpy);

    addVisit(&kunjunganHead, datecpy, patientIDcpy, diagnosisIndex, tindakanIndex, controlcpy);
    gtk_label_set_text(GTK_LABEL(((struct addVisitData*)data)->label), "Data Kunjungan Berhasil Ditambahkan");
}

void addVisitClicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *pIDEntry;
    GtkWidget *dateEntry;
    GtkWidget *diagnosisEntry;
    GtkWidget *tindakanEntry;
    GtkWidget *controlEntry;
    GtkWidget *saveButton;
    GtkWidget *exitButton;

    DataKunjungan *kunjunganHead = (DataKunjungan *)data;
    printf("Patient ID: %s\n", kunjunganHead->patientID);

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Tambah Kunjungan");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    struct addVisitData *addVisitData = malloc(sizeof(struct addVisitData));
    addVisitData->kunjungan = kunjunganHead;

    //create patient ID entry
    pIDEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(pIDEntry), "Patient ID");
    addVisitData->entryPatientID = pIDEntry;     

    //create date entry
    dateEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(dateEntry), "Tanggal Kunjungan (dd/mm/yyyy)");
    addVisitData->entryDate = dateEntry;

    //create diagnosis entry
    diagnosisEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(diagnosisEntry), "Diagnosis");
    addVisitData->entryDiagnosis = diagnosisEntry;

    //create tindakan entry
    tindakanEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(tindakanEntry), "Tindakan");
    addVisitData->entryTindakan = tindakanEntry;

    //create control entry
    controlEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(controlEntry), "Tanggal Kontrol (dd/mm/yyyy)");
    addVisitData->entryControl = controlEntry;

    //create save button
    saveButton = gtk_button_new_with_label("Simpan");
    label = gtk_label_new("");
    addVisitData->label = label;
    g_signal_connect(saveButton, "clicked", G_CALLBACK(visitAddSave), addVisitData);

    //create exit button
    exitButton = gtk_button_new_with_label("Keluar");
    g_signal_connect(exitButton, "clicked", G_CALLBACK(closeWindow), window);

    //add to vbox
    gtk_box_pack_start(GTK_BOX(vbox), pIDEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), dateEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), diagnosisEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), tindakanEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), controlEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), saveButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), exitButton, TRUE, TRUE, 0);

    //add vbox to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}

struct deleteVisitData{
    GtkWidget *label;
    GtkWidget *entryPatientID;
    GtkWidget *entryDate;
    DataKunjungan *kunjungan;
};

void visitDeleteSave(GtkWidget *widget, gpointer data){
    DataKunjungan *kunjunganHead = ((struct deleteVisitData*)data)->kunjungan;
    const char *patientID = gtk_entry_get_text(GTK_ENTRY(((struct deleteVisitData*)data)->entryPatientID));
    const char *tanggal = gtk_entry_get_text(GTK_ENTRY(((struct deleteVisitData*)data)->entryDate));


    char patientIDcpy[11];
    char datecpy[11];
    strcpy(patientIDcpy, patientID);
    strcpy(datecpy, tanggal);

    date tanggalKunjungan;
    char *token = strtok(datecpy, "/");
    tanggalKunjungan.date = atoi(token);
    token = strtok(NULL, "/");
    tanggalKunjungan.month = atoi(token);
    token = strtok(NULL, "/");
    tanggalKunjungan.year = atoi(token);

    deleteVisit(&kunjunganHead, patientIDcpy, tanggalKunjungan);
    gtk_label_set_text(GTK_LABEL(((struct deleteVisitData*)data)->label), "Data Kunjungan Berhasil Dihapus");
}

void visitDeleteClicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *pIDEntry;
    GtkWidget *dateEntry;
    GtkWidget *deleteButton;
    GtkWidget *exitButton;

    struct deleteVisitData *deleteVisitData = malloc(sizeof(struct deleteVisitData));

    DataKunjungan *kunjunganHead = (DataKunjungan *)data;
    deleteVisitData->kunjungan = kunjunganHead;

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hapus Kunjungan");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create patient ID entry
    pIDEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(pIDEntry), "Patient ID");
    deleteVisitData->entryPatientID = pIDEntry;

    //create date entry
    dateEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(dateEntry), "Tanggal Kunjungan (dd/mm/yyyy)");
    deleteVisitData->entryDate = dateEntry;

    //create delete button
    deleteButton = gtk_button_new_with_label("Hapus");
    label = gtk_label_new("");
    deleteVisitData->label = label;

    g_signal_connect(deleteButton, "clicked", G_CALLBACK(visitDeleteSave), deleteVisitData);

    //create exit button
    exitButton = gtk_button_new_with_label("Keluar");
    g_signal_connect(exitButton, "clicked", G_CALLBACK(closeWindow), window);

    //add to vbox
    gtk_box_pack_start(GTK_BOX(vbox), pIDEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), dateEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), deleteButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), exitButton, TRUE, TRUE, 0);

    //add vbox to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);

}