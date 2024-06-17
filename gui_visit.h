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

    int success = deleteVisit(&kunjunganHead, patientIDcpy, tanggalKunjungan);
    if(success == 0){
        gtk_label_set_text(GTK_LABEL(((struct deleteVisitData*)data)->label), "Data Kunjungan Tidak Ditemukan");
        return;
    }
    else{
    gtk_label_set_text(GTK_LABEL(((struct deleteVisitData*)data)->label), "Data Kunjungan Berhasil Dihapus");
    }
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

struct editVisitData{
    GtkWidget *label;
    GtkWidget *entryPatientID;
    GtkWidget *entryDate;
    GtkWidget *entryDiagnosis;
    GtkWidget *entryTindakan;
    GtkWidget *entryControl;
    DataKunjungan *kunjungan;
};

void visitEditSave(GtkWidget *widget, gpointer data){
    DataKunjungan *kunjunganHead = ((struct editVisitData*)data)->kunjungan;
    const char *patientID = gtk_entry_get_text(GTK_ENTRY(((struct editVisitData*)data)->entryPatientID));
    const char *dateEntry = gtk_entry_get_text(GTK_ENTRY(((struct editVisitData*)data)->entryDate));
    const char *diagnosis = gtk_entry_get_text(GTK_ENTRY(((struct editVisitData*)data)->entryDiagnosis));
    const char *tindakanEntry = gtk_entry_get_text(GTK_ENTRY(((struct editVisitData*)data)->entryTindakan));
    const char *control = gtk_entry_get_text(GTK_ENTRY(((struct editVisitData*)data)->entryControl));

    char patientIDcpy[11];
    char datecpy[11];
    char diagnosiscpy[20];
    char tindakancpy[20];
    char controlcpy[11];
    strcpy(patientIDcpy, patientID);
    strcpy(datecpy, dateEntry);
    strcpy(diagnosiscpy, diagnosis);
    strcpy(tindakancpy, tindakanEntry);
    strcpy(controlcpy, control);

    int diagnosisIndex = getDiagnosis(penyakit, diagnosiscpy);
    int tindakanIndex = getTindakan(tindakan, tindakancpy);

    date tanggalKunjungan;
    char *token = strtok(datecpy, "/");
    tanggalKunjungan.date = atoi(token);
    token = strtok(NULL, "/");
    tanggalKunjungan.month = atoi(token);
    token = strtok(NULL, "/");
    tanggalKunjungan.year = atoi(token);

    int success = updateVisit(&kunjunganHead, patientIDcpy, tanggalKunjungan, controlcpy, diagnosisIndex, tindakanIndex);
    if(success == 0){
        gtk_label_set_text(GTK_LABEL(((struct editVisitData*)data)->label), "Data Kunjungan Tidak Ditemukan");
        return;
    }
    else{
    gtk_label_set_text(GTK_LABEL(((struct editVisitData*)data)->label), "Data Kunjungan Berhasil Diubah");
    }
}

void visitEditClicked(GtkWidget *widget, gpointer data){
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

    struct editVisitData *editVisitData = malloc(sizeof(struct editVisitData));

    DataKunjungan *kunjunganHead = (DataKunjungan *)data;
    editVisitData->kunjungan = kunjunganHead;

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Edit Kunjungan");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create patient ID entry
    pIDEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(pIDEntry), "Patient ID");
    editVisitData->entryPatientID = pIDEntry;

    //create date entry
    dateEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(dateEntry), "Tanggal Kunjungan (dd/mm/yyyy)");
    editVisitData->entryDate = dateEntry;

    //create diagnosis entry
    diagnosisEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(diagnosisEntry), "Diagnosis");
    editVisitData->entryDiagnosis = diagnosisEntry;

    //create tindakan entry
    tindakanEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(tindakanEntry), "Tindakan");
    editVisitData->entryTindakan = tindakanEntry;

    //create control entry
    controlEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(controlEntry), "Tanggal Kontrol (dd/mm/yyyy)");
    editVisitData->entryControl = controlEntry;

    //create save button
    saveButton = gtk_button_new_with_label("Simpan");
    label = gtk_label_new("");
    editVisitData->label = label;
    g_signal_connect(saveButton, "clicked", G_CALLBACK(visitEditSave), editVisitData);

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

