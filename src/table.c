#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "table.h"
#define LABEL_LEN 10

static void square_root(GtkWidget *widget,gpointer data)
{
  gdouble text=0,result=0;
  gchar label_text[LABEL_LEN]="";
  gint label_lenght=0;

  label_lenght = strlen(gtk_label_get_text(GTK_LABEL(data)));

  if(label_lenght){
    text = atof(gtk_label_get_text(GTK_LABEL(data)));
    if (text > 0){
      result = sqrt(text);
      sprintf(label_text,"%f",result);
      gtk_label_set_text(GTK_LABEL(data),label_text);
    } else {
      gtk_label_set_text(GTK_LABEL(data),"Input is not positive");
    }
  }
}

void cancel_label(GtkWidget *widget,gpointer data)
{
  gtk_label_set_text(GTK_LABEL(data),"");
}

void append_to_label(GtkWidget *widget,gpointer data)
{
  gchar label_text[LABEL_LEN] = "\0";
  gint label_lenght=0;
  
  label_lenght = strlen(gtk_label_get_text(GTK_LABEL(data)));

  if(!strncmp(gtk_label_get_text(GTK_LABEL(data)),"Invalid expression",sizeof(gchar)*label_lenght)){
    cancel_label(widget,data);
    label_lenght = 0;
  }

  if(label_lenght < LABEL_LEN-1){
  strncpy(label_text,gtk_label_get_text(GTK_LABEL(data)),sizeof(gchar)*(LABEL_LEN-1));
  strncpy((label_text+label_lenght),gtk_button_get_label(GTK_BUTTON(widget)),(sizeof(gchar)*((LABEL_LEN-1)-label_lenght)));
  gtk_label_set_text(GTK_LABEL(data),label_text);
  } else return;
}

GtkWidget *create_table(void)
{
  const gchar table_buttons[4][5] = {{"789()"},{"456+-"},{"123*/"},{"0.SD="}};
  gint i=0,j=0;
  gchar string[5];
  GtkWidget *table, *button, *label, *frame;
  
  table = gtk_table_new(5,5,TRUE);
  label = gtk_label_new("");
  gtk_misc_set_alignment(GTK_MISC(label),1,0.5);

  frame = gtk_frame_new(NULL);
  gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_IN);

  gtk_container_add(GTK_CONTAINER(frame),label);

  gtk_table_attach_defaults(GTK_TABLE(table),frame,0,5,0,1);

  
  for(j=0;j<4;++j){
    for(i=0;i<5;++i){
      if(table_buttons[j][i] != 'S' && table_buttons[j][i] != 'D'){
        string[0] = table_buttons[j][i];
        string[1] = '\0';
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
        g_signal_connect(button,"clicked",G_CALLBACK(append_to_label),label);
      } else if (table_buttons[j][i] == 'S'){ /*Square root button*/
        strncpy(string,"SQRT\0",sizeof(gchar)*5);
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
        g_signal_connect(button,"clicked",G_CALLBACK(square_root),label);
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
