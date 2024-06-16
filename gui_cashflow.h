#include <gtk/gtk.h>
#include <stdlib.h>
#include "gui_commonfunc.h"
#include "cashflow.c"

#ifndef GUI_CASHFLOW_H
#define GUI_CASHFLOW_H

#endif

struct cashflowData{
    GtkWidget *labelValue;
    DataKunjungan *head;
};

void yearSearched(GtkWidget *widget, gpointer data){
    DataKunjungan *head = ((struct cashflowData *)data)->head;
    GtkWidget *labelValue = ((struct cashflowData *)data)->labelValue;
    const gchar *yearEntry = gtk_entry_get_text(GTK_ENTRY(widget));
    char yearstr[5];
    strcpy(yearstr, yearEntry);
    int year = atoi(yearstr);
    int income = income_yearly(head, year);
    char incomeString[100];
    sprintf(incomeString, "Rp. %d", income);
    gtk_label_set_text(GTK_LABEL(labelValue), incomeString);
}

void cashflowYearClicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *labelInstruct;
    GtkWidget *dateEntry;
    GtkWidget *labelValue;
    GtkWidget *exitButton;

    DataKunjungan *head = data;
    struct cashflowData *cashflowData = malloc(sizeof(struct cashflowData));
    cashflowData->head = head;
    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "data kas per tahun");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    
    //create label value
    labelValue = gtk_label_new("Rp. 0");
    cashflowData->labelValue = labelValue;

    //create date entry
    dateEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(dateEntry), "Masukkan Tahun (yyyy)");
    g_signal_connect(dateEntry, "activate", G_CALLBACK(yearSearched), cashflowData);


    //create label instruct
    labelInstruct = gtk_label_new("Masukkan tahun yang ingin dilihat (YYYY))");
    
    //create exit button
    exitButton = gtk_button_new_with_label("kembali");
    g_signal_connect(exitButton, "clicked", G_CALLBACK(closeWindow), window);

    //add button to vbox
    gtk_box_pack_start(GTK_BOX(vbox), labelInstruct, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), dateEntry, TRUE, TRUE, 100);
    gtk_box_pack_start(GTK_BOX(vbox), labelValue, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), exitButton, TRUE, TRUE, 100);

    //add vbox to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}


void cashflowClicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *exitButton;
    GtkWidget *yearButton;
    GtkWidget *monthButton;
    GtkWidget *averageLabel;
    GtkWidget *averageValue; 

    DataKunjungan *head = data;

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "data kas");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create year button
    yearButton = gtk_button_new_with_label("Lihat Data Kas per Tahun");
    g_signal_connect(yearButton, "clicked", G_CALLBACK(cashflowYearClicked), head);

    //create month button
    monthButton = gtk_button_new_with_label("Lihat Data Kas per Bulan");
    //insert function for month button

    //create average label
    averageLabel = gtk_label_new("Rata-rata Kas Setiap Tahun");
    float average = average_income_per_year(head);//insert function to get average
    char averageString[100];
    sprintf(averageString, "Rp. %.2f", average);
    averageValue = gtk_label_new(averageString);


    //create exit button
    exitButton = gtk_button_new_with_label("kembali");
    g_signal_connect(exitButton, "clicked", G_CALLBACK(closeWindow), window);

    //add button to vbox
    gtk_box_pack_start(GTK_BOX(vbox), yearButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), monthButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), averageLabel, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), averageValue, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), exitButton, TRUE, TRUE, 0);

    //add vbox to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}