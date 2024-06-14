#include <gtk/gtk.h>

void closeWindow(GtkWidget *widget, gpointer window){
    gtk_widget_destroy(GTK_WIDGET(window));
}

void patient_clicked(GtkWidget *widget){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *add_button;
    GtkWidget *edit_button;
    GtkWidget *delete_button;
    GtkWidget *search_button;
    GtkWidget *back_button;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Data Pasien");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //add button
    add_button = gtk_button_new_with_label("Tambah Data Pasien");
    //insert function for add button

    //edit button
    edit_button = gtk_button_new_with_label("Edit Data Pasien");
    //insert function for edit button

    //delete button
    delete_button = gtk_button_new_with_label("Hapus Data Pasien");
    //insert function for delete button

    //search button
    search_button = gtk_button_new_with_label("Cari Data Pasien");
    //insert function for search button

    //back button
    back_button = gtk_button_new_with_label("Kembali");
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

int main(int argc, char *argv[]){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *control_button;
    GtkWidget *visit_button;
    GtkWidget *patient_button;
    GtkWidget *cash_button;
    GtkWidget *sick_button;
    
    // Initialize GTK
    gtk_init(&argc, &argv);

    //Main window creation
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Rumah Sakit X");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //patient button
    patient_button = gtk_button_new_with_label("Data Pasien");
    g_signal_connect(patient_button, "clicked", G_CALLBACK(patient_clicked), NULL);


    //visit button  
    visit_button = gtk_button_new_with_label("Data Kunjungan");
    //insert function for visit button

    //control button
    control_button = gtk_button_new_with_label("Data Kontrol");
    //insert function for control button

    //cash button
    cash_button = gtk_button_new_with_label("Data Kas/Cashflow");
    //insert function for cash button

    //sick button
    sick_button = gtk_button_new_with_label("Data Penyakit");
    //insert function for sick button

    //add button to vbox
    gtk_box_pack_start(GTK_BOX(vbox), patient_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), visit_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), control_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), cash_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), sick_button, TRUE, TRUE, 0);

    //add vbox to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
}