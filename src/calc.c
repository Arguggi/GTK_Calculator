#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

GtkWidget* create_table(void)
{
  const gchar table_buttons[4][10] = {{'7','\0','8','\0','9','\0','(','\0',')','\0'},{'4','\0','5','\0','6','\0','+','\0','-','\0'},
                                      {'1','\0','2','\0','3','\0','x','\0','-','\0'},{'0','\0',',','\0','S','\0','=','\0','=','\0'}};
  gint i=0,j=0;
  GtkWidget *table, *button, *label;
  
  table = gtk_table_new(5,5,TRUE);
  label = gtk_label_new("Operations will go here");
  gtk_table_attach_defaults(GTK_TABLE(table),label,0,4,0,1);

  for(j=0;j<4;++j){
    for(i=0;i<5;++i){
      button = gtk_button_new_with_label((*(table_buttons+j)+i*2));
      gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
    }
  }
  gtk_table_set_row_spacing(GTK_TABLE(table),0,25);
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
  g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);

  vbox = create_table();

  gtk_container_add(GTK_CONTAINER(window),vbox);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
