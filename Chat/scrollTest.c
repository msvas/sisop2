#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

int main(int argc, char *argv[]) 
{ 
    GtkWidget *window; 
    gtk_init (&argc, &argv); 
    GtkWidget *scrollview = gtk_scrolled_window_new( NULL, NULL ); 
    GtkWidget *textview = gtk_text_view_new(); 
    GtkTextBuffer *buffer; 
    GtkWidget *avbox = gtk_vbox_new(FALSE, 0); 
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
    GtkTextIter iter; 
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (textview)); 
    gtk_text_buffer_get_start_iter(buffer, &iter); 
     
    gtk_window_set_default_size(GTK_WINDOW (window), 200, 200); 
     
    gtk_container_add(GTK_CONTAINER (scrollview), textview); 
    gtk_container_add(GTK_CONTAINER (avbox), scrollview); 
    gtk_container_add(GTK_CONTAINER (window), avbox); 
       
    gtk_widget_show(textview); 
    gtk_widget_show(scrollview); 
    gtk_widget_show(avbox); 
    gtk_widget_show(window); 
     
    gtk_text_buffer_insert(buffer, &iter, "a line\n" , -1); 
    gtk_text_buffer_insert(buffer, &iter, "another line\n" , -1); 
     
    gtk_text_buffer_insert(buffer, &iter, "half a line :-" , -1); 
    gtk_text_buffer_insert(buffer, &iter, ": the other half\n" , -1); 
     
     

    gtk_main (); 
    return 0; 
}  