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

static gboolean numbers_left_right(gchar *expression,gint index)
{
  if(index != 0 && index+1 < strlen(expression)){ /* Check for index of first and last place */
    g_print("index:%d\n",index);
    if (isdigit(expression[index-1] && isdigit(expression[index+1])))
      return TRUE;
    else return FALSE;
  } 
  else return FALSE;
}

void calc_eq(gchar *expression, eq_result *result)
{
  int i=0,operator=0,number=0,paren=0,point=0,paren_index;
  gchar oper_list[20],num_list[40],paren_list[10];
  
  if (!result->valid){
    return;
  }

  for(i=0;i<strlen(expression);++i){
    if(isdigit(expression[i])){ /* Check for number */
        num_list[number++] = expression[i];
        g_print("i:%d\n",i);
        continue;
    } else if (ispunct(expression[i])){ /* Check operators ()/+-*. */
      if(numbers_left_right(expression,i)){
        if (expression[i] == '('){
          paren++;
          paren_list[paren_index++] = expression[i];
          continue;
        } else if (expression[i] == ')'){
          paren--;
          paren_list[paren_index++] = expression[i];
          continue;
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/'){
          oper_list[operator++] = expression[i];
          continue;
        } else if (expression[i] == '.'){
          point++;
          continue;
        }
      else {
        result->valid = 0;
        g_print("valid?:%d",result->valid);
        return;
      }
      }
    }
  }

  if(paren != 0){ /* Check for valid parenthesis */
    result->valid = 0;
    return;
  }

  result->result = 10;
}

void parse_equation(GtkWidget *widget,gpointer data)
{
  gchar label_text[LABEL_LEN] = "\0";
  eq_result *result=NULL;

  result = g_malloc(sizeof(eq_result));

  result->valid = 1;
  result->result = 0;

  strncpy(label_text,gtk_label_get_text(GTK_LABEL(data)),sizeof(gchar)*(LABEL_LEN-1));

  calc_eq(label_text,result);

  g_print("\nAFTER CALC %d\n",result->valid);
  if(result->valid){
    snprintf(label_text,sizeof(gchar)*LABEL_LEN,"%d",result->result);
    gtk_label_set_text(GTK_LABEL(data),label_text);
  } else {
    gtk_label_set_text(GTK_LABEL(data),"Invalid expression");
  }

  g_free(result);
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
