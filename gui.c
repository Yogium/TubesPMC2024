#include <gtk/gtk.h>

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
    //insert function for patient button


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