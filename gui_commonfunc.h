#include <gtk/gtk.h>

#ifndef GUI_COMMONFUNC_H
#define GUI_COMMONFUNC_H

void closeWindow(GtkWidget *widget, gpointer window){
    gtk_widget_destroy(GTK_WIDGET(window));
}

#endif