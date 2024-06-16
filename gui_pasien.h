#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>

#ifndef GUI_PASIEN_H

enum patientColumns{
    COL_NAME,
    COL_ADDRESS,
    COL_CITY,
    COL_BIRTHDATE,
    COL_AGE,
    COL_BPJS,
    COL_PID,
    PATIENT_N_COLS
};

void getTextInput(GtkWidget *entry, gpointer data){
    entryString *es = (entryString *)data;
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));
    strcpy(es->string, text);
}

void closeWindow(GtkWidget *widget, gpointer window){
    gtk_widget_destroy(GTK_WIDGET(window));
}

#endif


void addPatientClicked(GtkWidget *widget){
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

    //create label address
    entry_address = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_address)"Alamat Pasien");

    //create label city
    entry_city = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_city), "Kota");

    //create label birthdate
    entry_birthdate= gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_birthdate), "Tempat dan Tanggal Lahir (dalam format kota/dd/mm/yyyy)");

    //create label age
    entry_age= gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_age), "Umur Pasien");

    //create label BPJS
    entry_bpjs= gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_bpjs), "Nomor BPJS Pasien");

    //create label PID
    entry_PID= gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_PID), "Patient ID");

    //save button
    button_save = gtk_button_new_with_label("Simpan");
    g_signal_connect(button_save, "clicked", G_CALLBACK(closeWindow)/*insert fungsi add pasien*/, window);

    //cancel button
    button_cancel = gtk_button_new_with_label("Batal");
    g_signal_connect(button_cancel, "clicked", G_CALLBACK(closeWindow), window);

    //pack all widget
    gtk_box_pack_start(GTK_BOX(vbox), label_general, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_name->entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_address->entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_city->entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_birthdate->entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_age->entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_bpjs->entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_PID->entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_save, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_cancel, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}

void editNamaClicked(GtkWidget *widget){
    GtkWidget *window;
    GtkWidget *vbox;
    
}

void searchPatientClicked(GtkWidget *widget){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *entryChoice;
    GtkWidget *button_search;/*button untuk mencari data pasien*/
    GtkListStore *searchList;
    GtkTreeViewColumn *column;
    GtkWidget *view;
    char PID[11];

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Cari Data Pasien");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
    
    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create entry choice
    entryChoice = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryChoice), "Masukkan ID pasien yang ingin dicari");
    g_signal_connect(entryChoice, "activate", G_CALLBACK(getTextInput), entryChoice);

    //create search button
    button_search = gtk_button_new_with_label("Search");
    g_signal_connect(button_search, "clicked", G_CALLBACK(closeWindow)/*insert fungsi search pasien*/, window);
    //insert fungsi buat search di sini


    //create list store
    searchList = gtk_list_store_new(PATIENT_N_COLS, G_TYPE_STRING/*NAMA*/, G_TYPE_STRING/*ALAMAT*/, G_TYPE_STRING/*KOTA*/, G_TYPE_STRING/*TEMPAT TANGGAL LAHIR*/, G_TYPE_INT/*UMUR*/, G_TYPE_STRING/*BPJS*/, G_TYPE_STRING/*PID*/);
    view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(searchList));

    column = gtk_tree_view_column_new_with_attributes("Nama", gtk_cell_renderer_text_new(), "text", COL_NAME, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Alamat", gtk_cell_renderer_text_new(), "text", COL_ADDRESS, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Kota", gtk_cell_renderer_text_new(), "text", COL_CITY, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Tempat dan Tanggal Lahir", gtk_cell_renderer_text_new(), "text", COL_BIRTHDATE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Umur", gtk_cell_renderer_text_new(), "text", COL_AGE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("BPJS", gtk_cell_renderer_text_new(), "text", COL_BPJS, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Patient ID", gtk_cell_renderer_text_new(), "text", COL_PID, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    //pack all widget
    gtk_box_pack_start(GTK_BOX(vbox), entryChoice, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_search, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}

void editPatientClicked(GtkWidget *widget){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *nameButton;
    GtkWidget *addressButton;
    GtkWidget *cityButton;
    GtkWidget *birthdateButton;
    GtkWidget *ageButton;
    GtkWidget *bpjsButton;

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Edit Data Pasien");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create button
    nameButton = gtk_button_new_with_label("Edit Nama");
    addressButton = gtk_button_new_with_label("Edit Alamat");
    cityButton = gtk_button_new_with_label("Edit Kota");
    birthdateButton = gtk_button_new_with_label("Edit Tempat dan Tanggal Lahir");
    ageButton = gtk_button_new_with_label("Edit Umur");
    bpjsButton = gtk_button_new_with_label("Edit BPJS");

    //pack all widget
    gtk_box_pack_start(GTK_BOX(vbox), nameButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), addressButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), cityButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), birthdateButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), ageButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), bpjsButton, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}

void delPatientClicked(GtkWidget *widget){
    GtkWidget *window;
    GtkWidget *vbox;
    entryString *entryChoice = malloc(sizeof(entryString));
    GtkWidget *buttonExit;/*button untuk membatalkan penghapusan data pasien*/

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hapus Data Pasien");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create entry choice
    entryChoice->entry = gtk_entry_new();
    entryChoice->string = malloc(11*sizeof(char));
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryChoice->entry), "Masukkan ID pasien yang ingin dihapus");
    g_signal_connect(entryChoice->entry, "activate", G_CALLBACK(getTextInput), entryChoice);

    //create exit button
    buttonExit = gtk_button_new_with_label("Batal");
    g_signal_connect(buttonExit, "clicked", G_CALLBACK(closeWindow), window);

    //pack all widget
    gtk_box_pack_start(GTK_BOX(vbox), entryChoice->entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), buttonExit, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}