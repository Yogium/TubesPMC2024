#include <gtk/gtk.h>
#include "struct.h"
#include "penyakit.c"
#include "gui_commonfunc.h"

enum sickCountColumns{
    DIAGNOSIS,
    AMOUNT,
    N_SICK_COLUMNS
};


struct sickData{
    GtkWidget *entryDate;
    DataKunjungan *kunjungan;
    GtkListStore *sickList;
};

void sickYearSearched(GtkWidget *widget, gpointer data){
    DataKunjungan *kunjunganHead = ((struct sickData *)data)->kunjungan;

    const gchar *dateEntry = gtk_entry_get_text(GTK_ENTRY(((struct sickData *)data)->entryDate));
    GtkListStore *sickList = ((struct sickData *)data)->sickList;
    int year = atoi(dateEntry);

    ListPenyakit *head = NULL;
    head = diagbyyear(kunjunganHead, year);
    ListPenyakit *temp = head;
    gtk_list_store_clear(sickList);
    GtkTreeIter iter;
    while(temp != NULL){
        gtk_list_store_append(sickList, &iter);
        gtk_list_store_set(sickList, &iter, DIAGNOSIS, temp->penyakit, AMOUNT, temp->count, -1);
        temp = temp->next;
    }

}

void sickYearPressed(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *labelInstruct;
    GtkWidget *entryDate;
    GtkListStore *sickList;
    GtkWidget *view;
    GtkTreeViewColumn *column;

    DataKunjungan *kunjunganHead = data;
    struct sickData *sickData = malloc(sizeof(struct sickData));
    sickData->kunjungan = kunjunganHead;

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Data Pasien Sakit");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create label instruct
    labelInstruct = gtk_label_new("Masukkan tahun (yyyy)");

    //create entry date
    entryDate = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryDate), "Masukkan tahun (yyyy)");
    sickData->entryDate = entryDate;

    //create list store
    sickList = gtk_list_store_new(N_SICK_COLUMNS, G_TYPE_STRING, G_TYPE_INT);

    //create view
    view  = gtk_tree_view_new_with_model(GTK_TREE_MODEL(sickList));
    
    column = gtk_tree_view_column_new_with_attributes("Diagnosis", gtk_cell_renderer_text_new(), "text", DIAGNOSIS, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Jumlah", gtk_cell_renderer_text_new(), "text", AMOUNT, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    sickData->sickList = sickList;

    g_signal_connect(entryDate, "activate", G_CALLBACK(sickYearSearched), sickData);
    
    //add to vbox
    gtk_box_pack_start(GTK_BOX(vbox), labelInstruct, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entryDate, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);

    //add vbox to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}

void sickMonthSearched(GtkWidget *widget, gpointer data){
    DataKunjungan *kunjunganHead = ((struct sickData *)data)->kunjungan;
    const gchar *dateEntry = gtk_entry_get_text(GTK_ENTRY(((struct sickData *)data)->entryDate));
    GtkListStore *sickList = ((struct sickData *)data)->sickList;
    char datestr[7];
    strcpy(datestr, dateEntry);
    char *token = strtok(datestr, "/");
    int month = atoi(token);
    token = strtok(NULL, "/");
    int year = atoi(token);

    ListPenyakit *head = NULL;
    head = diagbymonth(kunjunganHead, month, year);
    ListPenyakit *temp = head;
    gtk_list_store_clear(sickList);
    GtkTreeIter iter;
    while(temp != NULL){
        gtk_list_store_append(sickList, &iter);
        gtk_list_store_set(sickList, &iter, DIAGNOSIS, temp->penyakit, AMOUNT, temp->count, -1);
        temp = temp->next;
    }
}

void sickMonthPressed(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *labelInstruct;
    GtkWidget *entryDate;
    GtkListStore *sickList;
    GtkWidget *view;
    GtkTreeViewColumn *column;

    DataKunjungan *kunjunganHead = data;
    struct sickData *sickData = malloc(sizeof(struct sickData));
    sickData->kunjungan = kunjunganHead;

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Data Pasien Sakit");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    //create vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    //create label instruct
    labelInstruct = gtk_label_new("Masukkan bulan dan tahun (mm/yyyy)");

    //create entry date
    entryDate = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryDate), "Masukkan bulan dan tahun (mm/yyyy)");
    sickData->entryDate = entryDate;

    //create list store
    sickList = gtk_list_store_new(N_SICK_COLUMNS, G_TYPE_STRING, G_TYPE_INT);
    
    //create view
    view  = gtk_tree_view_new_with_model(GTK_TREE_MODEL(sickList));

    column = gtk_tree_view_column_new_with_attributes("Diagnosis", gtk_cell_renderer_text_new(), "text", DIAGNOSIS, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Jumlah", gtk_cell_renderer_text_new(), "text", AMOUNT, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    sickData->sickList = sickList;

    g_signal_connect(entryDate, "activate", G_CALLBACK(sickMonthSearched), sickData);

    //add to vbox
    gtk_box_pack_start(GTK_BOX(vbox), labelInstruct, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entryDate, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);

    //add vbox to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}
