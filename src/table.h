#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

typedef struct
{
  gdouble first;
  gint operation;
}Result;


void square_root(GtkWidget *widget,gpointer data);
void square(GtkWidget *widget,gpointer data);
void cancel_label(GtkWidget *widget,gpointer data);
void append_to_label(GtkWidget *widget,gpointer data);
void operation(GtkWidget *widget,gpointer data);
void calculate(GtkWidget *widget,gpointer data);
GtkWidget *create_table(void);
#endif /* TABLE_H_INCLUDED*/
