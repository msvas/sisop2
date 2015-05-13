#include "interface.h"

static void enter_callback( GtkWidget *widget,
                            GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}

int chatInterface(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *msgEntry, *chatEntry;
    gint tmp_pos;

    gtk_init (&argc, &argv);

    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 200, 100);
    gtk_window_set_title (GTK_WINDOW (window), "GTK Entry");
    g_signal_connect (window, "destroy",
                      G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (window, "delete-event",
                              G_CALLBACK (gtk_widget_destroy), 
                              window);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    msgEntry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (msgEntry), 50);
    g_signal_connect (msgEntry, "activate", G_CALLBACK (enter_callback), msgEntry);
    gtk_entry_set_text (GTK_ENTRY (msgEntry), "hello");
    tmp_pos = GTK_ENTRY (msgEntry)->text_length;
    gtk_editable_insert_text (GTK_EDITABLE (msgEntry), " world", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (msgEntry), 0, GTK_ENTRY (msgEntry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), msgEntry, TRUE, TRUE, 0);
    gtk_widget_show (msgEntry);
  
    chatEntry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (chatEntry), 50);
    g_signal_connect (chatEntry, "activate", G_CALLBACK (enter_callback), chatEntry);
    gtk_entry_set_text (GTK_ENTRY (chatEntry), "hello");
    gtk_editable_insert_text (GTK_EDITABLE (chatEntry), " world", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (chatEntry), 0, GTK_ENTRY (chatEntry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), chatEntry, TRUE, TRUE, 0);
    gtk_widget_show (chatEntry);

    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_widget_show (hbox);
                                  
    gtk_widget_show (window);

    gtk_main();

    return 0;
}