enum searchColumns{
    COLUMN_PATIENTID,
    COLUMN_DATE,
    COLUMN_DIAGNOSIS,
    COLUMN_TINDAKAN,
    COLUMN_CONTROL,
    SVISIT_NUM_COLUMNS
};

struct searchVisitData{
    GtkWidget *entryPID;
    GtkListStore *searchList;
    DataKunjungan *kunjungan;
};

char *dateToString(date tanggal){
    char *result = malloc(20);
    sprintf(result, "%d/%d/%d", tanggal.date, tanggal.month, tanggal.year);
    return result;
}

void searchVisitSearched(GtkWidget *widget, gpointer data){
    DataKunjungan *kunjunganHead = ((struct searchVisitData*)data)->kunjungan;
    const char *patientID = gtk_entry_get_text(GTK_ENTRY(((struct searchVisitData*)data)->entryPID));
    GtkListStore *gtk_store = ((struct searchVisitData*)data)->searchList;


    DataKunjungan *result = NULL;

    char patientIDcpy[11];
    strcpy(patientIDcpy, patientID);

    result = searchVisit(kunjunganHead, patientIDcpy);

    GtkTreeIter iter;
    gtk_list_store_clear(gtk_store);
    while(result != NULL){
        gtk_list_store_append(gtk_store, &iter);
        char *tanggalStr = dateToString(result->tanggal);
        char *controlStr = dateToString(result->control);
        gtk_list_store_set(gtk_store, &iter, COLUMN_PATIENTID, patientIDcpy, COLUMN_DATE, tanggalStr, COLUMN_DIAGNOSIS, penyakit[result->diagnosis], COLUMN_TINDAKAN, tindakan[result->tindakan].nama, COLUMN_CONTROL, controlStr, -1);
        result = result->next;
    }
}


void searchVisitClicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkListStore *searchList;
    GtkTreeViewColumn *column;
    GtkWidget *view;
    GtkWidget *entryPID;
    GtkWidget *searchButton;
    GtkWidget *exitButton;

    struct searchVisitData *searchVisitData = malloc(sizeof(struct searchVisitData));

    DataKunjungan *kunjunganHead = (DataKunjungan *)data;
    searchVisitData->kunjungan = kunjunganHead;

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Cari Kunjungan");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create patient ID entry
    entryPID = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryPID), "Patient ID");
    searchVisitData->entryPID = entryPID;


    //create search button
    searchButton = gtk_button_new_with_label("Cari");

    //create exit button
    exitButton = gtk_button_new_with_label("Keluar");

    //create list store
    searchList = gtk_list_store_new(SVISIT_NUM_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(searchList));

    //create columns
    column = gtk_tree_view_column_new_with_attributes("Patient ID", gtk_cell_renderer_text_new(), "text", COLUMN_PATIENTID, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Tanggal Kunjungan", gtk_cell_renderer_text_new(), "text", COLUMN_DATE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Diagnosis", gtk_cell_renderer_text_new(), "text", COLUMN_DIAGNOSIS, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Tindakan", gtk_cell_renderer_text_new(), "text", COLUMN_TINDAKAN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Tanggal Kontrol", gtk_cell_renderer_text_new(), "text", COLUMN_CONTROL, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
    searchVisitData->searchList = searchList;

    g_signal_connect(searchButton, "clicked", G_CALLBACK(searchVisitSearched), searchVisitData);

    //add to vbox
    gtk_box_pack_start(GTK_BOX(vbox), entryPID, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), searchButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), exitButton, TRUE, TRUE, 0);

    //add vbox to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}