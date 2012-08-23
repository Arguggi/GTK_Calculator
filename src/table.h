#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

typedef struct
{
  int result;
  int valid;
}eq_result;


void cancel_label(GtkWidget *widget,gpointer data);
GtkWidget *create_table(void);
void append_to_label(GtkWidget *widget,gpointer data);
#endif /* TABLE_H_INCLUDED*/
