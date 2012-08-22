#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GdkPixbuf *create_pixbuf(const gchar *filename)
{
  GdkPixbuf *pixbuf;
  GError *error = NULL;

  pixbuf = gdk_pixbuf_new_from_file(filename,&error);
  if (!pixbuf){
    fprintf(stderr, "%s\n",error->message);
    g_error_free(error);
  }
  return pixbuf;
}

GtkWidget* create_table(void)
{
  const gchar table_buttons[4][5] = {{"789()"},{"456+-"},{"123x/"},{"0.SC="}};
  gint i=0,j=0;
  gchar *string;
  GtkWidget *table, *button, *label;
  
  string = malloc(sizeof(gchar) * 5);
  table = gtk_table_new(5,5,TRUE);
  label = gtk_label_new("Operations will go here");
  gtk_table_attach_defaults(GTK_TABLE(table),label,0,4,0,1);

  for(j=0;j<4;++j){
    for(i=0;i<5;++i){
      if(table_buttons[j][i] != 'S' && table_buttons[j][i] != 'C'){
        string[0] = table_buttons[j][i];
        string[1] = '\0';
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
      } else if (table_buttons[j][i] == 'S'){ /*Square root button*/
        strncpy(string,"SQRT\0",sizeof(gchar)*5);
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
      } else {                                /*Reset button*/
        strncpy(string,"CANC\0",sizeof(gchar)*5);
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
      }
    }
  }
  gtk_table_set_row_spacing(GTK_TABLE(table),0,25);
  free(string);
  return table;
}


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
