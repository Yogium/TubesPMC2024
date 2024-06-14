#include <gtk/gtk.h>

static int count = 0;
static GtkWidget *label;

void button_clicked(GtkWidget *widget, gpointer data){
    char count_str[50] = {0};
    count++;
    sprintf(count_str, "Button clicked %d times", count);
    gtk_label_set_text(GTK_LABEL(label), count_str);
}

void button1_clicked(GtkWidget *widget, gpointer data){
    char count_str[50] = {0};
    count--;
    sprintf(count_str, "Button clicked %d times", count);
    gtk_label_set_text(GTK_LABEL(label), count_str);
}

void get_text(GtkWidget *widget, gpointer entry){
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));
    gtk_label_set_text(GTK_LABEL(label), text);
}

int main(int argc, char *argv[]){
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button1;
    GtkWidget *entry;
    GtkWidget *grid;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Click Me!");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 600);
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
    //button
    button = gtk_button_new_with_label("Add!");
    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), NULL);

    //button1
    button1 = gtk_button_new_with_label("Subtract!");
    g_signal_connect(button1, "clicked", G_CALLBACK(button1_clicked), NULL);

    //label
    label = gtk_label_new("Button clicked 0 times");

    //entry
    entry = gtk_entry_new();
    g_signal_connect(entry, "activate", G_CALLBACK(get_text), entry);

    //grid
    grid = gtk_grid_new();
    GtkWidget *label1 = gtk_label_new("Hello");
    gtk_grid_attach(GTK_GRID(grid), label1, 0, 0, 1, 1);
    GtkWidget *label2 = gtk_label_new("Label 2");
    GtkWidget *entry1 = gtk_entry_new();
    GtkWidget *entry2 = gtk_entry_new();

    //add button and label to vbox
    gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, TRUE, 100);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);
    //add vbox to window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_add(GTK_CONTAINER(window), hbox);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
}