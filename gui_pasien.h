#include <gtk/gtk.h>
#include <string.h>

#ifndef GUI_PASIEN_H
typedef struct{
    GtkWidget *entry;
    char *string;
}entryString;

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

void getTextInput(GtkWidget *entry){
    entryString *es = (entryString *)entry;
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(es->entry));
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
    entryString *entry_name = malloc(sizeof(entryString));
    entryString *entry_address = malloc(sizeof(entryString));
    entryString *entry_city = malloc(sizeof(entryString));
    entryString *entry_birthdate = malloc(sizeof(entryString));
    entryString *entry_age = malloc(sizeof(entryString));
    entryString *entry_bpjs = malloc(sizeof(entryString));
    entryString *entry_PID = malloc(sizeof(entryString));
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
    entry_name->entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_name->entry), "Nama Pasien");

    //create label address
    entry_address->entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_address->entry), "Alamat Pasien");

    //create label city
    entry_city->entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_city->entry), "Kota");

    //create label birthdate
    entry_birthdate->entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_birthdate->entry), "Tempat dan Tanggal Lahir (dalam format kota/dd/mm/yyyy)");

    //create label age
    entry_age->entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_age->entry), "Umur Pasien");

    //create label BPJS
    entry_bpjs->entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_bpjs->entry), "Nomor BPJS Pasien");

    //create label PID
    entry_PID->entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_PID->entry), "Patient ID");

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
    entryString *entryChoice;
    entryString *entry_name;
    entryString *entry_address;
    entryString *entry_city;
    entryString *entry_birthdate;
    entryString *entry_age;
    entryString *entry_bpjs;
    entryString *entry_PID;
    GtkWidget *buttonSearch;
    GtkWidget *button_save;/*button untuk menyimpan data pasien*/
    GtkWidget *button_cancel;/*button untuk membatalkan input data pasien*/

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Edit Data Pasien");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create entry choice
    entryChoice->entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryChoice->entry), "Masukkan ID pasien yang ingin diedit");
    g_signal_connect(entryChoice->entry, "activate", G_CALLBACK(getTextInput), entryChoice);
    
    //create search button
    buttonSearch = gtk_button_new_with_label("Search");
    //insert function to search patient data


}

void editPatientFound(GtkWidget *widget){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label_general;
    entryString *entry_name = malloc(sizeof(entryString));
    entryString *entry_address = malloc(sizeof(entryString));
    entryString *entry_city = malloc(sizeof(entryString));
    entryString *entry_birthdate = malloc(sizeof(entryString));
    entryString *entry_age = malloc(sizeof(entryString));
    entryString *entry_bpjs = malloc(sizeof(entryString));
    entryString *entry_PID = malloc(sizeof(entryString));
    GtkWidget *button_save;/*button untuk menyimpan data pasien*/
    GtkWidget *button_cancel;/*button untuk membatalkan input data pasien*/

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Edit Data Pasien");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create label general
    label_general = gtk_label_new("Input data pasien yang telat diedit lalu klik simpan");

    //create entry name
    entry_name->entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_name->entry), ");
}