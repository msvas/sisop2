#include "chat.h"
#include "client.h"
#include "interface.h"

const gchar *entry_text;
int messageRead, sockfd;
MSG *buffer;

static void enter_callback(GtkWidget *widget, GtkWidget *entry)
{
    entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
    bzero(buffer, sizeof(MSG));
    strcpy(buffer->message, (char*) entry_text);
    printf ("Entry contents: %s\n", buffer->message);
    writeSocket(buffer);
    gtk_entry_set_text (GTK_ENTRY (entry), "");
    messageRead = 1;
}

static void destroy(GtkWidget *widget, gpointer data)
{
    buffer->connected = -1;
    writeSocket(buffer);
    gtk_main_quit ();
}

static gboolean cb_timeout(gpointer textview)
{
    /* Timeouts also don't automatically obtain main lock, but
       since we added this one using gdk_threads_add_timeout,
       lock has been obtained for us. */
    //gtk_button_set_label( GTK_BUTTON( data ), "Timeout" );
    //gtk_button_set_label( GTK_BUTTON( data ), "Timeout" );
    GtkTextBuffer *chatText;
    GtkTextIter iter;
    chatText = gtk_text_view_get_buffer(GTK_TEXT_VIEW (textview));
    gtk_text_buffer_get_start_iter(chatText, &iter);
    if(readSocket(buffer)) {
      //printf("%s\n", buffer->message);
      gtk_text_buffer_insert(chatText, &iter, buffer->userName, -1);
      gtk_text_buffer_insert(chatText, &iter, ":\n", -1);
      gtk_text_buffer_insert(chatText, &iter, buffer->message, -1);
      gtk_text_buffer_insert(chatText, &iter, "\n\n", -1);
      bzero(buffer, sizeof(MSG));
    }
    return( TRUE );
}

int chatInterface(int argc, char *argv[], int sock)
{
    GtkWidget *window;
    GtkWidget *scrollview;
    GtkWidget *textview;
    GtkWidget *chatEntry;
    //GtkTextBuffer *chatText;
    GtkWidget *avbox;
    //GtkTextIter iter;
    //GThread *thread;
    //GError *error = NULL;

    /* Secure glib */
    //if(! g_thread_supported())
        //g_thread_init( NULL );

    /* Secure gtk */
    gdk_threads_init();

    /* Obtain gtk's global lock */
    gdk_threads_enter();

    gtk_init (&argc, &argv);
    scrollview = gtk_scrolled_window_new(NULL, NULL);
    textview = gtk_text_view_new();
    avbox = gtk_vbox_new(FALSE, 0);

    //chatText = gtk_text_view_get_buffer(GTK_TEXT_VIEW (textview));
    //gtk_text_buffer_get_start_iter(chatText, &iter);

    messageRead = 0;
    buffer = malloc(sizeof(MSG));
    buffer->connected = 1;
    sockfd = sock;

    /* create a new window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 500, 250);
    gtk_window_set_title (GTK_WINDOW (window), "SISOPII Chat - Marcelo Vasques, 208895");
    g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);

    //gdk_threads_add_timeout(2300, cb_timeout, (gpointer)button);
    gdk_threads_add_timeout(1000, cb_timeout, (gpointer)textview);

    chatEntry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (chatEntry), 140);
    g_signal_connect (chatEntry, "activate", G_CALLBACK (enter_callback), chatEntry);

    gtk_widget_set_size_request(textview, 100, 180);

    gtk_container_add(GTK_CONTAINER (scrollview), textview);
    gtk_container_add(GTK_CONTAINER (avbox), scrollview);
    gtk_box_pack_start (GTK_BOX (avbox), chatEntry, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER (window), avbox);

    gtk_widget_show(chatEntry);
    gtk_widget_show(textview);
    gtk_widget_show(scrollview);
    gtk_widget_show(avbox);
    gtk_widget_show(window);

    gtk_main();

    gdk_threads_leave();

    return 0;
}
