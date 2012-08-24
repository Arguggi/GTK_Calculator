#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "table.h"
#define LABEL_LEN 270 
#define MULT 1
#define DIVI 2
#define ADDI 3
#define SUBT 4

Result results;

void square_root(GtkWidget *widget,gpointer data)
{
  gdouble text=0,result=0;
  gchar label_text[LABEL_LEN]="";
  gint label_lenght=0;

  label_lenght = strlen(gtk_label_get_text(GTK_LABEL(data)));

  if(label_lenght){
    text = atof(gtk_label_get_text(GTK_LABEL(data)));
    if (text > 0){
      result = sqrt(text);
      sprintf(label_text,"%.3f",result);
      gtk_label_set_text(GTK_LABEL(data),label_text);
    } else {
      gtk_label_set_text(GTK_LABEL(data),"Input is not positive");
    }
  }
}

void square(GtkWidget *widget,gpointer data)
{
  gdouble text=0;
  gchar label_text[LABEL_LEN]="";
  gint label_lenght=0;

  label_lenght = strlen(gtk_label_get_text(GTK_LABEL(data)));

  if(label_lenght){
    text = atof(gtk_label_get_text(GTK_LABEL(data)));
    if(text < sqrt(DBL_MAX)){
        text = text*text;
    } else {
      gtk_label_set_text(GTK_LABEL(data),"Input is too large");
      return;
    }
    sprintf(label_text,"%.3f",text);
    gtk_label_set_text(GTK_LABEL(data),label_text);
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

void operation(GtkWidget *widget,gpointer data)
{
  gchar button_pressed[2];
  
  strncpy(button_pressed,gtk_button_get_label(GTK_BUTTON(widget)),sizeof(gchar));
  results.first = atof(gtk_label_get_text(GTK_LABEL(data)));
  button_pressed[1] = '\0';
  if(button_pressed[0] == '*'){
    results.operation = MULT;
  } else if (button_pressed[0] == '/'){
    results.operation = DIVI;
  } else if (button_pressed[0] == '+'){
    results.operation = ADDI;
  } else {
    results.operation = SUBT;
  }

  gtk_label_set_text(GTK_LABEL(data),"");
}

void calculate(GtkWidget *widget,gpointer data)
{
  gdouble final=0.0,second=0.0;
  gchar label_text[LABEL_LEN];
  second = atof(gtk_label_get_text(GTK_LABEL(data)));

  switch(results.operation){
    case MULT:
      final = second * results.first;
      break;
    case DIVI:
      if (second != 0.0){
        final = results.first / second;
        break;
      } else {
        gtk_label_set_text(GTK_LABEL(data),"Cannot divide by 0");
        return;
      }
    case ADDI:
      final = second + results.first;
      break;
    case SUBT:
      final = results.first - second;
      break;
    default:
      gtk_label_set_text(GTK_LABEL(data),"Invalid expression");
      return;
  }
        
  sprintf(label_text,"%.3f",final);
  gtk_label_set_text(GTK_LABEL(data),label_text);
}

GtkWidget *create_table(void)
{
  const gchar table_buttons[4][5] = {{"789SC"},{"456+-"},{"123*/"},{"0.DB="}};
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
      if(isdigit(table_buttons[j][i]) || table_buttons[j][i] == '.'){
        string[0] = table_buttons[j][i];
        string[1] = '\0';
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
        g_signal_connect(button,"clicked",G_CALLBACK(append_to_label),label);
      } else if (table_buttons[j][i] == '='){ /*Calculate buttons*/
        string[0] = table_buttons[j][i];
        string[1] = '\0';
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
        g_signal_connect(button,"clicked",G_CALLBACK(calculate),label);
      } else if (ispunct(table_buttons[j][i])){ /*Operation buttons*/
        string[0] = table_buttons[j][i];
        string[1] = '\0';
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
        g_signal_connect(button,"clicked",G_CALLBACK(operation),label);
      } else if (table_buttons[j][i] == 'S'){ /*Square root button*/
        strncpy(string,"SQRT\0",sizeof(gchar)*5);
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
        g_signal_connect(button,"clicked",G_CALLBACK(square_root),label);
      } else if (table_buttons[j][i] == 'D'){ /*Delete button*/
        strncpy(string,"DEL\0",sizeof(gchar)*5);
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
        g_signal_connect(button,"clicked",G_CALLBACK(cancel_label),label);
      } else if (table_buttons[j][i] == 'B'){ /*Back button*/
        strncpy(string,"<-\0",sizeof(gchar)*5);
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
        //g_signal_connect(button,"clicked",G_CALLBACK(square),label);
      } else { /* Square button */
        strncpy(string,"^2\0",sizeof(gchar)*5);
        button = gtk_button_new_with_label(string);
        gtk_table_attach_defaults(GTK_TABLE(table),button,i,i+1,j+1,j+2);
        g_signal_connect(button,"clicked",G_CALLBACK(square),label);
      }
    }
  }
  gtk_table_set_row_spacing(GTK_TABLE(table),0,15);
  return table;
}
