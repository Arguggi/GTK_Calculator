#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "table.h"
#define LABEL_LEN 50

void cancel_label(GtkWidget *widget,gpointer data)
{
  gtk_label_set_text(GTK_LABEL(data),"");
}

void append_to_label(GtkWidget *widget,gpointer data)
{
  gchar label_text[LABEL_LEN] = "\0";
  gint label_lenght=0;
  
  label_lenght = strlen(gtk_label_get_text(GTK_LABEL(data)));
  if(label_lenght < LABEL_LEN-1){
  strncpy(label_text,gtk_label_get_text(GTK_LABEL(data)),sizeof(gchar)*(LABEL_LEN-1));
  strncpy((label_text+label_lenght),gtk_button_get_label(GTK_BUTTON(widget)),(sizeof(gchar)*((LABEL_LEN-1)-label_lenght)));
  gtk_label_set_text(GTK_LABEL(data),label_text);
  } else return;
}
void calc_eq(gchar *expressioni, eq_result *result)
{
  result->result = 10;
  result->valid = 1;
}
void parse_equation(GtkWidget *widget,gpointer data)
{
  gchar label_text[LABEL_LEN] = "\0";
  eq_result result;


  strncpy(label_text,gtk_label_get_text(GTK_LABEL(data)),sizeof(gchar)*(LABEL_LEN-1));

  calc_eq(label_text,&result);

  if(result.valid){
    snprintf(label_text,sizeof(gchar)*LABEL_LEN,"%d",result.result);
    gtk_label_set_text(GTK_LABEL(data),label_text);
  } else {
    gtk_label_set_text(GTK_LABEL(data),"Invalid expression");
  }

}
  
GtkWidget *create_table(void)
{
  const gchar table_buttons[4][5] = {{"789()"},{"456+-"},{"123*/"},{"0.SD="}};
  gint i=0,j=0;
  gchar string[5];
  GtkWidget *table, *button, *label;
  
  table = gtk_table_new(5,5,TRUE);
  label = gtk_label_new("");
  gtk_misc_set_alignment(GTK_MISC(label),1,0.5);
  gtk_table_attach_defaults(GTK_TABLE(table),label,0,5,0,1);

  
  for(j=0;j<4;++j){
    for(i=0;i<5;++i){
      if(table_buttons[j][i] != 'S' && table_buttons[j][i] != 'D'){
        string[0] = table_buttons[j][i];
        string[1] = '\0';
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
        if(string[0] != '='){
          g_signal_connect(button,"clicked",G_CALLBACK(append_to_label),label);
        } else g_signal_connect(button,"clicked",G_CALLBACK(parse_equation),label);
      } else if (table_buttons[j][i] == 'S'){ /*Square root button*/
        strncpy(string,"SQRT\0",sizeof(gchar)*5);
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
      } else {                                /*Reset button*/
        strncpy(string,"DEL\0",sizeof(gchar)*5);
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
        g_signal_connect(button,"clicked",G_CALLBACK(cancel_label),label);
      }
    }
  }
  gtk_table_set_row_spacing(GTK_TABLE(table),0,15);
  return table;
}
