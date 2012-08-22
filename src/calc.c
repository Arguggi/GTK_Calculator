#include <gtk/gtk.h>
#include <string.h>
#include "icon.h"
#include "table.h"
#define LABEL_LEN 50

int main(int argc, char **argv)
{
  GtkWidget *window, *vbox;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window),"Calc");
  gtk_container_set_border_width(GTK_CONTAINER(window),15);
  gtk_window_set_resizable(GTK_WINDOW(window),TRUE);
  gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("../img/calculator.png"));
  g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);

  vbox = create_table();

  gtk_container_add(GTK_CONTAINER(window),vbox);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
